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
/// \file ODA.cc
///
/// @author Piotr Kuchta, Feb 2009

#include "ecml/data/DataHandleFactory.h"
#include "odb_api/Reader.h"

using namespace std;
using namespace eckit;

namespace odb {

Reader::Reader(DataHandle &dh)
: dataHandle_(&dh),
  deleteDataHandle_(false),
  context_(0)
{}

Reader::Reader(DataHandle &dh, ecml::ExecutionContext* context)
: dataHandle_(&dh),
  deleteDataHandle_(false),
  context_(context)
{}

Reader::Reader()
: dataHandle_(0),
  deleteDataHandle_(true),
  path_(""),
  context_(0)
{}

Reader::Reader(ecml::ExecutionContext* context)
: dataHandle_(0),
  deleteDataHandle_(true),
  path_(""),
  context_(context)
{}

Reader::Reader(const std::string& path, ecml::ExecutionContext* context)
: dataHandle_(ecml::DataHandleFactory::openForRead(path)),
  deleteDataHandle_(true),
  path_(path),
  context_(context)
{}

Reader::Reader(const std::string& path)
: dataHandle_(ecml::DataHandleFactory::openForRead(path)),
  deleteDataHandle_(true),
  path_(path),
  context_(0)
{}

Reader::~Reader()
{
    if (dataHandle_ && deleteDataHandle_)
    {
        dataHandle_->close();
        delete dataHandle_;
    }
}

ReaderIterator* Reader::createReadIterator(const PathName& pathName)
{
    return new ReaderIterator(*this, pathName);
}

ReaderIterator* Reader::createReadIterator()
{
return createReadIterator(path_);
}

Reader::iterator Reader::begin()
{
    ReaderIterator * it = new ReaderIterator(*this);
    it->next(context_);
    return iterator(it);
}

const Reader::iterator Reader::end() { return iterator(0); }

void Reader::noMoreData()
{
    if (dataHandle_ && deleteDataHandle_)
    {
        dataHandle_->close();
        delete dataHandle_;
    }
    dataHandle_ = 0;
}

eckit::DataHandle* Reader::dataHandle() 
{
    // Assume the Reader was constructed with a path, and not a DataHandle*
    if (! dataHandle_)
        dataHandle_ = ecml::DataHandleFactory::openForRead(path_);
    return dataHandle_; 
}

} // namespace odb
