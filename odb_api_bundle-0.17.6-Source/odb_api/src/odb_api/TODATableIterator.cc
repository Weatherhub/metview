/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

//#include "odb_api/odb_api.h"

#include "odb_api/ODAColumn.h"
//#include "odb_api/SQLDatabase.h"
//#include "odb_api/SQLType.h"
//#include "odb_api/TODATable.h"
//#include "odb_api/TODATableIterator.h"



namespace odb {
namespace sql {

template <typename T>
TODATableIterator<T>::TODATableIterator(Table &p, iterator reader, iterator end, double* data, const std::vector<odb::sql::SQLColumn*>& columns)
: parent(p),
  it_(reader),
  end_(end), 
  data_(data),
  columns_(columns),
  firstRow_(true)
{
	if (it_ != end_)
	{
		updateMetaData();
		copyRow();
	}
}

template <typename T>
void TODATableIterator<T>::rewind() {}

template <typename T>
TODATableIterator<T>::~TODATableIterator() {}

template <typename T>
bool TODATableIterator<T>::next()
{
	if (firstRow_) firstRow_ = false;
	else
		++it_;

	if (! (it_ != end_) )
		return false;

	if (it_->isNewDataset())
		updateMetaData();

	copyRow();
	return true;
}

template <typename T>
void TODATableIterator<T>::copyRow()
{
	size_t n = columns_.size();
	for(size_t i = 0; i < n; ++i)
		data_[i] = *static_cast<ODAColumn *>(columns_[i])->value(); //it_->data()[columns_[i]->index()];
}

template <typename T>
void TODATableIterator<T>::updateMetaData()
{
	parent.updateMetaData(columns_);
	data_ = parent.data_;

	size_t n = columns_.size();
	for(size_t i = 0; i < n; i++)
	{
		ODAColumn *odaColumn = dynamic_cast<ODAColumn *>(columns_[i]);
		//ASSERT(odaColumn);
		odaColumn->value(const_cast<double*>(it_->data()) + columns_[i]->index());
	}
}

} // namespace sql
} // namespace odb
