PROGRAM populate
!*** populate.F90 ***

  
USE odb_module

implicit none

REAL(8), ALLOCATABLE :: x(:,:)
REAL(8) :: statid(3), to_real8
REAL(8) mdi ! Missing data indicator ("NULL")
INTEGER(4) :: myproc,nproc,npools,jp,h
INTEGER(4) :: nrows, ncols, rc
character(len=64) dbname, tblname

rc = ODB_init(myproc=myproc,nproc=nproc)

CALL getarg(1,dbname)    ! Database name

npools = 0 ! Gets true value from ODB_open()

h = ODB_open(dbname,'OLD',npools)

mdi = abs(ODB_getval(h, '$mdi'))

jp = 1 ! Here: Populate poolno#1 only for now

if (myproc == mod(jp-1,nproc)+1) then
  tblname = '@hdr' ! Note '@'-sign in front of
  rc = ODB_getsize(h,tblname,nrows,ncols,poolno=jp)
  nrows = 3 ! Three new rows for TABLE hdr
  ALLOCATE(x(nrows,0:ncols))

  statid(1) = transfer("07027", to_real8)
  statid(2) = transfer("07061", to_real8)
  statid(3) = transfer("07075", to_real8)

  !              seqno       date     time     statid  ...
  !                ...     lat       lon  body.offset  body.len
  x(1,1:ncols) = (/1d0,20010101d0,100000d0,statid(1), &
               &       49.18d0,  -0.45d0,      0d0,         2d0/)
  x(2,1:ncols) = (/2d0,20010101d0,130000d0,statid(2), &
               &       49.82d0,   3.20d0,      2d0,         2d0/)
  x(3,1:ncols) = (/3d0,20010101d0,130000d0,statid(3), &
               &       49.78d0,   4.63d0,      4d0,         1d0/)

  ! Note: the following APPENDs after the existing data
  rc = ODB_put(h,tblname,x,nrows,ncols,poolno=jp)

  DEALLOCATE(x)

  tblname = '@body' ! Note '@'-sign in front of

  rc = ODB_getsize(h,tblname,nrows,ncols,poolno=jp)

  nrows = 5 ! Five new rows for TABLE body

  ALLOCATE(x(nrows,0:ncols))
  ! entryno, varno,     press,  obsvalue,    depar, obs_error, bias
  x(1,1:ncols) = &
    (/1d0,   110d0,  657.05d0,98530.00d0, -85.86d0,   69.03d0, -mdi/)
  x(2,1:ncols) = &
    (/2d0,    39d0,98530.00d0,  282.70d0,   1.80d0,    1.95d0, -mdi/)
  x(3,1:ncols) = &
    (/1d0,   110d0,  990.47d0,98480.00d0,-221.59d0,   69.09d0, -mdi/)
  x(4,1:ncols) = &
    (/2d0,    39d0,98480.00d0,  279.80d0,   1.06d0,    1.95d0, -mdi/)
  x(5,1:ncols) = &
    (/1d0,   110d0, 1451.38d0,98250.00d0,-123.32d0,   69.36d0, -mdi/)
  ! Note: the following APPENDs after the existing data

  rc = ODB_put(h,tblname,x,nrows,ncols,poolno=jp)

  DEALLOCATE(x)

endif

rc = ODB_close(h,save=.TRUE.)

rc = ODB_end()

END PROGRAM populate
