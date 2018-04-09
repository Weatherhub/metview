#!/bin/ksh

set -e
source use_odb.sh
set -x

# (0) Go to directory where DB.ddl sits
# This will become (by default) your database directory
rm -fr DB
mkdir -p DB
cd DB

# (1) Compile database DB (once in the lifetime):
cp $2 .
newodb DB

# (2) Run setup to get the IOASSIGN right:
./DB.setup > DB.IOASSIGN

# (3) Make sure to get the database directories right:
export ODB_DATAPATH_DB=`pwd`
export ODB_SRCPATH_DB=`pwd`

# (4) Compile and link Fortran90 application: (NOTE: already done by CMake)
odbf90 $1 -lDB -o createdb.x

# (5) Run the application
$MPIEXEC_CMD ./createdb.x DB

# (6) Validate the result
odbsql -q "select count(*) from hdr" > createdb.out
diff $3 createdb.out

# FIXME: Wait for (at least) one second before running a next test to avoid issues with
# DCA files caching in odbsql script.
sleep 1.1
