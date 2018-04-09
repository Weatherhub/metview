/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/types/Types.h"

#include "odb_api/FunctionEQ.h"
#include "odb_api/FunctionMATCH.h"
#include "odb_api/SQLMATCHSubquerySession.h"
#include "odb_api/SQLStatement.h"
#include "odb_api/SQLSelect.h"

#include <vector>
#include <algorithm>

namespace odb {
namespace sql {
namespace expression {
namespace function {

using namespace eckit;
using namespace std;

FunctionMATCH::FunctionMATCH(const std::string& name, const expression::Expressions& args, const SelectAST& selectAST)
: FunctionExpression(name, args),
  size_(args.size()),
  subquery_(selectAST),
  subqueryResult_()
{}

FunctionMATCH::FunctionMATCH(const FunctionMATCH& other)
: FunctionExpression(other.name_, other.args_),
  size_(other.args_.size()),
  subquery_(other.subquery_),
  subqueryResult_(other.subqueryResult_)
{}

FunctionMATCH::~FunctionMATCH() {}

void FunctionMATCH::prepare(SQLSelect& sql)
{
    FunctionExpression::prepare(sql);

    SQLMATCHSubquerySession session(*this);
    SQLSelect* select(session.selectFactory().create(session, subquery_));
    session.execute(dynamic_cast<SQLStatement&>(*select), (ecml::ExecutionContext*) 0);

    std::stable_sort(subqueryResult_.begin(), subqueryResult_.end());
}

FunctionMATCH& FunctionMATCH::operator=(odb::sql::expression::function::FunctionMATCH const&)
{
    // TODO:
    NOTIMP;
    return *this;
}

void FunctionMATCH::collect(const std::vector<double>& v)
{
    subqueryResult_.push_back(v);
}

const type::SQLType* FunctionMATCH::type() const { return &type::SQLType::lookup("real"); } //TODO: bool?

SQLExpression* FunctionMATCH::clone() const { return new FunctionMATCH(*this); }

double FunctionMATCH::eval(bool& missing) const
{
    std::vector<double> vs (size_);
    for (size_t i(0); i < size_; ++i)
    {
        bool missing (false);
        vs[i] = args_[i]->eval(missing);
    }
    return std::binary_search(subqueryResult_.begin(), subqueryResult_.end(), vs);
}

} // namespace function
} // namespace expression
} // namespace sql
} // namespace odb 
