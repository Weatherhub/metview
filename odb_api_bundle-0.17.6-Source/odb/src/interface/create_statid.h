INTERFACE
SUBROUTINE CREATE_STATID(CDSTATID,kstatid)
USE PARKIND1  ,ONLY : JPIM     ,JPRB
implicit none
character(len=*), intent(in) :: CDSTATID
INTEGER(KIND=JPIM), intent(out) :: kstatid
END SUBROUTINE CREATE_STATID
END INTERFACE