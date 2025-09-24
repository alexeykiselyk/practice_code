PROGRAM example1
! This is a comment. Comments in Fortran start with an exclamation mark (!)
    IMPLICIT NONE
    INTEGER :: hours, mins, secs, temp
    REAL :: x, y
    PRINT *, 'Type the hours, minutes and seconds'
    READ *, hours, mins, secs
    temp = 60*(hours*60 + mins) + secs
    PRINT *, 'Time in seconds =',temp

    print *, 'Now enter two numbers'
    read(*,*) x, y

    print *, 'The sum and product of the numbers are: ', x+y, x*y
    
END PROGRAM example1