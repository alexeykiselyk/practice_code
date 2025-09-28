 !A derived type is a special form of data type that can encapsulate other built-in
 ! types as well as other derived types. It could be considered equivalent to
 ! struct in the C and C++ programming languages.

module m_employee
  implicit none
  private
  public t_date, t_address, t_person, t_employee
  ! Note another way of using the public attribute:
  ! gathering all public data types in one place.

  type :: t_date
    integer :: year, month, day
  end type

  type :: t_address
    character(len=:), allocatable :: city, road_name
    integer :: house_number
  end type

  type, extends(t_address) :: t_person
    character(len=:), allocatable :: first_name, last_name, e_mail
  end type

  type, extends(t_person)  :: t_employee
    type(t_date) :: hired_date
    character(len=:), allocatable :: position
    real :: monthly_salary
  end type

end module m_employee

program test_employee
  use m_employee
  implicit none
  type(t_employee) :: employee

  ! Initialization

  ! t_employee has access to type(t_date) members not because of extends
  ! but because a type(t_date) was declared within t_employee.
  employee%hired_date%year  = 2020
  employee%hired_date%month = 1
  employee%hired_date%day   = 20

  ! t_employee has access to t_person, and inherits its members due to extends.
  employee%first_name = 'John'
  employee%last_name  = 'Doe'

  ! t_employee has access to t_address, because it inherits from t_person,
  ! which in return inherits from t_address.
  employee%city         = 'London'
  employee%road_name    = 'BigBen'
  employee%house_number = 1

  ! t_employee has access to its defined members.
  employee%position       = 'Intern'
  employee%monthly_salary = 0.0

end program test_employee

! program derived_types
!     implicit none

!     type :: t_pair
!     integer :: i = 34 ! Can specify values here but don't need to
!     real :: x = 0.6
!     end type

!     ! Declare
!     type(t_pair) :: pair
!     ! Initialize
!     pair%i = 1
!     pair%x = 0.5 ! The percentage symbol % is used to access the members of a derived type.

!     ! Or can initialise derived type members like so:
!     pair = t_pair(1, 0.5)      ! Initialize with positional arguments
!     pair = t_pair(i=1, x=0.5)  ! Initialize with keyword arguments
!     pair = t_pair(x=0.5, i=1)  ! Keyword arguments can go in any order

!     ! The full syntax of a derived type with all optional properties is presented below:
!         ! type [,attribute-list] :: name [(parameterized-declaration-list)]
!         ! [parameterized-definition-statements]
!         ! [private statement or sequence statement]
!         ! [member-variables]
!     ! contains
!         ! [type-bound-procedures]
!     ! end type


! end program derived_types