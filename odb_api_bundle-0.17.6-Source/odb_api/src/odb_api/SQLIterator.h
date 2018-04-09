/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File SQLIterator
// Baudouin Raoult - ECMWF Dec 03

#ifndef SQLIterator_H
#define SQLIterator_H

#include "eckit/memory/MemoryPool.h"
#include "odb_api/SQLType.h"

namespace odb {
namespace sql {

// Forward declarations
class SQLIterator {
public:

    void *operator new(size_t s)          { return eckit::MemoryPool::fastAllocate(s);}
	//void *operator new(size_t s,void *p)  { return p;                          }
    void operator delete(void* p)         { eckit::MemoryPool::fastDeallocate(p);     }

	SQLIterator(const type::SQLType& type): type_(type) {}

    virtual ~SQLIterator() {} 

	const type::SQLType& type() const { return type_; }

	virtual void rewind()  = 0;
	virtual double next(bool& missing)                = 0;
	virtual void advance(unsigned long) = 0;

	virtual void load()   {}
	virtual void unload() {}

protected:
	const type::SQLType& type_;
	
	virtual void print(std::ostream&) const = 0; 	

private:
// No copy allowed

	SQLIterator(const SQLIterator&);
	SQLIterator& operator=(const SQLIterator&);

	friend std::ostream& operator<<(std::ostream& s,const SQLIterator& p)
		{ p.print(s); return s; }
};

} // namespace sql
} // namespace odb

#endif
