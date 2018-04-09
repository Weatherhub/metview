#!/bin/ksh

set -e
source use_odb.sh
set -x

cd DB

# (4) Compile and link Fortran90 application: (NOTE: already done by CMake)
odbf90 $1 -lDB -o populate.x

# (5) Run the application
$MPIEXEC_CMD ./populate.x DB

# (6) Validate the result
odbsql -q "select * from hdr,body" > populate.out
diff $2 populate.out
