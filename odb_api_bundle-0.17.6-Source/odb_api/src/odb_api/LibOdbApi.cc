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

#include <algorithm>
#include <string>

#include "odb_api/LibOdbApi.h"

#include "odb_api/ODBAPIVersion.h"

namespace odb {

//----------------------------------------------------------------------------------------------------------------------

static LibOdbApi libodbapi;

LibOdbApi::LibOdbApi() : Library("odb_api") {}

const LibOdbApi& LibOdbApi::instance()
{
    return libodbapi;
}

const void* LibOdbApi::addr() const { return this; }

std::string LibOdbApi::version() const { return ODBAPIVersion::version(); }

std::string LibOdbApi::gitsha1(unsigned int count) const {
    std::string sha1(eckit_git_sha1());
    if(sha1.empty()) {
        return "not available";
    }

    return sha1.substr(0,std::min(count,40u));
}

//----------------------------------------------------------------------------------------------------------------------

} // namespace eckit

