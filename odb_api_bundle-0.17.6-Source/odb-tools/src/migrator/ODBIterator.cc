/*
 * © Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

///
/// \file ODBIterator.cc
///
/// @author Piotr Kuchta, Feb 2009

#include <map>

#include "eckit/config/Resource.h"
#include "eckit/filesystem/PathName.h"
#include "eckit/parser/StringTools.h"
#include "migrator/ODBIterator.h"
#include "odb_api/MetaData.h"
#include "odb_api/SQLDatabase.h"
#include "odb_api/SQLParser.h"
#include "odb_api/SQLSelectFactory.h"
#include "odb_api/StringTool.h"
#include "odb_api/odb_api.h"
#include "odb_api/tools/Tool.h"


namespace odb { namespace sql { class SQLInteractiveSession; } }

extern "C" {
#include "odbdump.h"
}

using namespace eckit;

namespace odb {
namespace tool {

//ODBIterator::ODBIterator(const PathName& db, const std::string& sql)
ODBIterator::ODBIterator(const std::string& db, const std::string& sql)
: db_(db),
  odbHandle_(0),
  noOfColumns_(0),
  ci_(0),
  columns_(new odb::MetaData(0, (odb::Column *) 0)),
  newDataset_(false),
  data_(0),
  nd_(0),
  schemaParsed_(false),
  refCount_(0),
  noMore_(true),
  context_(0)
{
	Log::info() << "ODBIterator::ODBIterator: @" << this << " db=" << db << std::endl;

	const std::string odbDirectory = db; //.asString();
	Log::info() << "Opening ODB in '" << odbDirectory << "'" << std::endl;
	if (! PathName(odbDirectory).exists())
        throw CantOpenFile(odbDirectory);
	
	std::string select = sql.size() ? sql : defaultSQL(db);

	ASSERT(select.size() != 0 && select != "");

	const std::string dbPath = db; //.asString();
	const char *db_path = dbPath.c_str();
	const char *sql_select = select.c_str();

	Log::info() << "ODBIterator::ODBIterator: Calling odbdump_open(\"" << db_path << "\",\"" << sql_select << "\", NULL, NULL, NULL, &" << nd_ << ")" << std::endl;

	odbHandle_ = odbdump_open(db_path, sql_select, NULL, NULL, NULL, &nd_);
	ASSERT("odbdump_open returned NULL" && odbHandle_);
	ASSERT("odbdump_open returned nd_ <= 0" && nd_ > 0);

	data_ = new double[nd_];

	//next();
	//if (noMore_) Log::warning() << "ODBIterator::ODBIterator: result set empty, no data." << std::endl;
}

bool ODBIterator::next(eckit::ExecutionContext*)
{
	newDataset_ = false;
	noOfColumns_ = odbdump_nextrow(odbHandle_, data_, nd_, &newDataset_);
	if (noOfColumns_ == 0)
	{
		return !(noMore_ = true);
	}

	if (newDataset_)
	{
		Log::info() << "ODBIterator::readRow: new data set" << std::endl;
		createColumns();
	}

	ASSERT(noOfColumns_ <= nd_);
    // FIXME: read the missing values for a given constant from somewhere
	// This is because sometime ODB has MISSING_VALUE_REAL in INTEGER columns...
	// for example station_type@hdr in ECMA.conv
	for (int i = 0; i < noOfColumns_; ++i)
		if ((*columns_)[i]->type() == odb::INTEGER && data_[i] == odb::MDI::realMDI())
			data_[i] = odb::MDI::integerMDI();

	return !(noMore_ = false);
}

void ODBIterator::createColumns()
{
	Log::debug() << " => ODBIterator::createColumns: " << std::endl;

	delete columns_;
	columns_ = new odb::MetaData(noOfColumns_, (odb::Column *) 0);

	bool preservePrecision = Resource<bool>("$ODB2ODA_PRESERVE_PRECISION", false);
	
	ci_ = (colinfo_t *) odbdump_destroy_colinfo( (colinfo_t *) ci_, noOfColumns_); 
	int nci = 0;
	ci_ = (colinfo_t *) odbdump_create_colinfo(odbHandle_, &nci); 

    std::map<std::string, std::string> truenames;
	for (int i = 0; i < noOfColumns_; i++)
	{
		colinfo_t *pci = &((colinfo_t *) ci_)[i];
		std::string name = pci->nickname ? pci->nickname : pci->name;
        truenames[name] = pci->name;

		odb::ColumnType type = odb::REAL;
		double missing = odb::MDI::integerMDI(); 

		switch(pci->dtnum)
		{
			case DATATYPE_REAL4:
				type = odb::REAL;
				missing = odb::MDI::realMDI(); 
				break;

			case DATATYPE_REAL8:
				type = preservePrecision ? odb::DOUBLE : odb::REAL;
				missing = odb::MDI::realMDI(); 
				break;

			case DATATYPE_STRING:
				type = odb::STRING;
				break;

			case DATATYPE_INT4:
			case DATATYPE_YYYYMMDD:
			case DATATYPE_HHMMSS:
				type = odb::INTEGER;
				break;

			case DATATYPE_BITFIELD:
				type = odb::BITFIELD;
				break;

			default:
				Log::error() << "Unsupported type: [" << pci->type_name << "] " << name
							<< std::endl;
				break;
		}
		setColumn(i, name, type, missing);
	}
	getSchema(db_).updateBitfieldsDefs(columns(), truenames);
	Log::debug() << " <= ODBIterator::createColumns: " << std::endl;
}

void ODBIterator::destroy()
{
	Log::debug() << "ODBIterator::destroy: @" << this << std::endl;
	odbdump_destroy_colinfo( (colinfo_t *) ci_, noOfColumns_); 
	odbdump_close(odbHandle_);
	delete columns_;
	delete [] data_;
}

ODBIterator::~ODBIterator ()
{
	Log::info() << "ODBIterator::~ODBIterator: @" << this << std::endl;
	destroy();
}

odb::MetaData& ODBIterator::columns() { return *columns_; }

double* ODBIterator::data() { return data_; }

bool ODBIterator::isNewDataset() { return newDataset_; }

int ODBIterator::setColumn(unsigned long index, std::string& name, odb::ColumnType type, double missingValue)
{
	//Log::debug() << "ODBIterator::setColumn: " << index << ", " << name << ", " << columnTypeName(type) << ", " << missingValue << std::endl;

	ASSERT(int(index) < noOfColumns_);
	ASSERT(columns_);
	odb::Column* col = (*columns_)[index];
	delete col;
	col = new odb::Column(*columns_);
	ASSERT(col);

	col->name(name); 
	col->type<DataStream<SameByteOrder, DataHandle> >(type, false);
	col->missingValue(missingValue);

	(*columns_)[index] = col;
	return 0;
}


//const char* defaultSQL = "select {!/LINK/} from hdr,body,errstat";
PathName ODBIterator::schemaFile(const PathName& db)
{
    Log::info() << "ODBIterator::schemaFile: db=" << db << std::endl;

	std::string d = db;

	if (d[d.size() - 1] != '/')
		d += "//";

	std::string s = StringTools::split(".", StringTools::split("//", d).back())[0];

	return d + s + ".sch";
}

const odb::sql::SchemaAnalyzer& ODBIterator::getSchema(const PathName& db)
{
	//odb::sql::SQLSelectFactory::instance().config(); //odb::sql::SQLOutputConfig());
	// FIXME: this is not good cause when you call the method several times with different db it will fail...
	// It's not used like that at the moment, anyway. So perhaps I should make db a member (db_).
	if (!schemaParsed_)
	{
		PathName schemaFile = this->schemaFile(db);
		Log::info() << "ImportODBTool::getSchema: parsing '" << schemaFile << "'" << std::endl;
	
		odb::sql::SQLParser p;
		p.parseString(session_, StringTool::readFile(schemaFile), static_cast<DataHandle*>(0), session_.selectFactory().config());
		schemaParsed_ = true;
	}

	return session_
			.currentDatabase()
			.schemaAnalyzer();
}

std::string ODBIterator::defaultSQL(const PathName& db)
{
	return getSchema(db).generateSELECT();
}

} // namespace tool 
} //namespace odb 

