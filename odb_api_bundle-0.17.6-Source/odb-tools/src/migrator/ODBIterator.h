/*
 * © Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef ODBIterator_H
#define ODBIterator_H

#include "eckit/filesystem/PathName.h"
#include "odb_api/SQLInteractiveSession.h"
#include "odb_api/ColumnType.h"

namespace eckit { class PathName; }
namespace eckit { class ExecutionContext; }

namespace odb { namespace sql { class SchemaAnalyzer; class SQLInteractiveSession; } }

namespace odb {

class MetaData;

namespace tool {

class ODBIterator 
{
public:
    ODBIterator(const std::string& db, const std::string& sql); 
    virtual ~ODBIterator ();

    void destroy();

    const ODBIterator& end() { return *reinterpret_cast<ODBIterator*>(0); }

    ODBIterator& operator++() { next(context_); return *this; }

    bool operator!=(const ODBIterator& o) {
        /* SDS: I have no idea what the purpose of this operator is,
         *      but returning uninitialised memory
         *      seems a bad plan. Check that it is never being used. */
        throw eckit::SeriousBug("Non-functional operator!= must never be called", Here());
        /*ASSERT(&o == 0); return hasNext_;*/
    }

    odb::MetaData& columns();

    virtual bool isNewDataset();
    virtual double* data();

    static eckit::PathName schemaFile(const eckit::PathName& db);

    virtual bool next(eckit::ExecutionContext*);

protected:
    int setColumn(unsigned long index, std::string& name, odb::ColumnType type, double missingValue);

private: // methods

	void createColumns();

    std::string defaultSQL(const eckit::PathName& db);
    const odb::sql::SchemaAnalyzer& getSchema(const eckit::PathName& db);

private: // members

	eckit::PathName db_;

	void *odbHandle_;
	int noOfColumns_;
	//colinfo_t *ci_;
	void *ci_;
	odb::MetaData *columns_;
	int newDataset_;
	double* data_;
	int nd_;

	bool schemaParsed_;
	odb::sql::SQLInteractiveSession session_;

	friend class FakeODBIterator;
	//friend class ReptypeGenIterator;

public: // members

	int refCount_;
	bool noMore_;
    eckit::ExecutionContext* context_;
};

} // namespace tool 
} // namespace odb 

#endif
