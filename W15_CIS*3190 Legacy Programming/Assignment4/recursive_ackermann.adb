-- filename:   recursive_ackermann.adb
-- author:     Michael Wirth
--             (From Courselink)
-- course:     CIS*3190
-- assignment: 4

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;


procedure Recursive_Ackermann is 

    function Ackermann (M, N : Natural) return Natural is
    begin
        if M = 0 then
            return N + 1;
        elsif N = 0 then
            return Ackermann (M - 1, 1);
        else 
            return Ackermann (M - 1, Ackermann (M, N - 1));
        end if;
    end Ackermann;

    M : integer;
    N : integer;
begin 
    for M in 0..3 loop
        for N in 0..6 loop
            Put(M);
            Put(N);
            Put(": ");
            Put(Natural'Image (Ackermann(M, N)));
            new_line;
        end loop;
        new_line;
    end loop;
    
--    This is code I used for performance testing.
--
--    M := 4;
--    N := 1;
--    put("Result is :");
--    put(Natural'Image (Ackermann(M, N)));
--    new_line;
end Recursive_Ackermann;
