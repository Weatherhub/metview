/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File ShiftedColumnExpression.h
// Piotr Kuchta - ECMWF Dec 2012
#ifndef ShiftedColumnExpression_H
#define ShiftedColumnExpression_H

namespace odb {
namespace sql {

class SQLOutput;

namespace expression {

template <typename T>
class ShiftedColumnExpression : public T {
public:
	ShiftedColumnExpression(const std::string&, SQLTable*, int shift, int nominalShift, int begin = -1, int end = -1);
	ShiftedColumnExpression(const std::string&, const std::string& tableReference, int shift, int nominalShift, int begin = -1, int end = -1);
	ShiftedColumnExpression(const ShiftedColumnExpression&);
	ShiftedColumnExpression(const T& o, int shift, int nominalShift);

	// for bitfields columns
	ShiftedColumnExpression(const std::string& name, const std::string& field, SQLTable* table, int shift, int nominalShift);
	ShiftedColumnExpression(const std::string& name, const std::string& field, const std::string& tableReference, int shift, int nominalShift);


	~ShiftedColumnExpression(); 

	SQLTable* table() { return this->table_; }

	double* current() { NOTIMP; return &(this->value_->first); }

	SQLExpression* clone() const;

	int shift() { return shift_; }
	int nominalShift() { return nominalShift_; }

protected:
	int	                   shift_; // For the HASH operator
	int	                   nominalShift_; // For the HASH operator

// -- Overridden methods
	virtual void print(std::ostream& s) const;
	virtual void cleanup(SQLSelect& sql);
	virtual double eval(bool& missing) const;
	virtual void output(SQLOutput& s) const;

private:
	ShiftedColumnExpression& operator=(const ShiftedColumnExpression&);

	void allocateCircularBuffer();
    std::list<std::pair<double,bool> > oldValues_;

// -- Overridden methods
	//friend std::ostream& operator<<(std::ostream& s,const ShiftedColumnExpression& p)
	//	{ p.print(s); return s; }
};

} // namespace expression 
} // namespace sql
} // namespace odb 

#include "odb_api/ShiftedColumnExpression.cc"

#endif
