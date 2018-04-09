/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// \file UnitTest.cc
///
/// @author ECMWF, July 2010

const double EPS =     4e-5;

#include <cmath>

#include "eckit/log/Timer.h"
#include "odb_api/Select.h"

#include "odb_api/Writer.h"
#include "TestCase.h"

using namespace std;
using namespace eckit;
using namespace odb;



static void setUp()
{
	Timer t("Test Dotp function");
	odb::Writer<> oda("test_dotp.odb");

	odb::Writer<>::iterator row = oda.begin();
	row->setNumberOfColumns(2);

	row->setColumn(0, "x", odb::REAL);
	row->setColumn(1, "y", odb::REAL);
	
	row->writeHeader();

	(*row)[0] = 3.0;
	(*row)[1] = 2.0;
    ++row;
	(*row)[0] = 7.5;
	(*row)[1] = 112.0;
    ++row;
	(*row)[0] = 93.7;
	(*row)[1] = 12.3;
    ++row;
}

static void tearDown() 
{ 
	PathName("test_dotp.odb").unlink();
}

static void test()
{
    const string sql = "select dotp(x,y) from \"test_dotp.odb\";";

	Log::info() << "Executing: '" << sql << "'" << std::endl;

	odb::Select oda(sql);
	odb::Select::iterator it = oda.begin();

	ASSERT(fabs((*it)[0] - 1998.51e0)<EPS); // 

}



SIMPLE_TEST(FunctionDotp)
