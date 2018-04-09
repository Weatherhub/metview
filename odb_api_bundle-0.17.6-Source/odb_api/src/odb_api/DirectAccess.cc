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
/// @author Baudouin Raoult, Dec 2013

#include <time.h>
#include <sys/time.h>

#include "eckit/eckit.h"
#include "eckit/io/FileHandle.h"
#include "eckit/io/PartHandle.h"
#include "eckit/io/SharedHandle.h"
#include "eckit/log/Bytes.h"
#include "eckit/log/BigNum.h"

#include "eckit/log/Timer.h"
#include "odb_api/DirectAccess.h"
#include "odb_api/MetaDataReaderIterator.h"
#include "odb_api/Reader.h"
#include "odb_api/Select.h"

using namespace std;
using namespace eckit;

namespace odb {

DirectAccessBlock::~DirectAccessBlock()
{
    delete handle_;
    delete[] data_;
}

void DirectAccessBlock::unload() {
    delete handle_; handle_ = 0;
    delete[] data_; data_ = 0;
    unloads_ ++;
}


DirectAccess::DirectAccess(DataHandle &dh, const std::string& statement, size_t maxBlocksSize)
    : HandleHolder(dh),
      statement_(statement),
      current_(new DirectAccessIterator(*this)),
      row_(current_),
      maxBlocksSize_(maxBlocksSize),
      usedBlocksSize_(0),
      seq_(0)
{
    initBlocks();
}

DirectAccess::DirectAccess(DataHandle *dh, const std::string& statement, size_t maxBlocksSize)
    : HandleHolder(dh),
      statement_(statement),
      current_(new DirectAccessIterator(*this)),
      row_(current_),
      maxBlocksSize_(maxBlocksSize),
      usedBlocksSize_(0),
      seq_(0)
{
    initBlocks();
}

DirectAccess::DirectAccess(const std::string& path, const string &statement, size_t maxBlocksSize)
    : HandleHolder(new FileHandle(path)),
      statement_(statement),
      path_(path),
      current_(new DirectAccessIterator(*this)),
      row_(current_),
      maxBlocksSize_(maxBlocksSize),
      usedBlocksSize_(0),
      seq_(0)
{
    handle().openForRead();
    initBlocks();
}

void DirectAccess::initBlocks()
{
    eckit::Timer timer("DirectAccessIterator::initBlocks");
    IteratorProxy<MetaDataReaderIterator, DirectAccessIterator, const double> it(new MetaDataReaderIterator(handle(), true));
    IteratorProxy<MetaDataReaderIterator, DirectAccessIterator, const double> end(0);

    unsigned long long n = 0;
    size_t c = 0;
    for (; it != end; ++it)
    {
        const MetaData &md = it->columns();
        n += md.rowsNumber();
        blocks_.push_back(DirectAccessBlock(c++,
                                            md.rowsNumber(),
                                            it.iter_->blockStartOffset(),
                                            it.iter_->blockEndOffset() - it.iter_->blockStartOffset()
                                            ));
    }

    std::cout << "Rows " << BigNum(n) << std::endl;
    eckit::Timer t("DirectAccessIterator::initBlocks (index)");

    ASSERT(size_t(n) == n);
    index_.reserve(n);

    for(std::deque<DirectAccessBlock>::iterator j = blocks_.begin(); j != blocks_.end(); ++j) {
        DirectAccessBlock& b = *j;
        size_t n = 0;
        for(size_t i = 0; i < b.rows(); ++i) {
            index_.push_back(std::make_pair(&b, n));
            n++;
        }
    }

}


template<class Source>
void DirectAccess::readPart(DirectAccessBlock& b, Source& in)
{
    typename Source::iterator it = in.begin();
    typename Source::iterator end = in.end();

    const MetaData& md = it->columns();

    //std::cout << "SIZE " << md.size() << std::endl;
    //std::cout <<  md << std::endl;

    size_t width = md.size();
    size_t height = b.rows();


    b.size(width * height);
    b.width(width);

    usedBlocksSize_  += b.size();
    b.data(new double[b.size()]);
    b.metaData(md.clone());

    //eckit::Timer t("Read part");
    size_t n = 0;
    size_t off = 0;
    for(; it != end; ++it) {
        const double* d = it->data();
        std::copy(d, d+width, b.data() + off);
        n++;
        off += width;
/*
        if(n <5) {
            std::cout << "++++";
            for(size_t p = 0; p < width; p++) std::cout << " - " << d[p]; std::cout << std::endl;
        }*/
    }
    ASSERT(n == height); // This will happen if there is a 'where' clause
}

DirectAccess::row* DirectAccess::operator[](size_t n)
{

    ASSERT(n < index_.size());
    std::pair<DirectAccessBlock*, size_t>& e = index_[n];
    DirectAccessBlock* b = e.first;
    if(!b->handle()) {


        while(usedBlocksSize_ >= maxBlocksSize_) {
            // Unload blocks


            unsigned long long t = 0;
            std::deque<DirectAccessBlock>::iterator k;

            for(std::deque<DirectAccessBlock>::iterator j = blocks_.begin();
                j != blocks_.end(); ++j) {
                DirectAccessBlock& u = *j;
                if(u.handle()) {
                    if(t == 0 || u.last() < t) {
                        k = j;
                        t = u.last();
                    }
                }
            }

            ASSERT(t);
            usedBlocksSize_ -= (*k).size();
            (*k).unload();
            //std::cout << "UNLOAD " << (*k).n() << " maxBlocksSize " << maxBlocksSize_ << std::endl;

        }

        /*
        std::cout << "LOADING block " << b->n() << " at offset " << eckit::Bytes(b->offset()) << ", length "
                  <<  eckit::Bytes(b->length()) << std::endl;
        std::cout << "INDEX is " << n << " offset in block is " << e.second << std::endl;
        */
        b->handle(new PartHandle(new SharedHandle(handle()), b->offset(), b->length()));


    }

    if(!b->data())
    {
        if(statement_.length()) {
            Select in(statement_, *b->handle());
            readPart(*b, in);
        }
        else
        {
            Reader in(*b->handle());
            readPart(*b, in);
        }

    }

    b->last(++seq_) ;
    //std::cout << " ==== n = " << n << " idx " << e.second << std::endl;

/*
    {
        const double* d = b->data() + e.second;
        std::cout << "****";
        for(size_t p = 0; p < 10; p++) std::cout << " - " << d[p]; std::cout << std::endl;
    }*/

    idx_   = e.second * b->width();
    block_ = b;
    return &(*current_);

}


DirectAccess::~DirectAccess()
{
    /*

    std::cout << "BLOCKS : " << blocks_.size() << std::endl;
    for(std::deque<DirectAccessBlock>::iterator j = blocks_.begin(); j != blocks_.end(); ++j) {
        DirectAccessBlock& b = *j;
        if(b.loads())
            std::cout << "BLOCK " << b.n() << " loads: " << b.loads() << " unloads: " << b.unloads() << std::endl;
    }
    */

}


} // namespace odb
