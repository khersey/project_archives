*>
*> filename:   iterative_ackermann.cbl
*> student:    Kyle Hersey
*> student#:   0851973
*> course:     CIS*3190
*> assignment: 4
*>

identification division.
program-id. iterative_ackermann.

data division.
working-storage section.
77 m pic S9(12).
77 n pic S9(12).

01 stack.
    02 st pic S9(12) occurs 1000000 times.

77 st-top pic S9(12).

procedure division.
    move 0 to st-top.

    display "Please enter M: ".
    accept m.
    display "Please enter N: ".
    accept n.

    *> push
    add 1 to st-top.
    move m to st(st-top).

    perform until st-top equals 0
        *> pop
        move st(st-top) to m
        subtract 1 from st-top

        evaluate true
            when m equals 0
                add 1 to n

            when n equals 0
                move 1 to n

                *> push
                add 1 to st-top
                if (st-top = 1000000) then
                    display "Error: Stack Overflow"
                    stop run
                end-if
                subtract 1 from m giving st(st-top)

            when other
                subtract 1 from n

                *> push
                add 1 to st-top
                if (st-top = 1000000) then
                    display "Error: Stack Overflow"
                    stop run
                end-if
                subtract 1 from m giving st(st-top)

                *> push
                add 1 to st-top
                if (st-top = 1000000) then
                    display "Error: Stack Overflow"
                    stop run
                end-if
                move m to st(st-top)

        end-evaluate
    end-perform.

    display "Result is " n.

stop run.     
