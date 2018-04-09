/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File Decoder.h
// Baudouin Raoult - ECMWF Dec 03

#ifndef Decoder_H
#define Decoder_H


namespace odb {

class Decoder {
public:
	typedef long long W;

	static W makeMask(W);
	static void printBinary(std::ostream&, W);
	static std::string printBinary(W);

    static void printHexadecimal(std::ostream&, W);
	static std::string printHexadecimal(W);
};

} // namespace odb 

#endif
