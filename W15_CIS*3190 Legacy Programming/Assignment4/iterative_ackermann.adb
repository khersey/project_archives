-- filename:   iterative_ackermann.adb
-- author:     Kyle Hersey
-- student#:   0851973
-- course:     CIS*3190
-- assignment: 4
-- M=4 N=1 Time to Complete=8m59.296s


with ada.text_io; use ada.text_io;
with ada.integer_text_io; use ada.integer_text_io;
with ada.containers.doubly_linked_lists;


procedure Iterative_Ackermann is

    package linked is 
        new ada.containers.doubly_linked_lists(element_type => integer);

    -- push to top of stack operation
    procedure push(stack : in out linked.list; item : in integer) is
    begin
        linked.prepend(stack, item, 1);
    end push;


    -- pop from top of stack operation
    procedure pop(stack : in out linked.list; item : out integer) is 
    begin
        if linked.is_empty(stack) then
            put_line("Error: attempt to pop from empty stack");
        else 
            item := linked.first_element(stack);
            linked.delete_first(stack, 1);
        end if;
    end pop;

    procedure ackermann(stack : in out linked.list; m : in out integer; n : in out integer) is
    begin
        push(stack, m);
        while not linked.is_empty(stack) loop
            pop(stack, m);
            if m = 0 then
                n := n+1;
            elsif n = 0 then 
                n := 1;
                push(stack, m-1);
            else 
                n := n-1;
                push(stack, m-1);
                push(stack, m);
            end if;
        end loop;
    end ackermann;

    -- Variable declarations
    stack : linked.list;
    m     : integer;
    n     : integer;

begin 
    put("Please Enter M: ");
    get(m);
    put("Please Enter N: ");
    get(n);

    ackermann(stack, m, n);

    put("Result = "); 
    put(n); 
    new_line;

end Iterative_Ackermann;
