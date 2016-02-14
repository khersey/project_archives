*>
*> filename:   convert.cbl
*> student:    Kyle Hersey
*> student#:   0851973
*> course:     CIS*3190
*> assignment: 3
*>

identification division.
program-id. convert.

data division.
working-storage section.
77 i    pic S99   usage is computational.
77 prev pic S9(8) usage is computational.
77 d    pic S9(4) usage is computational.

linkage section.
77 err pic s9 usage is computational.
77 sum1 pic s9(8) usage is computational.
01 array-area.
    02 s pic X(1) occurs 30 times.

procedure division using array-area, err, sum1.
    move zero to sum1. 
    move 1001 to prev.
    move 1    to i.

    perform varying i from 1 by 1 until s(i) is equal to space 

        evaluate true
            when s(i) is equal to "i" or "I"
                move 1 to d

            when s(i) is equal to 'V' or 'v'
                move 5 to d

            when s(i) is equal to 'X' or 'x'
                move 10 to d

            when s(i) is equal to 'L' or 'l'
                move 50 to d

            when s(i) is equal to 'C' or 'c'
                move 100 to d

            when s(i) is equal to 'D' or 'd'
                move 500 to d

            when s(i) is equal to 'M' or 'm'
                move 1000 to d

            when other
                *> invalid character
                *> display error message
                display " ERROR: Illegal Roman Numeral"
                move 2 to err 
                *> exit on error
                goback 
        end-evaluate

        add d to sum1
        if d is greater than prev
            compute sum1 = sum1 - 2 * prev
        end-if
        move d to prev

    end-perform.
    
    move 1 to err.
goback.
