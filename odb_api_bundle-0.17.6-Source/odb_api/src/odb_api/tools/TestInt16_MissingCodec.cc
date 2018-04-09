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
/// @author Piotr Kuchta, ECMWF, Jan 2010

#include "eckit/log/Timer.h"
#include "odb_api/MetaData.h"
#include "odb_api/Reader.h"

#include "odb_api/Writer.h"
#include "MockReader.h"
#include "TestCase.h"

using namespace std;
using namespace eckit;
using namespace odb;


class MockReaderIterator3 
{
public:
	MockReaderIterator3()
    : noMore_(false), refCount_(0), columns_(1), nRows_(0), min_(23), data_(0), context_(0) 
	{
		odb::Column* col = columns_[0] = new odb::Column(columns_);
		ASSERT(col);

		col->name("column_name"); 
		col->type<DataStream<SameByteOrder, DataHandle> >(odb::INTEGER, false);
		col->hasMissing(true);
		next(context_);
	}

	odb::MetaData& columns() { return columns_; }

	bool isNewDataset() { return false; } 
	double* data() { return &data_; }
	
	//MockReaderIterator3& operator++() { next(); return *this; }

	const MockReaderIterator3& end() { return *reinterpret_cast<MockReaderIterator3*>(0); }

	bool next(ecml::ExecutionContext*)
	{
		if (noMore_) return noMore_;
		switch (nRows_++)
		{
			case 0:
				data_ = min_ + 0;
				break;
			case 1:
				data_ = min_ + (0xffff - 1) / 2;
				break;
			case 2:
				data_ = min_ + (0xffff - 1);
				break;
			case 3:
				data_ = columns_[0]->coder().missingValue();
				break;
			default:
				return !(noMore_ = true);
				break;
		}
		return true;
	}
	
	bool noMore_;
	int refCount_;
    ecml::ExecutionContext* context_;

private:
	odb::MetaData columns_;
	unsigned int nRows_;
	double min_;
	double data_;
};

static void setUp()
{
	Timer t("Writing test_int16_missing.odb");
	odb::Writer<> oda("test_int16_missing.odb");

	typedef tool::MockReader<MockReaderIterator3> M;
	M reader;
	M::iterator b = reader.begin();
	const M::iterator e = reader.end();

	odb::Writer<>::iterator outit = oda.begin();
	outit->pass1(b, e);
}

static void test()
{
	odb::Reader oda("test_int16_missing.odb");
	odb::Reader::iterator it = oda.begin();
	odb::Reader::iterator end = oda.end();

	typedef tool::MockReader<MockReaderIterator3> M;
	M reader;
	M::iterator originalIt = reader.begin();
	const M::iterator originalItEnd = reader.end();

	Log::info() << it->columns() << std::endl;
	
	for ( ; it != end; ++it, ++originalIt)
	{
		Log::info() << "it[0] = " << (*it)[0] << ", originalIt.data()[0]=" << (*originalIt)[0] << std::endl;
		ASSERT((*it)[0] == (*originalIt)[0]);
	}

	odb::codec::Codec& coder ( it->columns()[0]->coder() );

	string name = coder.name();

	Log::debug() << "test: codec name is '" << name << "'" << std::endl;

	ASSERT(name == "int16_missing");

	Log::debug() << "test: OK" << std::endl;
}


static void tearDown(){}

SIMPLE_TEST(Int16_MissingCodec)
