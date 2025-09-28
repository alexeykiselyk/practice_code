program flow_control
    implicit none
    integer :: i, j
    real, parameter :: pi = 3.14159265
    integer, parameter :: n = 10
    real :: result_sin(n)

    outer_loop: do i = 1, 10
        inner_loop: do j = 1, 10
            if ((j + i) > 10) then  ! Print only pairs of i and j that add up to 10
            cycle outer_loop  ! Go to the next iteration of the outer loop
            end if
            ! print *, 'I=', i, ' J=', j, ' Sum=', j + i
        end do inner_loop
    end do outer_loop

    ! Example of do concurrent() loop

    do concurrent (i = 1:n)  ! Careful, the syntax is slightly different
    result_sin(i) = sin(i * pi/4.)
    end do

    print *, result_sin
end program flow_control