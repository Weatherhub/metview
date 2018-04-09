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

const double EPS =   7e-6;

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
	Timer t("Test eq_boxlat and eq_boxlon functions");
	odb::Writer<> oda("test_eq_box.odb");

	odb::Writer<>::iterator row = oda.begin();
	row->setNumberOfColumns(2);

	row->setColumn(0, "lat", odb::REAL);
	row->setColumn(1, "lon", odb::REAL);
	
	row->writeHeader();

	(*row)[0] = 45.0;
	(*row)[1] = 5.0;

    ++row;
}

static void tearDown() 
{ 
	PathName("test_eq_box.odb").unlink();
}

static void test()
{
    const string sql = "select eq_boxlat(lat,lon,10.5), eq_boxlon(lat,lon,10.5) from \"test_eq_box.odb\";";

	Log::info() << "Executing: '" << sql << "'" << std::endl;

	odb::Select oda(sql);
	odb::Select::iterator it = oda.begin();

	ASSERT(fabs((*it)[0] - 47.134066345052e0)<EPS); // 
	ASSERT((*it)[1] == 0); // 

}


SIMPLE_TEST(FunctionEqBox)
