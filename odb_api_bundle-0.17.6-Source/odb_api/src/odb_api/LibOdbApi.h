/*
 * (C) Copyright 1996-2017 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Simon Smart
/// @date   June 2017

#ifndef odb_api_LibOdbApi_H
#define odb_api_LibOdbApi_H

#include "eckit/system/Library.h"

namespace odb {

//----------------------------------------------------------------------------------------------------------------------

class LibOdbApi : public eckit::system::Library {
public:

    LibOdbApi();

    static const LibOdbApi& instance();

protected:

    const void* addr() const;

    virtual std::string version() const;

    virtual std::string gitsha1(unsigned int count) const;

};

//----------------------------------------------------------------------------------------------------------------------

} // namespace eckit

#endif // odb_api_LibOdbApi_H
