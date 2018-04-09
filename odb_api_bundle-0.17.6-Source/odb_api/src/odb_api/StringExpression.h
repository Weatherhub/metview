/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File StringExpression.h
// Baudouin Raoult - ECMWF Dec 03

#ifndef StringExpression_H
#define StringExpression_H

#include "odb_api/SQLExpression.h"

namespace odb {
namespace sql {
namespace expression {

class StringExpression : public SQLExpression {
public:
	StringExpression(const std::string&);
	StringExpression(const StringExpression&);
	~StringExpression(); 

	SQLExpression* clone() const;

private:
// No copy allowed
	StringExpression& operator=(const StringExpression&);

	std::string name_;
	double value_;

// -- Overridden methods
	virtual void print(std::ostream& s) const;
	virtual void expandStars(const std::vector<SQLTable*>&, expression::Expressions&);
	virtual void prepare(SQLSelect& sql);
	virtual void cleanup(SQLSelect& sql);

	const type::SQLType* type() const;
	virtual double eval(bool& missing) const;
	virtual bool isConstant() const { return true; }
	virtual bool isNumber() const { return true; }
	virtual void output(std::ostream& s) const;
};

} // namespace expression
} // namespace sql
} // namespace odb 

#endif
