/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File SQLOutput.h
// Baudouin Raoult - ECMWF Dec 03

#ifndef odb_api_SQLOutput_H
#define odb_api_SQLOutput_H

#include "ecml/core/ExecutionContext.h"

#include "odb_api/SQLOutputConfig.h"

namespace odb {
namespace sql {

namespace expression {
class Expressions;
}

class SQLSelect;

class SQLOutput {
public:
	SQLOutput();
	virtual ~SQLOutput(); 

	virtual void size(int) = 0;

	virtual void prepare(SQLSelect&) = 0;
	virtual void cleanup(SQLSelect&) = 0;

	virtual void reset() = 0;
	virtual void flush(ecml::ExecutionContext*) = 0;

	virtual bool output(const expression::Expressions&, ecml::ExecutionContext*) = 0;

	virtual void outputReal(double, bool) = 0;
	virtual void outputDouble(double, bool) = 0;
	virtual void outputInt(double, bool) = 0;
	virtual void outputUnsignedInt(double, bool) = 0;
	virtual void outputString(double, bool) = 0;
	virtual void outputBitfield(double, bool) = 0;

	virtual const SQLOutputConfig& config();
	virtual	void config(SQLOutputConfig&);

	virtual unsigned long long count() = 0;

protected:
	SQLOutputConfig config_;

	virtual void print(std::ostream&) const; 	

private:
// No copy allowed
	SQLOutput(const SQLOutput&);
	SQLOutput& operator=(const SQLOutput&);
// -- Friends
	friend std::ostream& operator<<(std::ostream& s,const SQLOutput& p)
		{ p.print(s); return s; }

};

} // namespace sql
} // namespace odb

#endif
