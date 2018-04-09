/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File Prelude.h
// Piotr Kuchta - (c) ECMWF July 2015

#ifndef eckit_ecml_Prelude_H
#define eckit_ecml_Prelude_H

#include "ecml/core/Module.h"
#include "ecml/core/ExecutionContext.h"
#include "eckit/filesystem/PathName.h"

namespace ecml {

class Prelude : public Module {
public:
    Prelude();
    ~Prelude();
    void importInto(ExecutionContext&);

    static std::string preludePath();
private:
    void executePrelude(ExecutionContext&);
};

} // namespace ecml

#endif
