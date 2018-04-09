/// @file SQLDataSet.cc
/// @author Tomas Kral

#include "odb_api/SQLDataSet.h"

using namespace std;
using namespace eckit;

namespace odb {
namespace sql {

SQLDataSet::SQLDataSet()
  : SQLDatabase("anonymous")
{}

SQLDataSet::SQLDataSet(const std::string& name)
  : SQLDatabase(name)
{}

SQLDataSet::~SQLDataSet()
{}

void SQLDataSet::open()
{}

void SQLDataSet::close()
{
    SQLDatabase::close();
}

SQLTable* SQLDataSet::openDataHandle(DataHandle&, DataFormat)
{
    NOTIMP;
    return 0;
}

SQLTable* SQLDataSet::openDataStream(std::istream&, const std::string &, DataFormat)
{
    NOTIMP;
    return 0;
}

} // namespace sql
} // namespace odb
