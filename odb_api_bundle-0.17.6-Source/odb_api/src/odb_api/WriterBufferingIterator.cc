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
/// \file WriterBufferingIterator.cc
///
/// @author Piotr Kuchta, Feb 2009

#include "eckit/exception/Exceptions.h"
#include "odb_api/Writer.h"

#include "odb_api/WriterBufferingIterator.h"
#include <arpa/inet.h>

#include "odb_api/ODBAPISettings.h"
#include "odb_api/SQLAST.h"

inline size_t MEGA(size_t n) { return n*1024*1204; }

using namespace eckit;

namespace odb {

WriterBufferingIterator::WriterBufferingIterator(Owner &owner, DataHandle *dh, bool openDataHandle, const odb::sql::TableDef* tableDef)
: owner_(owner),
  columns_(0),
  lastValues_(0),
  nextRow_(0),
  nrows_(0),
  f(dh),
  encodedDataBuffer_(0),
  refCount_(0),
  properties_(),
  blockBuffer_(),
  rowsBuffer_(),
  nextRowInBuffer_(0),
  memoryDataHandle_(0),
  columnsBuffer_(0),
  rowsBufferSize_(owner.rowsBufferSize()),
  setvBuffer_(0),
  maxAnticipatedHeaderSize_( ODBAPISettings::instance().headerBufferSize() ),
  tableDef_(tableDef),
  path_(owner.path()),
  openDataHandle_(openDataHandle),
  initialisedColumns_(false)
{
	if (openDataHandle)	
		open();
}

WriterBufferingIterator::~WriterBufferingIterator()
{
	close();
	delete [] lastValues_;
	delete [] nextRow_;
	if (! openDataHandle_)	
        delete f;
}

unsigned long WriterBufferingIterator::gatherStats(const double* values, unsigned long count)
{
	ASSERT(count == columns().size());

	//for (size_t i = 0; i < columns_.size(); ++i) Log::info() << "gatherStats: columns_[" << i << "]=" << *columns_[i] << std::endl;

    for(size_t i = 0; i < count; i++) {
		columns_[i]->coder().gatherStats(values[i]);
    }

	return 0;
} 

template <typename DATASTREAM>
int WriterBufferingIterator::setOptimalCodecs()
{
	if (columnsBuffer_.size() == 0)
	{
		columnsBuffer_ = columns();
		columnsBuffer_.resetStats();
	}

	return codecOptimizer_.setOptimalCodecs<DATASTREAM>(const_cast<MetaData&>(columns()));
}

void WriterBufferingIterator::allocBuffers()
{
    delete [] lastValues_;
	delete [] nextRow_;
	int32_t colSize = columns().size();
	double* last = new double [colSize];
	lastValues_ = last;
	nextRow_ = new double [colSize];
	ASSERT(last);

    for (int i = 0; i < colSize; ++i) {

        // If we are trying to do anything before the writer is properly initialised ...
        ASSERT(columns_[i]->hasInitialisedCoder());

		nextRow_[i] = last[i] = columns_[i]->missingValue();
    }

	nrows_ = 0;

	encodedDataBuffer_.size(sizeof(uint16_t) + colSize * sizeof(double));
}

void WriterBufferingIterator::allocRowsBuffer()
{
	size_t nCols = columns().size();
	const size_t maxEncodedRowSize (sizeof(uint16_t) + nCols * sizeof(double));
	blockBuffer_.size(maxAnticipatedHeaderSize_ + rowsBufferSize_ * maxEncodedRowSize);
	rowsBuffer_.share(blockBuffer_ + maxAnticipatedHeaderSize_, rowsBufferSize_ * maxEncodedRowSize);

	memoryDataHandle_.buffer(rowsBuffer_);
	nextRowInBuffer_ = rowsBuffer_;
}

void WriterBufferingIterator::writeHeader()
{
	allocBuffers();
    for (size_t i = 0; i < columns_.size(); ++i) {

        // If we haven't configured a row, then this is bad
        ASSERT(columns_[i]->hasInitialisedCoder());

		columns_[i]->coder().resetStats();
    }
    initialisedColumns_ = true;
	//for (size_t i = 0; i < columns_.size(); ++i) Log::info() << "writeHeader: columns_[" << i << "]=" << *columns_[i] << std::endl;
}

bool WriterBufferingIterator::next(ecml::ExecutionContext* context)
{
    return writeRow(nextRow_, columns().size()) == 0;
}

double* WriterBufferingIterator::data() { return nextRow_; }
double& WriterBufferingIterator::data(size_t i)
{
	ASSERT(i >= 0 && i < columns().size());
	return nextRow_[i];
}

int WriterBufferingIterator::writeRow(const double* data, unsigned long nCols)
{
	ASSERT(nCols == columns().size());
    ASSERT(initialisedColumns_);

	if (rowsBuffer_ == 0)
		allocRowsBuffer();

	gatherStats(data, nCols);

    std::copy(data, data + nCols, reinterpret_cast<double*>(nextRowInBuffer_ + sizeof(uint16_t)));
	nextRowInBuffer_ += sizeof(uint16_t) + nCols * sizeof(double);

	ASSERT(nextRowInBuffer_ <= rowsBuffer_ + rowsBuffer_.size());

	if (nextRowInBuffer_ == rowsBuffer_ + rowsBuffer_.size())
		flush();

	return 0;
}

inline bool equal(const double* const v1, const double* const v2)
{
	for (size_t i=0; i < sizeof(double); ++i)
		if (reinterpret_cast<unsigned const char*>(v1)[i] != reinterpret_cast<unsigned const char*>(v2)[i])
			return false;
	return true;
}

unsigned char* WriterBufferingIterator::writeNumberOfRepeatedValues(unsigned char *p, uint16_t k)
{
	uint16_t nk (htons(k));
	unsigned char *pk (reinterpret_cast<unsigned char *>(&nk));
	*p++ = *pk++;
	*p++ = *pk;
	return p;
}

int WriterBufferingIterator::doWriteRow(const double* values, unsigned long count)
{
	if (lastValues_ == 0) allocBuffers();

	uint16_t k (0);
	for (; k < count && equal(&values[k], &lastValues_[k]); ++k)
		;

	unsigned char *p (encodedDataBuffer_);
	p = writeNumberOfRepeatedValues(p, k);

	for (size_t i = k; i < count; ++i) 
	{
		Column *col (columns_[i]);
		p = col->coder().encode(p, values[i]);
		lastValues_[i] = values[i];
	}

	DataStream<SameByteOrder, FastInMemoryDataHandle> f(memoryDataHandle_);
	f.writeBytes(encodedDataBuffer_.cast<char>(), p - encodedDataBuffer_);

	nrows_++;
	return 0;
} 

int WriterBufferingIterator::open()
{
	//Log::debug() << "WriterBufferingIterator::open@" << this << ": Opening data handle " << f << std::endl;
	ASSERT(f);

	Length estimatedLen = MEGA(20);
	f->openForWrite(estimatedLen);

	return 0;
}


int WriterBufferingIterator::setColumn(size_t index, std::string name, ColumnType type)
{
	//Log::debug() << "WriterBufferingIterator::setColumn: " << std::endl;
	ASSERT(index < columns().size());
	Column* col = columns_[index];
	ASSERT(col);

    // Ensure that this column is unique!
    for (size_t i = 0; i < columns_.size(); i++) {
        if (index != i && columns_[i] != 0) {
            if (columns_[i]->name() == name) {
                std::stringstream ss;
                ss << "Attempting to create multiple columns with the same name: " << name;
                throw SeriousBug(name, Here());
            }
        }
    }

	col->name(name); 
	col->type<DataStream<SameByteOrder, FastInMemoryDataHandle> >(type, false);
	return 0;
}

int WriterBufferingIterator::setBitfieldColumn(size_t index, std::string name, ColumnType type, BitfieldDef b)
{
	//Log::debug() << "WriterBufferingIterator::setBitfieldColumn: " << std::endl;
	ASSERT(index < columns().size());
	Column* col = columns_[index];
	ASSERT(col);

	col->name(name); 
	col->type<DataStream<SameByteOrder, FastInMemoryDataHandle> >(type, false);
    col->bitfieldDef(b);
	col->missingValue(0);
	return 0;
}

void WriterBufferingIterator::missingValue(size_t i, double missingValue)
{
	ASSERT(i < columns().size());
	Column* col = columns_[i];
	ASSERT(col);

	col->missingValue(missingValue);
}

void WriterBufferingIterator::flush()
{
	if (nextRowInBuffer_ == rowsBuffer_)
		return;
    
	setOptimalCodecs<DataStream<SameByteOrder, FastInMemoryDataHandle> >();

	unsigned long rowsWritten = 0;
	const size_t nCols = columns().size();
	for (unsigned char *pr = rowsBuffer_; pr < nextRowInBuffer_; pr += sizeof(uint16_t) + nCols * sizeof(double), ++rowsWritten)
		doWriteRow(reinterpret_cast<double *>(pr + sizeof(uint16_t)), nCols);

	InMemoryDataHandle bufferForHeader;
	doWriteHeader(bufferForHeader, memoryDataHandle_.position(), rowsWritten);

    Log::debug() << "WriterBufferingIterator::flush: header size: " << bufferForHeader.position() << std::endl;

	MemoryBlock buff(bufferForHeader.position());
	bufferForHeader.openForRead();
	bufferForHeader.read(buff, buff.size());

	if (buff.size() < maxAnticipatedHeaderSize_)
	{
		Log::debug() << "WriterBufferingIterator::flush: writing header and data in one go. "
			"Block size: " << buff.size() + memoryDataHandle_.position() << std::endl;

        std::copy(static_cast<unsigned char*>(buff), static_cast<unsigned char*>(buff) + buff.size(),
			memoryDataHandle_.buffer() - buff.size());
		this->f->write(memoryDataHandle_.buffer() - buff.size(),
			static_cast<size_t>(memoryDataHandle_.position()) + buff.size()); // Write encoded data
	}
	else
	{
		Log::info() << "WriterBufferingIterator::flush: writing header and data separately." << std::endl;

		this->f->write(buff, buff.size()); // Write header
		this->f->write(memoryDataHandle_.buffer(), memoryDataHandle_.position()); // Write encoded data
	}

	Log::debug() << "WriterBufferingIterator::flush: flushed " << rowsWritten << " rows." << std::endl;

	memoryDataHandle_.buffer(rowsBuffer_.cast<unsigned char>());

	nextRowInBuffer_ = rowsBuffer_;

    MetaData& md(const_cast<MetaData&>(columns()));
    md = columnsBuffer_;
    md.resetStats();
}


template <typename T>
void WriterBufferingIterator::doWriteHeader(T& dataHandle, size_t dataSize, size_t rowsNumber)
{
	//Log::debug() << "WriterBufferingIterator::doWriteHeader: dataSize=" << dataSize << ", rowsNumber=" << rowsNumber << std::endl;

	allocBuffers();

	//  FIXME: copy properties from input - props are not initialised now
	serializeHeader<SameByteOrder,T>(dataHandle, dataSize, rowsNumber, properties_, columns()); 
}

int WriterBufferingIterator::close()
{
	flush();

	if (!openDataHandle_ && f)
	{
		f->close();
		f = 0;
	}
	return 0;
}

std::vector<eckit::PathName> WriterBufferingIterator::outputFiles()
{
    std::vector<eckit::PathName> r;
    r.push_back(path_);
    return r;
}

} // namespace odb 

