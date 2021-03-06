!===============================================================================
! Copyright 2005-2017 Intel Corporation All Rights Reserved.
!
! The source code,  information  and material  ("Material") contained  herein is
! owned by Intel Corporation or its  suppliers or licensors,  and  title to such
! Material remains with Intel  Corporation or its  suppliers or  licensors.  The
! Material  contains  proprietary  information  of  Intel or  its suppliers  and
! licensors.  The Material is protected by  worldwide copyright  laws and treaty
! provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
! modified, published,  uploaded, posted, transmitted,  distributed or disclosed
! in any way without Intel's prior express written permission.  No license under
! any patent,  copyright or other  intellectual property rights  in the Material
! is granted to  or  conferred  upon  you,  either   expressly,  by implication,
! inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
! property rights must be express and approved by Intel in writing.
!
! Unless otherwise agreed by Intel in writing,  you may not remove or alter this
! notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
! suppliers or licensors in any way.
!===============================================================================

!  Content:
!      F95 interface for LAPACK routines
!*******************************************************************************
! This file was generated automatically!
!*******************************************************************************

PURE SUBROUTINE SSTEIN_F95(D,E,W,IBLOCK,ISPLIT,Z,IFAILV,INFO)
    ! Fortran77 call:
    ! SSTEIN(N,D,E,M,W,IBLOCK,ISPLIT,Z,LDZ,WORK,IWORK,IFAILV,INFO)
    ! <<< Use statements >>>
    USE F77_LAPACK, ONLY: F77_STEIN, F77_XERBLA
    ! <<< Implicit statement >>>
    IMPLICIT NONE
    ! <<< Kind parameter >>>
    INTEGER, PARAMETER :: WP = KIND(1.0E0)
    ! <<< Scalar arguments >>>
    INTEGER, INTENT(OUT), OPTIONAL :: INFO
    ! <<< Array arguments >>>
    REAL(WP), INTENT(IN) :: D(:)
    REAL(WP), INTENT(IN) :: E(:)
    REAL(WP), INTENT(IN) :: W(:)
    INTEGER, INTENT(IN) :: IBLOCK(:)
    INTEGER, INTENT(IN) :: ISPLIT(:)
    REAL(WP), INTENT(OUT) :: Z(:,:)
    INTEGER, INTENT(OUT), OPTIONAL, TARGET :: IFAILV(:)
    ! <<< Local declarations >>>
    ! <<< Parameters >>>
    CHARACTER(LEN=5), PARAMETER :: SRNAME = 'STEIN'
    ! <<< Local scalars >>>
    INTEGER :: O_INFO
    INTEGER :: N
    INTEGER :: M
    INTEGER :: LDZ
    INTEGER :: L_STAT_ALLOC, L_STAT_DEALLOC
    ! <<< Local arrays >>>
    INTEGER, POINTER :: O_IFAILV(:)
    REAL(WP), POINTER :: WORK(:)
    INTEGER, POINTER :: IWORK(:)
    ! <<< Intrinsic functions >>>
    INTRINSIC MAX, PRESENT, SIZE
    ! <<< Executable statements >>>
    ! <<< Init optional and skipped scalars >>>
    LDZ = MAX(1,SIZE(Z,1))
    M = SIZE(Z,2)
    N = SIZE(D)
    ! <<< Init allocate status >>>
    L_STAT_ALLOC = 0
    ! <<< Allocate local and work arrays >>>
    IF(PRESENT(IFAILV)) THEN
        O_IFAILV => IFAILV
    ELSE
        ALLOCATE(O_IFAILV(M), STAT=L_STAT_ALLOC)
    ENDIF
    IF(L_STAT_ALLOC==0) THEN
        ALLOCATE(IWORK(N), STAT=L_STAT_ALLOC)
    ENDIF
    IF(L_STAT_ALLOC==0) THEN
        ALLOCATE(WORK(5*N), STAT=L_STAT_ALLOC)
    ENDIF
    ! <<< Call lapack77 routine >>>
    IF(L_STAT_ALLOC==0) THEN
        CALL F77_STEIN(N,D,E,M,W,IBLOCK,ISPLIT,Z,LDZ,WORK,IWORK,        &
     &                                                  O_IFAILV,O_INFO)
    ELSE; O_INFO = -1000
    ENDIF
    ! <<< Deallocate local and work arrays >>>
    IF(.NOT. PRESENT(IFAILV)) THEN
        DEALLOCATE(O_IFAILV, STAT=L_STAT_DEALLOC)
    ENDIF
    DEALLOCATE(IWORK, STAT=L_STAT_DEALLOC)
    DEALLOCATE(WORK, STAT=L_STAT_DEALLOC)
    ! <<< Error handler >>>
    IF(PRESENT(INFO)) THEN
        INFO = O_INFO
    ELSEIF(O_INFO <= -1000) THEN
        CALL F77_XERBLA(SRNAME,-O_INFO)
    ENDIF
END SUBROUTINE SSTEIN_F95
