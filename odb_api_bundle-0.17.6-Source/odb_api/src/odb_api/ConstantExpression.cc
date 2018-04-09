/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "odb_api/ConstantExpression.h"

namespace odb {
namespace sql {
namespace expression {

ConstantExpression::ConstantExpression(double v, bool missing, const odb::sql::type::SQLType* type)
: value_(v), missing_(missing), type_(*type)
{}

ConstantExpression::~ConstantExpression() {}

void ConstantExpression::output(SQLOutput& o) const 
{ 
    type_.output(o, value_, missing_);
}

const type::SQLType* ConstantExpression::type() const { return &type_; }

} // namespace expression
} // namespace sql
} // namespace odb

