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
/// \file TextReader.h
///
/// @author Piotr Kuchta, Oct 2010

#ifndef odb_api_TextReader_H
#define odb_api_TextReader_H

#ifdef SWIGPYTHON
#include <Python.h>
#endif

#include "odb_api/IteratorProxy.h"

namespace eckit { class PathName; }

namespace odb {

class TextReaderIterator;

class TextReader
{
public:
	typedef IteratorProxy<TextReaderIterator,TextReader,double> iterator;
	typedef iterator::Row row;

	TextReader(std::istream &, const std::string& delimiter);
	TextReader(std::istream &, const std::string& delimiter, ecml::ExecutionContext*);
    TextReader(const std::string& path, const std::string& delimiter);
    TextReader(const std::string& path, const std::string& delimiter, ecml::ExecutionContext*);

	virtual ~TextReader();

	iterator begin();
	iterator end(); 

    std::istream& stream() { return *in_; }
	// For C API
	TextReaderIterator* createReadIterator(const eckit::PathName&);

#ifdef SWIGPYTHON
	iterator __iter__() { return begin(); }
#endif

	const std::string& delimiter() { return delimiter_; }
private:
// No copy allowed
    TextReader(const TextReader&);
    TextReader& operator=(const TextReader&);
	TextReader();

    std::istream* in_;
	bool deleteDataHandle_;
	const std::string path_;
	const std::string delimiter_;
    ecml::ExecutionContext* context_;

	friend class odb::IteratorProxy<odb::TextReaderIterator,odb::TextReader,double>;
	friend class odb::TextReaderIterator;
};

} // namespace odb

#endif
