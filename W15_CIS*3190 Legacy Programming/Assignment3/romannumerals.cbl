*>
*> filename:   romannumerals.cbl
*> student:    Kyle Hersey
*> student#:   0851973
*> course:     CIS*3190
*> assignment: 3
*>

identification division.
program-id. roman-numerals.


environment division.
configuration section.

input-output section.
file-control.
    select file-input assign to dynamic in-file-name organization is line sequential.

data division.
file section.
fd file-input.
    01 file-in-record pic X(30).

working-storage section.
77 eof pic S9.
77 in-file-name pic X(50).
77 in-mode pic X(10).
77 temp pic S9(8)   usage is computational.
77 ret  pic S99     usage is computational.
01 array-area.
    02 r  pic X(1)  occurs 30 times.
77 out-eq pic Z(9).

procedure division.
    display " Roman Number Equivalents    ".
    display "-----------------------------".
    display " Roman Number    Dec. Equiv. ".
    display "--------------  -------------".
    display " ".

    perform until in-mode equals "yes" or "no"
        display "Would you like to use file input?"
        accept in-mode
    end-perform.

    if in-mode is equal to "no" then
        display "Enter 'quit' to exit"
        move spaces to array-area
        display "Enter Roman Number: "
        accept array-area
        perform until array-area equals "quit"
            call "convert" using array-area, ret, temp
            if ret is equal to 1 then
                move temp to out-eq
                display "Converted Value: " out-eq
                display " "o
            end-if
            move spaces to array-area
            display "Enter Roman Number: "
            accept array-area
        end-perform
    else 
        display "Enter File Name: "
        accept in-file-name
        open input file-input
        move 0 to eof

        read file-input 
            at end set eof to 1
        end-read

        perform until eof equals 1
            move spaces to array-area
            move file-in-record to array-area
            call "convert" using array-area, ret, temp

            if ret is equal to 1 then
                move temp to out-eq
                display "Value from File: "  array-area
                display "Converted Value: "  out-eq
                display " "
            end-if

            read file-input 
                at end set eof to 1
            end-read
            move file-in-record to array-area

        end-perform

        close file-input

    end-if.
    
stop run.
