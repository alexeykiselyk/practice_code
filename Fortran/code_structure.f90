
!!!
! Looking at sobroutines
!!!

subroutine print_matrix(n,m,A)
  implicit none
  integer, intent(in) :: n
  integer, intent(in) :: m
  real, intent(in) :: A(n, m)

  ! *intent* signifies to the compiler whether the argument is "read only" (intent(in)), ‘’write-only’’ (intent(out)),
  ! or ‘’read-write’’ (intent(inout)) within the procedure. In this example, the subroutine does not modify its
  ! arguments, hence all arguments are intent(in). It is good programming practice for functions not to modify their
  ! arguments—that is, all function arguments should be intent(in)

  integer :: i

  do i = 1, n
    print *, A(i, 1:m)
  end do

end subroutine print_matrix

!!!
! Now looking at an example of a function in Fortran
!!!

! L2 Norm of a vector, here result(norm) stores the output of the function
function vector_norm(n,vec) result(norm)
  implicit none
  integer, intent(in) :: n
  real, intent(in) :: vec(n)
  real :: norm

  norm = sqrt(sum(vec**2))

end function vector_norm

!!!
! Example of using a module in Fortran
!
! Each module should be written in a separate .f90 source file. Modules need to be
! compiled prior to any program units that use them.
!!!

module my_mod
  implicit none

  private private_var ! All entities are now module-private by default
  public public_var, print_mat  ! Explicitly export public entities

  real, parameter :: public_var = 2
  integer :: private_var

contains

  ! Print matrix A to screen
  subroutine print_mat(A)
    real, intent(in) :: A(:,:)  ! An assumed-shape dummy argument

    integer :: i

    do i = 1, size(A,1)
      print *, A(i,:)
    end do

  end subroutine print_mat

  ! We no longer have to explicitly pass the matrix dimensions and can instead take advantage of
  ! assumed-shape arguments since the module will generate the required explicit interface for us.
  ! This results in a much simpler subroutine interface.

end module my_mod

!!!
! Main program code_struc which calls the subroutine, function and module
!!!

program code_struc
    use my_mod
    implicit none

    real :: arr(2, 2)
    real :: mat(10, 10)
    integer :: n = 2, m = 2, i, j
    real :: v(9)
    real :: vector_norm

    ! Creating array to be printed by subroutine print_matrix
    row: do i = 1,n
        column: do j = 1, m
            arr(i,j) = i*j
        end do column
    end do row

    ! Call subroutine print_matrix
    call print_matrix(n, m, arr)

    ! create vector of interest, here it is a nine element long vector, 
    ! with each element equal to 9
    v(:) = 9

    print *, 'Vector norm = ', vector_norm(9,v)

    ! Use public_var from my_mod, equals 2. Fill mat with this number
    mat(:,:) = public_var

    ! Call the subroutine in my_mod print_mat
    call print_mat(mat)

end program code_struc