/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// \file FunctionMATCH.h
/// Piotr Kuchta - ECMWF October 2015

#ifndef FunctionMATCH_H
#define FunctionMATCH_H

#include <vector>
#include <set>

#include "odb_api/FunctionExpression.h"
#include "odb_api/SQLType.h"
#include "odb_api/SQLAST.h"

namespace odb {
namespace sql {
namespace expression {
namespace function {

class FunctionMATCH : public FunctionExpression {
public:
    FunctionMATCH(const std::string&, const odb::sql::expression::Expressions&, const odb::sql::SelectAST&);
    FunctionMATCH(const FunctionMATCH&);
    ~FunctionMATCH();

    FunctionMATCH& operator=(const FunctionMATCH&);

    SQLExpression* clone() const;

    void collect(const std::vector<double>&);

private:
    size_t size_;
    const SelectAST subquery_;
    std::vector<std::vector<double> > subqueryResult_;

    virtual const odb::sql::type::SQLType* type() const;
    virtual double eval(bool& missing) const;
    virtual void prepare(SQLSelect& sql);

// -- Friends
	//friend std::ostream& operator<<(std::ostream& s,const FunctionMATCH& p)
	//	{ p.print(s); return s; }
};

} // namespace function
} // namespace expression 
} // namespace sql
} // namespace odb

#endif
