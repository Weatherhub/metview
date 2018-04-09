/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "FirstHandler.h"

#include "ecml/parser/Request.h"
#include "ecml/core/ExecutionContext.h"
#include "ecml/core/Environment.h"

namespace ecml {

FirstHandler::FirstHandler(const std::string& name) : RequestHandler(name) {}

Values FirstHandler::handle(ExecutionContext& context)
{
    Values vs (context.environment().lookup("of"));
    return new Cell("_list", "", Cell::clone(vs->value()), 0);
}

} // namespace ecml
