/*
 * © Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef odb_api_OldODBReader_H
#define odb_api_OldODBReader_H

#include "migrator/TSQLReader.h"
#include "migrator/ODBIterator.h"

namespace odb {
namespace tool {

typedef odb::tool::TSQLReader<ODBIterator> OldODBReader;

} // namespace tool 
} // namespace odb 

#endif
