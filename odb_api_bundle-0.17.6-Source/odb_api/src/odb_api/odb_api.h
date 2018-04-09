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
/// \file odb_api.h
///
/// @author Piotr Kuchta, Feb 2009

#ifndef PUBLIC_ODB_API_H
#define PUBLIC_ODB_API_H

#include "odb_api/MetaData.h"
#include "odb_api/Column.h"
#include "odb_api/Select.h"
#include "odb_api/ColumnType.h"
#include "odb_api/Reader.h"
#include "odb_api/TextReader.h"
#include "odb_api/Writer.h"

// For importing data from text - used by examples and tests
#include "odb_api/tools/ImportTool.h"

// For importing data from text - used by examples and tests
#include "odb_api/tools/ImportTool.h"

// For ECML support
#include "ecml/core/ExecutionContext.h"
#include "ecml/core/Environment.h"
#include "ecml/core/RequestHandler.h"
#include "ecml/parser/RequestParser.h"
#include "ecml/parser/Cell.h"
#include "odb_api/ODBModule.h"
#include "odb_api/ecml_data/ResultSet.h"
#include "odb_api/ecml_data/ResultSetStore.h"

// Exceptions.
#include "eckit/exception/Exceptions.h"

#endif
