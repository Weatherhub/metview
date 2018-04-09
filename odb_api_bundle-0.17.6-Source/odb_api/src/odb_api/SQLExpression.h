/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File SQLExpression.h
// Baudouin Raoult - ECMWF Dec 03

#ifndef SQLExpression_H
#define SQLExpression_H

#include "SQLType.h"
#include "Types.h"

namespace odb {
namespace sql {
// Forward declarations

class SQLSelect;
class SQLTable;
class SQLIndex;
class SQLOutput;

namespace expression {

class Expressions;
class SQLExpression;
class Dictionary;

class SQLExpression {
public:
	SQLExpression();
	virtual ~SQLExpression(); 

	virtual void prepare(SQLSelect&) = 0;
	virtual void cleanup(SQLSelect&) = 0;

	// -- For WHERE
	virtual double eval(bool& missing) const = 0;

	virtual bool andSplit(expression::Expressions&) { return false; }
    virtual void tables(std::set<SQLTable*>&) {}

	virtual bool isConstant() const = 0;
	virtual bool isNumber() const { return false; }
	virtual bool isVector() const;
	virtual Expressions& vector(); 
	virtual bool isDictionary() const { return false; }
	virtual Dictionary& dictionary();

	virtual SQLExpression* simplify(bool&);

    virtual void title(const std::string&);
    virtual std::string title() const;

	virtual const odb::sql::type::SQLType* type() const = 0;
	// ----

	virtual SQLExpression* clone() const = 0;
	
	virtual bool isAggregate() const { return false; }
	// For select expression

	virtual void output(SQLOutput&) const;
	virtual void partialResult() {}
	virtual void expandStars(const std::vector<SQLTable*>&,expression::Expressions&);

	virtual bool isBitfield() const { return isBitfield_; }
	BitfieldDef bitfieldDef() const { return bitfieldDef_; }

	virtual bool hasMissingValue() const { return hasMissingValue_; }
	double missingValue() const { return missingValue_; }

	virtual bool indexed()  { return false; }
	virtual bool useIndex() { return false; }
	virtual SQLIndex* getIndex(double* = 0) { return 0; }

	static SQLExpression* number(double);

    virtual void print(std::ostream&) const = 0;

protected:
	SQLExpression(Expressions*);

	bool isBitfield_;
	BitfieldDef bitfieldDef_;
	bool hasMissingValue_;
	double missingValue_;
	//bool isVector_;
	//Vector* vector_;

private:
	SQLExpression(const SQLExpression&);
	SQLExpression& operator=(const SQLExpression&);

    std::string title_;

    friend std::ostream& operator<<(std::ostream& s,const SQLExpression& p) { p.print(s); return s; }
};

} // namespace expression
} // namespace sql
} // namespace odb

//#include "odb_api/Expressions.h"

using namespace odb::sql::expression;

#endif
