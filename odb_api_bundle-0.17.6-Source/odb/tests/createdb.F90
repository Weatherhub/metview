PROGRAM createdb
!*** createdb.F90 ***
USE odb_module
implicit none
INTEGER(4) :: myproc,nproc,npools,h
INTEGER(4) :: nrows, ncols, nra, rc
character(len=64) dbname
rc = ODB_init(myproc=myproc,nproc=nproc)
CALL getarg(1,dbname) ! Database name
npools = 1 ! Change this to a desired number
h = ODB_open(dbname,'NEW',npools)
rc = ODB_close(h,save=.TRUE.)
rc = ODB_end()
END PROGRAM createdb
