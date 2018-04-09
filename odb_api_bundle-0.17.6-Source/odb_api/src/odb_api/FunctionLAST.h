/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File FunctionLAST.h
// Piotr Kuchta - ECMWF Nov 2016

#ifndef odb_api_FunctionLAST_H
#define odb_api_FunctionLAST_H

#include "odb_api/FunctionExpression.h"

namespace odb {
namespace sql {
namespace expression {
namespace function {

class FunctionLAST : public FunctionExpression {
public:
	FunctionLAST(const std::string&,const expression::Expressions&);
	FunctionLAST(const FunctionLAST&);
	~FunctionLAST(); 

	SQLExpression* clone() const;

private:
// No copy allowed
	FunctionLAST& operator=(const FunctionLAST&);

	double value_;

// -- Overridden methods
	virtual const odb::sql::type::SQLType* type() const;
	virtual void prepare(SQLSelect&);
	virtual void cleanup(SQLSelect&);
	virtual void partialResult();
	virtual double eval(bool& missing) const;
	bool isAggregate() const { return true; }

	virtual void output(SQLOutput&) const;
// -- Friends
	//friend std::ostream& operator<<(std::ostream& s,const FunctionLAST& p)
	//	{ p.print(s); return s; }
};

} // namespace function
} // namespace expression 
} // namespace sql
} // namespace odb 

#endif
