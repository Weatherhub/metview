/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// \file TestIntegerValues.h
///
/// @author Piotr Kuchta, ECMWF, Jan 2011

#include "eckit/filesystem/PathName.h"
#include "odb_api/Reader.h"

#include "ImportTool.h"

#include "TestCase.h"





using namespace std;
using namespace eckit;
using namespace odb;

static void setUp()
{
	const char* data =
	"date:REAL\n"
	"20101130\n"
	"20101201\n"
	"20101202\n";
    odb::tool::ImportTool::importText(data, "TestIntegerValues.odb");
}


static void test()
{
	//Log::info() << fixed;
 //////////////////////////////           ODB from MARS             //////////////////////////////    

    const std::string fileNameOdb="TestIntegerValues.odb";

	odb::Reader odb(fileNameOdb);
	odb::Reader::iterator it = odb.begin();

	for (unsigned int i=0; i < it->columns().size(); ++i) {
		std::cout << "Name = " << it->columns()[i]->name() << " " ;
	}

	std::cout << std::endl;
	int nrows=0;
	for(; it != odb.end(); ++it)
	{
		++nrows;
		for (size_t i=0; i < it->columns().size(); ++i)
		{
			//float nr = ((*it)[i]); /// <- WRONG!
			double nr = ((*it)[i]);
			switch(it->columns()[i]->type())
			{
			case odb::INTEGER:
			case odb::BITFIELD:
				std::cout <<  static_cast<int>(nr) << " ";
				//cout <<  "* should be: " << it->integer(i) << " ";
				break;
			case odb::REAL:
				std::cout <<  nr << " ";
				break;
			case odb::IGNORE:
			default:
				ASSERT("Unknown type" && false);
				break;
			}
 		}
 		std::cout << std::endl;
	}
}

static void tearDown() { }


SIMPLE_TEST(IntegerValues)
