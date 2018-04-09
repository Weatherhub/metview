/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "odb_api/ColumnExpression.h"
#include "odb_api/FunctionEQ.h"
#include "odb_api/FunctionFactory.h"
#include "odb_api/SQLType.h"

namespace odb {
namespace sql {
namespace expression {
namespace function {

using namespace odb::sql::type;

const type::SQLType* FunctionEQ::type() const { return &type::SQLType::lookup("double"); }

FunctionEQ::FunctionEQ(const FunctionEQ& other)
: FunctionExpression(other.name_, other.args_),
  tmp_(other.tmp_)
{}

FunctionEQ::FunctionEQ(const std::string& name, const expression::Expressions& args)
: FunctionExpression(name, args),
  tmp_(0)
{}

SQLExpression* FunctionEQ::clone() const { return new FunctionEQ(*this); }

FunctionEQ::~FunctionEQ() {}

void FunctionEQ::trimStringInDouble(char* &p, size_t& len)
{
	len = 0;
	for(; len < sizeof(double) && isprint(p[len]); ++len)
		;
	for(; len > 0 && isspace(p[len - 1]); --len)
		;
	size_t plen = len;
	for (char *pp = p; isspace(*p) && p < pp + plen;)
	{
		++p;
		--len;
	}
}

bool FunctionEQ::equal(const SQLExpression& l, const SQLExpression& r, bool& missing)
{
	if (l.type()->getKind() == SQLType::stringType)
	{
		double v1 = l.eval(missing);
		double v2 = r.eval(missing);
		if (missing)
			return false;

		char *p1 = reinterpret_cast<char*>(&v1);
		char *p2 = reinterpret_cast<char*>(&v2);
		
		size_t len1 = sizeof(double);
		size_t len2 = sizeof(double);

		trimStringInDouble(p1, len1);
		trimStringInDouble(p2, len2);

		if (len1 != len2)
			return false;

		return 0 == strncmp(p1, p2, len1);
	}

	return l.eval(missing) == r.eval(missing);
}

double FunctionEQ::eval(bool& missing) const
{
	return equal(*args_[0], *args_[1], missing);
}

SQLExpression* FunctionEQ::simplify(bool& changed) 
{
	SQLExpression* x = FunctionExpression::simplify(changed);
	if(x) return x;

	ColumnExpression* a = dynamic_cast<ColumnExpression*>(args_[0]);
	ColumnExpression* b = dynamic_cast<ColumnExpression*>(args_[1]);

	if(a && b) {
		args_[0] = 0;
		args_[1] = 0;
		return FunctionFactory::instance().build("join",a,b);
	}

	//
	if(args_[0]->isConstant() && !args_[1]->isConstant())
        std::swap(args_[0],args_[1]);

	return 0;
}

bool FunctionEQ::useIndex()
{
	return args_[0]->indexed() && args_[1]->isConstant();
}

SQLIndex* FunctionEQ::getIndex(double*)
{
	bool missing = false;
	tmp_ = args_[1]->eval(missing);
	return args_[0]->getIndex(&tmp_);
}

} // namespace function
} // namespace expression
} // namespace sql
} // namespace odb

