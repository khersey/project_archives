! filename:   iterative_ackermann.f90
! author:     Kyle Hersey
! student#:   0851973
! course:     CIS*3190
! assignment: 4

! main function
Program iterative_ackermann
implicit none

integer, dimension(1000000) :: st
integer :: top, m, n

top = 0

write(*,*) 'Enter M: '
read(*,*) m
write(*,*) 'Enter N: '
read(*,*) n

call ackermann(m, n, st, top)

write(*,*) 'Result is', n

end Program iterative_ackermann


! ackermann function
subroutine ackermann(m, n, st, top)
implicit none

integer, dimension(1000000), intent(in out) :: st
integer, intent(in out) :: top, m, n

call push(m, st, top)
do while (top /= 0)
    call pop(m, st, top)
    if (m == 0) then
        n = n + 1
    else if (n == 0) then
        n = 1
        call push(m - 1, st, top)
    else
        n = n - 1
        call push(m - 1, st, top)
        call push(m, st, top)
    end if
end do

end subroutine ackermann


! stack push operation
subroutine push(item, st, top) 
implicit none

integer, dimension(1000000), intent(in out) :: st
integer, intent(in out) :: top
integer, intent(in) :: item

top = top + 1
if (top == 1000000) then
    write(*,*) 'Error: Stack Overflow'
    call exit(0)
end if

st(top) = item

end subroutine push

! stack pop operation
subroutine pop(item, st, top)
implicit none

integer, dimension(1000000), intent(in out) :: st
integer, intent(in out) :: top
integer, intent(out) :: item


if (top == 0) then
    write(*,*) 'Error: Stack Underflow'
    call exit(0)
end if

item = st(top)
top = top - 1

end subroutine pop


