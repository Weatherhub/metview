/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */
/// @author Piotr Kuchta, May 2015

#ifndef eckit_ecml_PrintHandler_H
#define eckit_ecml_PrintHandler_H

#include <sstream>

#include "ecml/parser/Request.h"
#include "ecml/core/RequestHandler.h"

namespace ecml {

class PrintHandler : public ecml::RequestHandler {
public:
    PrintHandler(const std::string&, const std::string&, std::ostream&);
    PrintHandler(const std::string&, const std::string&);
    virtual Values handle(ExecutionContext&);

    static void printList(std::ostream&, Values, const std::string& separator, const std::string& end);

protected:
    std::ostream& out() { return *out_; }
    void out(std::ostream& o) { out_ = &o; }

private:
    const std::string end_;
    std::ostream* out_;
};

} // namespace ecml

#endif
