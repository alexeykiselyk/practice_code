PROGRAM example1
! This is a comment. Comments in Fortran start with an exclamation mark (!)
    IMPLICIT NONE
    INTEGER :: hours, mins, secs, temp
    PRINT *, 'Type the hours, minutes and seconds'
    READ *, hours, mins, secs
    temp = 60*(hours*60 + mins) + secs
    PRINT *, 'Time in seconds =',temp
END PROGRAM example1