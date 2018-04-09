/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File SQLType.h
// Baudouin Raoult - ECMWF Dec 03

#ifndef SQLType_H
#define SQLType_H

#include "eckit/eckit.h"

namespace odb {
namespace sql {

class SQLOutput;

namespace type {

class SQLType {
public:

	enum {
		realType    = 0,
		integerType = 1,
		stringType  = 2,
		bitmapType  = 3,
		blobType    = 4,
		doubleType  = 5
	};

	SQLType(const std::string&);

	/// Constructor used when defining a bitfield.
	SQLType(const std::string&, const std::string&);

	virtual ~SQLType(); 

	const std::string& name() const { return name_; }

	virtual size_t size() const = 0;
	virtual void output(SQLOutput&, double, bool) const = 0;
	virtual const SQLType* subType(const std::string&) const;

	virtual int getKind() const = 0;

	// Formating functions (used by SQLSimpleOutput)
	virtual size_t width() const;
	typedef std::ios_base& (*manipulator)(std::ios_base&);
	virtual manipulator format() const;

	static const SQLType& lookup(const std::string&);
	static void createAlias(const std::string&, const std::string&);
    static SQLType* registerType(SQLType*);

protected:
    virtual void print(std::ostream&) const;
	static bool exists(const std::string&);

private:
// No copy allowed
	SQLType(const SQLType&);
	SQLType& operator=(const SQLType&);

	std::string name_;

    friend std::ostream& operator<<(std::ostream& s,const SQLType& p)
		{ p.print(s); return s; }
};

class DynamicallyCreatedTypesDestroyer {
public:
	static SQLType* registerType(SQLType*);
	~DynamicallyCreatedTypesDestroyer ();
};

} // namespace type 
} // namespace sql
} // namespace odb

#endif