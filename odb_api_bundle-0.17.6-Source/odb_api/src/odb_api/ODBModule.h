/*
 * (C) Copyright 1996-2013 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File ODBModule.h
// Piotr Kuchta - (c) ECMWF May 2015

#ifndef odb_api_ODBModule_H
#define odb_api_ODBModule_H

#include "ecml/core/Module.h"
#include "ecml/core/ExecutionContext.h"

namespace odb {

class ODBModule : public ecml::Module {
public:
    ODBModule();
    ~ODBModule();
    void importInto(ecml::ExecutionContext&);
};

}  // namespace odb

#endif
