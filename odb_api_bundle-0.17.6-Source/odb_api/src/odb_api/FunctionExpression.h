/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File FunctionExpression.h
// Baudouin Raoult - ECMWF Dec 03

#ifndef FunctionExpression_H
#define FunctionExpression_H

#include "odb_api/Expressions.h"

namespace odb {
namespace sql {
namespace expression {
namespace function {

class FunctionExpression : public SQLExpression {
public:
	FunctionExpression(const std::string&,const expression::Expressions&);
	FunctionExpression(const FunctionExpression&);
	~FunctionExpression();

    virtual void print(std::ostream& s) const;
	virtual void prepare(SQLSelect& sql);
	virtual void cleanup(SQLSelect& sql);
	virtual bool isConstant() const;
	virtual SQLExpression* simplify(bool&);
	//virtual double eval() const;
	bool isAggregate() const;
	void partialResult();

	virtual const odb::sql::type::SQLType* type() const;

	// For SQLSelectFactory (maybe it should just friend SQLSelectFactory).
	expression::Expressions& args() { return args_; }

protected:
	std::string name_;
	expression::Expressions args_;
    // void print(std::ostream&) const;

// -- Overridden methods

    void tables(std::set<SQLTable*>&);
private:
// No copy allowed
	//FunctionExpression(const FunctionExpression&);
	FunctionExpression& operator=(const FunctionExpression&);
};

} // namespace function
} // namespace expression 
} // namespace sql
} // namespace odb

#endif
