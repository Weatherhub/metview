/// @file   DataLinks.cc
/// @author Tomas Kral

#include "eckit/exception/Exceptions.h"
#include "odb_api/DataLink.h"
#include "odb_api/DataLinks.h"

namespace odb {

DataLinks::DataLinks(DataSet& owner)
  : owner_(owner),
    links_()
{}

void DataLinks::insert(DataLink* link)
{
    ASSERT(link != 0 && "Null DataLink pointers are not allowed.");
    ASSERT(!links_.count(link) && "Duplicate DataLinks are not allowed.");
    ASSERT(!link->dataset() && "DataLink cannot be owned by other DataSet.");

    link->dataset(&owner_);
    links_.insert(link);
}

DataLinks::iterator DataLinks::find(const DataTable* parent,
        const DataTable* child)
{
    for (iterator it = links_.begin(), end = links_.end(); it != end; ++it)
    {
        DataLink& link = (**it);

        if (&link.parent() == parent && &link.child() == child)
            return it;
    }

    return links_.end();
}

} // namespace odb
