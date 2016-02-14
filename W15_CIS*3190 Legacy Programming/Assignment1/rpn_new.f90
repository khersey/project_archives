
Program RPN

! ============================================= !
!  AUTHOR:           KYLE HERSEY                !
!  STUDENT NUMBER:   0851973                    !
!  ASSIGNMENT:       1. RE-ENGINEERING FORTRAN  !
!  COURSE:           CIS*3190    W15            !
! ============================================= !

implicit none

! TRANSLATING ALGRBRAIC EXPRESSIONS TO POLISH NOTATION
!
! THE VARIABLE NAMES AND THEIR MEANINGS ARE AS FOLLOWS:
! SOURCE THE INPUT STRING, IN NORMAL ALGEBRAIC FORM
! S_HIER ARRAY CONTAINING THE HIERARCHY NUMBERS OF THE INPUT
! OP_STACK 'OPERATOR STACK': THE OPERATORS FROM THE INPUT
! OP_HIER ARRAY CONTAINING THE HIERARCHY NUMBERS OF THE OPERATORS
! POLISH THE OUTPUT STRING, IN POLISH NOTATION
!
! M DO INDEX USED IN SETTING UP S_HIER ARRAY
! I POINTER TO INDEX STRING (SOURCE AND S_HIER)
! J POINTER TO OPERATOR STACK (OP_STACK AND OP_HIER)
! K POINTER TO OUTPUT STRING (POLISH)
!
! THE OTHER VARIABLES ARE ACTUALLY CONSTANTS, AND ARE
! DEFINED IN THE DATA STATEMENT.

integer, dimension(40) :: S_HIER, OP_HIER
integer :: M, I, J, K
character, dimension(40) :: SOURCE, OP_STACK, POLISH
character :: SPACE = ' ', LPAREN = '(', RPAREN = ')', PLUS = '+', MINUS = '-', ASTRSK = '*', SLASH = '/'

! INITIALIZE ARRAYS TO ZERO OR SPACE, AS APPROPRIATE

do
    S_HIER = 0
    OP_HIER = 0
    OP_STACK = SPACE
    POLISH = SPACE

    ! Read data from command line

    WRITE (*,*) 'Enter an equation: '
    READ (*, 30) SOURCE
    30 FORMAT (40A)
    
    ! IN THE FOLLOWING DO-LOOP, M POINTS TO INPUT COLUMNS, FROM LEFT TO RIGHT
    ! FIRST SPACE SIGNALS END OF STRING (EMBEDDED SPACES ARE NOT ALLOWED)
    ! IT IS ASSUMED THAT IF A CHARACTER IS NOT AN OPERATOR OR A
    ! PARENTHESIS, IT IS A VARIABLE.

    do M = 1, 40
        if (SOURCE(M) == SPACE) then
            exit

        else if (SOURCE(M) == LPAREN) then
            S_HIER(M) = 1

        else if (SOURCE(M) == RPAREN) then
            S_HIER(M) = 2

        else if (SOURCE(M) == PLUS .or. SOURCE(M) == MINUS) then
            S_HIER(M) = 3

        else if (SOURCE(M) == ASTRSK .or. SOURCE(M) == SLASH) then
            S_HIER(M) = 4

        end if
    end do

    
    ! IF NORMAL EXIT IS TAKEN, THE CARD DID NOT CONTAIN A SPACE
    if (SOURCE(M) /= SPACE) then
        WRITE (*,*) 'DATA INPUT IN ERROR - NO SPACES'
        cycle

    else if (M == 1) then 
        
        ! if nothing is entered exit program
        exit

    end if

    ! OTHERWISE PROCEED TO TRANSLATION
    ! INITIALIZE HIERARCHY NUMBERS TO GET STARTED PROPERLY
    S_HIER(M) = 0
    OP_HIER(1) = -1
    
    ! INITIALIZE POINTERS
    I = 1
    J = 2
    K = 1

    do
        if (S_HIER(I) == 0 .or. S_HIER(I) == 2) then
            
            ! CHECK FOR OPERAND
            if (S_HIER(I) == 0) then
                
                ! MOVE OPERAND TO POLISH STRING
                POLISH(K) = SOURCE(I)
                I = I + 1
                K = K + 1

            ! CHECK FOR RIGHT PARENTHESIS
            else if (S_HIER(I) == 2) then
                
                ! DELETE CORRESPONDING LEFT PARENTHESIS
                I = I + 1
                J = J - 1

            end if

            ! CHECK HIERARCHY RANKINGS
            do while ( OP_HIER(J-1) >= S_HIER(I) )
                
                ! MOVE OPERATOR TO POLISH STRING
                POLISH(K) = OP_STACK(J-1)
                K = K + 1
                J = J - 1

            end do

            ! CHECK FOR END OF SOURCE STRING
            if (I == M) exit

        else
            ! SOME OTHER OPERATOR IF HERE -- MOVE TO OPERATOR STACK
            OP_STACK(J) = SOURCE(I)
            OP_HIER(J) = S_HIER(I)
            
            ! ADVANCE POINTERS
            I = I + 1
            J = J + 1

        end if 
    end do
    
    ! WRITE SOURCE AND POLISH STRINGS
    WRITE (*, 130) 'INPUT: ', SOURCE, 'RPN: ', POLISH
    130 FORMAT (A7, 40A1/, A7, 40A1)

end do
end Program RPN
