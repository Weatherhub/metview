/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include <ostream>

#include "eckit/eckit.h"
#include "eckit/io/Offset.h"
#include "eckit/io/Length.h"

#include "odb_api/MetaData.h"
#include "odb_api/Reader.h"
#include "odb_api/Select.h"
#include "odb_api/Block.h"

using namespace eckit;
using namespace std;

namespace odb {

std::string Block::str() const
{
    stringstream ss;
    ss << *this;
    return ss.str();
}

ostream& operator<< (ostream& o, const Block& b)
{
    o << "block,file=\"" << b.fileName << "\","
      << "start=" << b.start << ","
      << "end=" << b.end << ","
      << "firstRow=" << b.firstRow << ","
      << "lastRow=" << b.lastRow 
      ;
    return o;
}

} // namespace odb 

