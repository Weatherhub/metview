PROGRAM querydata
!*** querydata.F90 ***
USE odb_module
implicit none
REAL(8), ALLOCATABLE :: x(:,:)
INTEGER(4) :: myproc,nproc,npools,jp,h
INTEGER(4) :: nrows, ncols, nra, rc
INTEGER(4) :: numargs, iargc, jque, jr, jc, nc
character(len=64) dbname, queryname
character(len=64), allocatable :: colnames(:)
rc = ODB_init(myproc=myproc,nproc=nproc)
numargs = iargc()
if (numargs < 1) then
  CALL ODB_abort('querydata',&
  'Usage: querydata DBname [query1 [query2] ...]',numargs)
endif
CALL getarg(1,dbname)    ! Database name
do jque=2,numargs
  CALL getarg(jque,queryname) ! Query name
  npools = 0 ! Gets true value from ODB_open()
  h = ODB_open(dbname,'READONLY',npools)
  write(*,*)'Exec query#',jque-1,'="'//trim(queryname)//'"'
  rc = ODB_addview(h,queryname) ! Not necessary anymore
  nc = ODB_getnames(h,queryname,'name')
  ALLOCATE(colnames(nc))
  nc = ODB_getnames(h,queryname,'name',colnames)
  do jp=myproc,npools,nproc ! Round-robin, "my" pools only
    rc = ODB_select(h,queryname,nrows,ncols,nra=nra,poolno=jp)
    if (nrows > 0) then
      ALLOCATE(x(nra,0:ncols))
      rc = ODB_get(h,queryname,x,nrows,ncols,poolno=jp)
      write(*,'((3a20))') (trim(colnames(jc)),jc=1,nc)
      do jr=1,nrows
        write(*,'(1p,(5x,3(1x,g20.10)))') x(jr,1:ncols)
      enddo
      DEALLOCATE(x)
    endif
    rc = ODB_cancel(h,queryname,poolno=jp)
    ! The following is the same as the less preferred
    ! rc = ODB_swapout(h,'*',poolno=jp)
    rc = ODB_release(h,poolno=jp)
  enddo ! do jp=myproc,npools,nproc
  DEALLOCATE(colnames)
  rc = ODB_close(h)
enddo ! do jque=2,numargs
rc = ODB_end()
END PROGRAM querydata
