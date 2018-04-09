/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include <climits>
#include <cfloat>

#include "odb_api/FunctionFIRST.h"

namespace odb {
namespace sql {
namespace expression {
namespace function {

FunctionFIRST::FunctionFIRST(const std::string& name,const expression::Expressions& args)
: FunctionExpression(name, args),
  value_(DBL_MAX),
  notFirst_(false)
{}

FunctionFIRST::FunctionFIRST(const FunctionFIRST& other)
: FunctionExpression(other.name_, other.args_),
  value_(other.value_),
  notFirst_(other.notFirst_)
{}

SQLExpression* FunctionFIRST::clone() const { return new FunctionFIRST(*this); }

const odb::sql::type::SQLType* FunctionFIRST::type() const { return args_[0]->type(); }

FunctionFIRST::~FunctionFIRST() {}

double FunctionFIRST::eval(bool& missing) const
{
	if (value_ == DBL_MAX)
		missing = true;

	return value_;
}

void FunctionFIRST::prepare(SQLSelect& sql)
{
	FunctionExpression::prepare(sql);
	value_ = DBL_MAX;
}

void FunctionFIRST::cleanup(SQLSelect& sql)
{
	FunctionExpression::cleanup(sql);
	value_ = DBL_MAX;
}

void FunctionFIRST::output(SQLOutput& s) const 
{ 
	bool missing (false);
	double d (eval(missing)); 
	type()->output(s, d, missing);
}

void FunctionFIRST::partialResult() 
{
    if (notFirst_)
        return;

	bool missing (false);
    value_ = (args_[0]->eval(missing));
    notFirst_ = true;
}

} // namespace function
} // namespace expression
} // namespace sql
} // namespace odb
