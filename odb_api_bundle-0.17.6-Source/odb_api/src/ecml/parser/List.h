/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Piotr Kuchta - ECMWF March 2015

#ifndef eckit_parser_List_H
#define eckit_parser_List_H

#include <string>
#include <list>
#include <vector>
#include <map>
#include <ostream>

#include "ecml/parser/Cell.h"

namespace ecml {

class List {
public:
    List(Cell*&);
    List();

    size_t size() const;
    List& append(Cell*);
    List& append(const std::string&);

    operator Cell*() const { return cell_; }

    std::ostream& print(std::ostream&) const;

private:
    Cell* p_;
    Cell*& cell_;

    friend std::ostream& operator<<(std::ostream& s, const List& l) { return l.print(s); }
};

} // namespace ecml

#endif
