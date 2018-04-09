/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// \file UnitTest.h
///
/// @author Piotr Kuchta, ECMWF, Feb 2009

#include "eckit/config/Resource.h"
#include "eckit/log/CodeLocation.h"
#include "eckit/log/Log.h"

#include "odb_api/StringTool.h"
#include "TestCase.h"
#include "ToolFactory.h"

using namespace std;
using namespace eckit;
using namespace odb;

static void test()
{
	string e(Resource<std::string>("$ODB_API_TEST_DATA_PATH", string(""))); 
	if (e.size())
		Log::info() << "ODB_API_TEST_DATA_PATH=" << e << std::endl;
	string testDataPath = e.size() ? e : "../../../odb_api/src/migrator";

	string cmd;
	if (getenv("ODB_ROOT"))
	{
		cmd = std::string("rm -rf 2000010106 && gzip -d <") + testDataPath + "/2000010106.old.ECMA.tar.gz|tar xf - && ODB_COMPILER_FLAGS=`pwd`/2000010106/ECMA/ECMA.flags odb_migrator 2000010106/ECMA . 2000010106.odb";
	}
	else
	{
		Log::warning() << "UnitTest: ODB_ROOT not set, skipping testing of odb_migrator" << std::endl;

		cmd = std::string("rm -rf 2000010106 && gzip -d <") + testDataPath + "/2000010106.odb.gz >2000010106.odb";
	}
    odb::StringTool::shell(cmd.c_str(), Here());
}

static void setUp(){}

static void tearDown(){}


SIMPLE_TEST(AAAImportODB)
