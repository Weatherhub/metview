/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "ecml/parser/Request.h"
#include "ecml/core/ExecutionContext.h"

#include "ParameterizedRequestHandler.h"

using namespace std;
using namespace eckit;

namespace ecml {

ParameterizedRequestHandler::ParameterizedRequestHandler(const string& name)
: RequestHandler(name)
{}

Values ParameterizedRequestHandler::handle(ExecutionContext& context)
{
    DynamicParametrisation params(context);
    vector<string> returnValues (handle(params));

    if (returnValues.size() == 0) 
        return new Cell("_list", "", 0, 0);

    Values rv(0);
    List list(rv);
    for (size_t i(0); i < returnValues.size(); ++i)
        list.append(returnValues[i]);
    return rv;
}

} // namespace ecml
