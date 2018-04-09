/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "odb_api/SQLOutput.h"

namespace odb {
namespace sql {

SQLOutput::SQLOutput() {}

SQLOutput::~SQLOutput() {}

void SQLOutput::print(std::ostream& s) const
{
	s << "SQLOutput" << std::endl;
}

const SQLOutputConfig& SQLOutput::config() { return config_; }

void SQLOutput::config(SQLOutputConfig& cfg) { config_ = cfg; }

} // namespace sql
} // namespace odb
