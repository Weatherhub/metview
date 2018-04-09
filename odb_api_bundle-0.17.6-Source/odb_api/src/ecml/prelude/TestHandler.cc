/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/types/Types.h"
#include "eckit/exception/Exceptions.h"
#include "eckit/parser/StringTools.h"
#include "ecml/parser/Request.h"

#include "ecml/core/ExecutionContext.h"
#include "ecml/core/Environment.h"
#include "ecml/core/Interpreter.h"
#include "ecml/core/SpecialFormHandler.h"

#include "TestHandler.h"

using namespace std;
using namespace ecml;

namespace ecml {

TestHandler::TestHandler(const string& name)
: SpecialFormHandler(name)
{}

/// Accepted parameters: label, do, expect
Request TestHandler::handle(const Request request, ExecutionContext& context)
{
    ASSERT(request->tag() == "_verb" && request->text() == "test");

    string label (request->valueAsString("label", "NO_LABEL"));
    Request code (request->valueOrDefault("do", 0));
    if (! code) throw eckit::UserError("No test code (keyword 'do') given for test '" + label + "'");
    Request expect (request->valueOrDefault("expect", 0));
    if (! expect) throw eckit::UserError("No expected value (keyword 'expect') given for test '" + label + "'");

    Values values (context.interpreter().eval(code, context));
    ASSERT(values);

    stringstream sv, se;
    sv << values;
    se << expect;

    if (sv.str() != se.str())
        throw eckit::UserError("ECML TEST '" + label + "' EXPECTED:[" + se.str() + "] GOT:[" + sv.str() + "]");

    return new Cell("_list", "", 0, 0);
}

} // namespace ecml

