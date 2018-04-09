/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

///
/// \file odb_api_tools_c.cc
///
/// @author Piotr Kuchta, September 2015

#include "odb_api/odb_api.h"

#include "odb_api/FastODA2Request.h"
#include "odb_api/MetaData.h"
#include "odb_api/MetaDataReader.h"
#include "odb_api/MetaDataReaderIterator.h"
#include "odb_api/ODAHandle.h"
#include "odb_api/ODBAPISettings.h"
#include "odb_api/ODBAPIVersion.h"
#include "odb_api/odbcapi.h"
#include "odb_api/Select.h"
#include "odb_api/Reader.h"
#include "odb_api/Writer.h"

using namespace eckit;
using namespace odb;

extern "C" {

int import_text(const char* text, const char* output_file)
{
    try {
        odb::tool::ImportTool::importText(text, output_file);
        return 0;
    } catch (Exception e) {
        return 1;
    }
}

} // extern "C" 

