#!/bin/sh

set -uex

which odb_migrator

# A unique working directory

wd=$(pwd)
test_wd=$(pwd)/test_import_odb_wd

if [ -d ${test_wd} ]; then
    rm -rf ${test_wd}
fi

mkdir ${test_wd}
cd ${test_wd}

# Extract the test data

tar xfz ${ODB_API_TEST_DATA_PATH}/2000010106.old.ECMA.tar.gz

export ODB_COMPILER_FLAGS=`pwd`/2000010106/ECMA/ECMA.flags

if [ -z ${ODB_ROOT:=""} ]; then

    echo "ODB_ROOT not set"
    exit -1

else

    # Runs its own verification step
    odb_migrator 2000010106/ECMA . 2000010106.odb

fi

# Clean up

cd ${wd}
rm -rf ${test_wd}

