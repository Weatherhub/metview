/*
 * (C) Copyright 1996-2013 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */
/// @author Piotr Kuchta, September 2015

#ifndef odb_api_Odb2NetcdfHandler_h
#define odb_api_Odb2NetcdfHandler_h

#include <sstream>

#include "ecml/parser/Request.h"
#include "ecml/core/RequestHandler.h"

class Odb2NetcdfHandler : public ecml::RequestHandler {
public:
    Odb2NetcdfHandler(const std::string&);
    virtual ecml::Values handle(ecml::ExecutionContext&);
};

#endif
