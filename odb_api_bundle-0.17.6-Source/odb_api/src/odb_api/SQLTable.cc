/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/parser/Tokenizer.h"
#include "odb_api/SQLBitColumn.h"
#include "odb_api/SQLColumn.h"
#include "odb_api/SQLDatabase.h"

using namespace eckit;

namespace odb {
namespace sql {

SQLTable::SQLTable(SQLDatabase& owner,const std::string& path,const std::string& name):
	path_(path),
	name_(name),
	owner_(owner),
	master_(0)
{
	//Log::info() << "SQLTable[path=" << path_ << ",name=" << name << ",no_rows=" << no_rows_ << ",index=" << index_ << "]" << std::endl;
}

SQLTable::~SQLTable() { clearColumns(); }

void SQLTable::clearColumns()
{
	// Don't loop on names, as we have all bitmap entries pointing to the same
	for(std::map<int,SQLColumn*>::iterator m = columnsByIndex_.begin(); m != columnsByIndex_.end(); ++m)
	{
		SQLColumn* p = (*m).second;
		delete p;
	}
	columnsByName_.clear();
	columnsByIndex_.clear();
}

std::vector<std::string> SQLTable::columnNames() const
{
	std::vector<std::string> results;
	for(std::map<int,SQLColumn*>::const_iterator j = columnsByIndex_.begin(); j != columnsByIndex_.end(); ++j)
		results.push_back((*j).second->name());
	return results;
}

FieldNames SQLTable::bitColumnNames(const std::string& name) const
{
	typedef std::map<std::string, FieldNames>::const_iterator I;
	I i = bitColumnNames_.find(name);
	if (i != bitColumnNames_.end())
		return (*i).second;

	ASSERT("name not found" && name.find("@") == std::string::npos);


	std::string columnName;
	FieldNames fieldNames;
	size_t counter = 0;
	for (I i = bitColumnNames_.begin(); i != bitColumnNames_.end(); ++i)
	{
		if (i->first.find(name + "@") == 0)
		{
			columnName = i->first;
			fieldNames = i->second;
			++counter;
		}
	}
	if (counter == 0) throw eckit::UserError(std::string("Column '") + name + "' not found.");
	if (counter != 1) throw eckit::UserError(std::string("Ambiguous column name: '") + name + "'");

	return fieldNames;
}


//void SQLTable::addColumn(const std::string& name, int index, const type::SQLType& type, const FieldNames& bitmap)
void SQLTable::addColumn(const std::string& name, int index, const type::SQLType& type, bool hasMissingValue, double missingValue, bool
isBitfield, const BitfieldDef& bitfieldDef)
{
	const FieldNames& bitmap = bitfieldDef.first;
	SQLColumn *col = isBitfield ? createSQLColumn(type, name, index, hasMissingValue, missingValue, bitfieldDef)
                                : createSQLColumn(type, name, index, hasMissingValue, missingValue);

	columnsByName_[name]   = col;
	columnsByIndex_[index] = col;

	bitColumnNames_[name] = bitmap;

	std::vector<std::string> tokens;
	Tokenizer("@")(name, tokens);

	ASSERT(tokens.size() == 1 || tokens.size() == 2);

	// TODO: clean up, probably no need to do this parsing as we have the whole bitfieldDef now
	std::string tableName = (tokens.size() == 2) ? tokens[1] : "";
	std::string columnName = tokens[0];

	for(FieldNames::const_iterator j = bitmap.begin(); j != bitmap.end(); ++j)
	{
		std::string fieldName = *j;
		std::string n = columnName + "." + fieldName + "@" + tableName;
		columnsByName_[n] = col;

		//Log::info() << "SQLTable::addColumn: columnsByName_[" << n << "] = " << *col << std::endl;
	}
}

void SQLTable::addColumn(SQLColumn *col, const std::string& name, int index)
{
	columnsByName_[name]   = col;	
	columnsByIndex_[index] = col;	
}

//bool SQLTable::hasColumn(const std::string& name, std::string* fullName, bool *hasMissingValue, double *missingValue, BitfieldDef* bitfieldDef)
bool SQLTable::hasColumn(const std::string& name, std::string* fullName)
{
	std::map<std::string,SQLColumn*>::iterator j = columnsByName_.find(name);
	return j != columnsByName_.end();
}

unsigned long long SQLTable::noRows() const
{
	std::map<std::string,SQLColumn*>::const_iterator j = columnsByName_.begin();
	if(j != columnsByName_.end())
		return(*j).second->noRows();
	return 0;
}


SQLColumn* SQLTable::column(const std::string& name)
{
	std::map<std::string,SQLColumn*>::iterator j = columnsByName_.find(name);
	if(j != columnsByName_.end())
		return (*j).second;

	std::vector<std::string> v;
	Tokenizer(".")(name, v);

	if(v.size() > 1)
	{
		SQLColumn* col = column(v[0]);
		columnsByName_[name] = new SQLBitColumn(*col,v[1]);
		return columnsByName_[name];
	}

	throw eckit::UserError("Column not found",name);

}

SQLPool* SQLTable::pool(int index)
{
	std::map<int,SQLPool*>::iterator j = pools_.find(index);
	if(j == pools_.end())
		return 0;
	else
		return (*j).second;
}

void SQLTable::addLinkFrom(const SQLTable* from)
{
	linksFrom_.insert(from);
}

bool SQLTable::hasLinkFrom(const SQLTable& from) const
{
	return linksFrom_.find(&from) != linksFrom_.end();
}

void SQLTable::addLinkTo(const SQLTable* to)
{
	linksTo_.insert(to);
}

bool SQLTable::hasLinkTo(const SQLTable& to) const
{
	return linksTo_.find(&to) != linksTo_.end();
}

bool SQLTable::isParentOf(const SQLTable& other) const
{
	if(hasLinkTo(other))
		return true;

	for(std::set<const SQLTable*>::const_iterator j = linksTo_.begin();
		j != linksTo_.end(); ++j)
			if((*j)->isParentOf(other))
				return true;

	return false;
}

SQLTable* SQLTable::master() const      
{ 
	return master_? master_ : const_cast<SQLTable*>(this); 
}

void SQLTable::master(SQLTable* master) 
{ 
//	std::cout << "MASTER of " << name() << " " << master->name() << std::endl;
	master_ = master;            
}

std::string SQLTable::fullName() const
{
	return owner_.name() + "." + name_;
}

bool SQLTable::sameAs(const SQLTable& other) const
{
	return owner_.sameAs(other.owner_) && (name_ == other.name_);
}

bool SQLTable::sameDatabase(const SQLTable& other) const
{
	return &owner_ == &other.owner_;
}

void SQLTable::print(std::ostream& s) const
{
	s << "CREATE TABLE " << fullName() << " AS (" << std::endl;
	for(std::map<int,SQLColumn*>::const_iterator j = columnsByIndex_.begin(); j != columnsByIndex_.end(); ++j)
	{
		SQLColumn *c = j->second;
		s << "	" << c->name() << " " << c->type() << "," << std::endl;
	}
	s << ")" << std::endl;
}

} // namespace sql 
} // namespace odb 

