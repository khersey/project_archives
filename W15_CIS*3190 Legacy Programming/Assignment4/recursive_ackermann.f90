! filename:   recursive_ackermann.f90
! author:     Kyle Hersey
! student#:   0851973
! course:     CIS*3190
! assignment: 4
! M=4 N=1 Time to Complete=0m55.100s

recursive function ackermann(m, n) result(r)
    implicit none
    integer, intent(in) :: m, n
    integer :: r

    if (m == 0) then
        r = (n + 1)
        return
    else if (n == 0) then
        r = ackermann(m - 1, 1)
        return
    else
        r = ackermann(m - 1, ackermann(m, n - 1))
        return
    end if
end function ackermann


Program Recursive_Ackermann

implicit none

integer, external :: ackermann
integer :: m, n, r

write(*,*) 'Enter M: '
read(*,*) m
write(*,*) 'Enter N: '
read(*,*) n

r = ackermann(m,n)

write(*,*) 'Result is ', r

end Program Recursive_Ackermann


