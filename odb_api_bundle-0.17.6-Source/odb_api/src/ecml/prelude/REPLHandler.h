/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */
/// @author Piotr Kuchta, August 2015

#ifndef eckit_ecml_REPLHandler_H
#define eckit_ecml_REPLHandler_H

#include "eckit/eckit_config.h"

#include "eckit/filesystem/PathName.h"
#include "ecml/parser/Request.h"
#include "ecml/core/SpecialFormHandler.h"
#include "ecml/core/ExecutionContext.h"

namespace ecml {

class REPLHandler : public SpecialFormHandler {
public:
    REPLHandler(const std::string&);
    virtual ecml::Request handle(const ecml::Request, ExecutionContext&);

    static void repl(ExecutionContext&);

private:
    static std::string readLine(ExecutionContext&);
    static void readHistory();
    static std::string historyFile();
    static void writeHistory();

    static bool showResultGraph(ExecutionContext&);
};

} // namespace ecml


#endif
