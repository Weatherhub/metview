/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "odb_api/SQLDouble.h"
#include "odb_api/SQLOutput.h"

namespace odb {
namespace sql {
namespace type {

SQLDouble::SQLDouble(const std::string& name): SQLType(name) {}

SQLDouble::~SQLDouble() {}

size_t SQLDouble::size() const { return sizeof(double); }

void SQLDouble::output(SQLOutput& o, double d, bool m) const { o.outputDouble(d, m); }

} // namespace type 
} // namespace sql
} // namespace odb
