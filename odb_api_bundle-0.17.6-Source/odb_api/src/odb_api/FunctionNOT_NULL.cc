/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "odb_api/FunctionNOT_NULL.h"

namespace odb {
namespace sql {
namespace expression {
namespace function {

FunctionNOT_NULL::FunctionNOT_NULL(const std::string& name,const expression::Expressions& args)
: FunctionExpression(name, args)
{}

FunctionNOT_NULL::FunctionNOT_NULL(const FunctionNOT_NULL& other)
: FunctionExpression(other.name_, other.args_)
{}

FunctionNOT_NULL::~FunctionNOT_NULL() {}

SQLExpression* FunctionNOT_NULL::clone() const { return new FunctionNOT_NULL(*this); }

const type::SQLType* FunctionNOT_NULL::type() const { return &type::SQLType::lookup("real"); }

// Don't set the missing flags
double FunctionNOT_NULL::eval(bool&) const
{
	bool missing = false;
#if 0
	std::cout << "FunctionNOT_NULL " << (*args_[0])  << " " << args_[0]->eval(missing);
	std::cout << " missing = " << missing << std::endl;
#else
	args_[0]->eval(missing);
#endif

	return !missing;
}

} // namespace function
} // namespace expression
} // namespace sql
} // namespace odb
