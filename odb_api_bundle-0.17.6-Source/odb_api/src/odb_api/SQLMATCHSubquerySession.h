/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File SQLMATCHSubquerySession.h
// Piotr Kuchta - ECMWF Octover 2015

#ifndef SQLMATCHSubquerySession_H
#define SQLMATCHSubquerySession_H

#include "odb_api/SQLSession.h"

namespace eckit { class ExecutionContext; }
namespace odb { class ReaderIterator; }
namespace odb { class SelectIterator; }
namespace odb { namespace sql { namespace expression { namespace function { class FunctionMATCH; } } } }

namespace odb {
namespace sql {

class SQLMATCHSubquerySession : public SQLSession {
public:
	SQLMATCHSubquerySession(expression::function::FunctionMATCH &);
	~SQLMATCHSubquerySession(); 

	SQLStatement* statement();

private:
// No copy allowed
	SQLMATCHSubquerySession(const SQLMATCHSubquerySession&);
	SQLMATCHSubquerySession& operator=(const SQLMATCHSubquerySession&);

	SQLStatement* statement_;
    expression::function::FunctionMATCH& f_;

// -- Overridden methods
	void statement(SQLStatement*);
	SQLOutput* defaultOutput();

// -- Friends
	//friend std::ostream& operator<<(std::ostream& s,const SQLMATCHSubquerySession& p)
	//	{ p.print(s); return s; }

};

} // namespace sql
} // namespace odb

#endif
