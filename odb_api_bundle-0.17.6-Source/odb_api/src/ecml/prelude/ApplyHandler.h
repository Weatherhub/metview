/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */
/// @author Piotr Kuchta, February 2015

#ifndef eckit_ecml_ApplyHandler_H
#define eckit_ecml_ApplyHandler_H

#include "eckit/filesystem/PathName.h"
#include "ecml/parser/Request.h"
#include "ecml/core/SpecialFormHandler.h"

namespace ecml {

class ExecutionContext;

class ApplyHandler : public SpecialFormHandler {
public:
    ApplyHandler(const std::string&);

    virtual ecml::Request handle(const ecml::Request, ExecutionContext&);
};

} // namespace ecml

#endif
