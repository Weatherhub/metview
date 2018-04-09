/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "ecml/core/ExecutionContext.h"
#include "eckit/types/Types.h"

#include "odb_api/SQLInsert.h"

namespace odb {
namespace sql {

SQLInsert::SQLInsert(const InsertAST& a) 
: table_(a.table_),
  columns_(a.columns_),
  values_(a.values_)
{}

SQLInsert::~SQLInsert() {}

void SQLInsert::print(std::ostream& s) const {}

unsigned long long SQLInsert::execute(ecml::ExecutionContext* context)
{
    NOTIMP;
    return 0; // TODO:
}

expression::Expressions SQLInsert::output() const
{
    NOTIMP;
}

} // namespace sql 
} // namespace odb 


