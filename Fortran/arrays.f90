program array_slice
  implicit none

  ! Fortran arrays are stored in *column-major* order; the first index varies fastest.

  integer :: i
  integer :: array1(10)  ! 1D integer array of 10 elements

  integer :: array2(10, 10)  ! 2D integer array of 100 elements

  character(:), allocatable :: first_name ! Allocable (dynamic) arrays
  character(:), allocatable :: last_name

  character(len=10), dimension(2) :: keys, vals ! String array

  array1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  ! Array constructor
  print *, "Array at odd indices"
  print *, array1(1:10:2)  ! Print out elements at odd indices, start at element 1, go up to element 10, in strides of 2

  print *, "Array in reverse!"
  print *, array1(10:1:-1)  ! Print an array in reverse

  array1(:) = 0  ! Set all elements to zero
  print *, "Reset array to 0!"
  print *, array1

  array1 = [(i, i = 1, 10)]  ! Implied do loop constructor
  print *, "Now back to 1 to 10!"
  print *, array1


  array1(1:5) = 1  ! Set first five elements to one
  print *, "Set first five elements to 1"
  print *, array1

  array1(6:) = 2  ! Set all elements after five to two
  print *, "Set all elements after 5 to 2"
  print *, array1


  print *, "First column of 2d array"
  print *, array2(:,1)  ! Print out the first column in a 2D array

  !!!
  ! Setting character strings
  !!!

  ! Explicit allocation statement
  allocate(character(4) :: first_name)
  first_name = 'John'

  ! Allocation on assignment
  last_name = 'Smith'

  print *, first_name//' '//last_name

  !!!
  ! 

  keys = [character(len=10) :: "user", "dbname"]
  vals = [character(len=10) :: "ben", "motivation"]

  call show(keys, vals)

  contains

  subroutine show(akeys, avals)
    character(len=*), intent(in) :: akeys(:), avals(:)
    integer                      :: i

    do i = 1, size(akeys)
      print *, trim(akeys(i)), ": ", trim(avals(i))
    end do

  end subroutine show

end program array_slice