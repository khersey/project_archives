-------------------------------------
-- Author:     Kyle Hersey         --
-- Student#:   0851973             --
-- Course:     CIS*3190            --
-- Assignment: 2 - Ada Programming --
-------------------------------------


-- Packages used
with ada.Text_IO; use ada.Text_IO;
with ada.Integer_Text_IO; use ada.Integer_Text_IO;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
with ada.strings.maps.constants;
with ada.containers.doubly_linked_lists;


procedure Word_Jumble is

    -- define doubly linked list of unbounded strings to be used as a stack
    package linked is 
        new ada.containers.doubly_linked_lists(element_type => unbounded_string);


-- Type Definitions

    type int_array is array (1 .. 20) of integer;
    type unb_str_array is array (natural range <>) of unbounded_string;


-- Function Definitions

    -- Function to check a string against values in the OS X 10.10 dictionary
    -- Returns true upon finding a match, otherwise false.
    function is_word(str : unbounded_string) return boolean is
        word_file : file_type;
        word      : unbounded_string;
        lower_str : unbounded_string;

    begin

        lower_str := translate(str, ada.strings.maps.constants.Lower_Case_Map);
        open(word_file, in_file, "english.dictionary");
        loop
            exit when end_of_file(word_file); 

            get_line(word_file, word);

            if lower_str = word then
                close(word_file);
                return true;
            end if;
        end loop;
        -- if we reach the end of the file it return false
        close(word_file);
        return false;

    end is_word;


-- Procedure Definitions


    -- push to top of stack operation
    procedure push(stack : in out linked.list; str : in unbounded_string) is
    begin
        linked.prepend(stack, str, 1);
    end push;


    -- pop from top of stack operation
    procedure pop(stack : in out linked.list; str : out unbounded_string) is 
    begin
        if linked.is_empty(stack) then
            put_line("Error: attempt to pop from empty stack");
        else 
            str := linked.first_element(stack);
            linked.delete_first(stack, 1);
        end if;
    end pop;


    -- set all values in int array to 0
    procedure reset_int_array(arr : in out int_array) is
    begin
        for i in 1 .. 20 loop
            arr(i) := 0;
        end loop;
    end reset_int_array;


    -- Recursively generate all anagrams of a word.
    -- anagrams are compared to a dictionary, and if they are found to be a read word
    -- they are pushed onto the stack.
    procedure generate_anagram(stack : in out linked.list; word : in out unbounded_string; pos : in integer) is
        len  : integer;
        temp : character;

    begin
        len := length(word);

        if pos < len then
            for i  in pos .. len loop
                -- do character swap
                temp := element(word, i);
                replace_element(word, i, element(word, pos));
                replace_element(word, pos, temp);
                -- end swap

                generate_anagram(stack, word, pos + 1);

                -- do character swap
                temp := element(word, i);
                replace_element(word, i, element(word, pos));
                replace_element(word, pos, temp);
                -- end swap
            end loop;

        else 
            if is_word(word) then
                if not linked.contains(stack, word) then 
                    push(stack, word);
                end if;
            end if;
        end if;
    end generate_anagram;


    -- Prompts user for word and letter indexes input
    -- Letter indexes are parsed from an unbound string, and are added to an int_array
    procedure get_user_input(word : out unbounded_string; letters : out int_array) is
        index : integer;
        num : integer;
        line : unbounded_string;
        chunk : unbounded_string;
        c : character;
    begin
        reset_int_array(letters);
        put("Please enter a word: ");
        get_line(word);
        put("Please enter index of letters to be saved: ");
        get_line(line);
        index := 1;
        for i in 1 .. length(line) loop
            c := element(line,i);
            -- append to chunk
            if c in '0' .. '9' and length(chunk) > 0  then
                chunk := chunk & c;
            -- create new chunk
            elsif c in '0' .. '9' and length(chunk) < 1 then
                chunk := to_unbounded_string("" & c);
            -- add number to array
            elsif (c = ',' or c = ' ') and length(chunk) > 0 then
                num := integer'value(to_string(chunk));
                if num /= 0 then 
                    letters(index) := num; 
                    index := index + 1;
                end if;
                delete(chunk,1,length(chunk));
            end if;
            -- case go make sure last number is added
            if i = length(line) and length(chunk) > 0 then
                num := integer'value(to_string(chunk));
                if num /= 0 then 
                    letters(index) := num; 
                    index := index + 1;
                end if;
                delete(chunk,1,length(chunk));
            end if;

        end loop;

    end get_user_input;


    -- This function displays all words found in the stack and asks to user to select one.
    procedure choose_word(stack : in out linked.list; selected_word : out unbounded_string) is
        choices : unb_str_array(1.. integer(linked.length(stack)));
        word : unbounded_string;
        index : integer := 0;
    begin
        while not linked.is_empty(stack) loop
            pop(stack, word);
            index := index + 1;
            choices(index) := word;
        end loop;
        put("Please select from matches: ");new_line;
        for i in choices'range loop
            put(i);put(". ");put(choices(i));new_line;
        end loop;
        put("Enter word number: ");
        get(index);skip_line;
        while index not in choices'range loop
            put("ERROR: Number out of range");new_line;
            put("Enter word number: ");
            get(index);skip_line;
            new_line;
        end loop;

        selected_word := choices(index);

    end choose_word;



-- Variable Declaration
    stack   : linked.list;
    word    : unbounded_string;
    letters : int_array;
    letter_index : integer;
    sum_word : unbounded_string;
    word_count : integer := 1;
    word_total : integer;

----------
-- MAIN --
----------
begin
    -- display instructions 
    put("------------------------------");new_line;
    put("- Word Jumble by Kyle Hersey -");new_line;
    put("------------------------------");new_line;
    put("This program solves jumbled words and keeps");new_line;
    put("selected letters to solve the final jumble.");new_line;
    put("------------------------------");new_line(2);

    put("Input number of jumbled words (includes final jumble): ");
    get(word_total); skip_line;

    while word_count < word_total loop 

        get_user_input(word, letters);
        word_count := word_count + 1;

        generate_anagram(stack, word, 1);
        -- check to see if no matches were found in dictionary
        if linked.is_empty(stack) then
            put("ERROR: No matches found in dictionary");new_line;
        else 
            -- check to see if more than one matches were found
            if integer(linked.length(stack)) > 1 then
                choose_word(stack, word);
            else
                pop(stack, word);
            end if;

            put("Match: "); 
            put(word);new_line(2);

            -- save letters based on indexes entered earlier
            for i in letters'range loop
                letter_index := letters(i);
                if letter_index /= 0 then
                    append(sum_word, element(word,letter_index));
                end if;
            end loop;
        end if;
    end loop;

    -- solve final word jumble

        new_line;put("Jumble letters are: ");put(sum_word);new_line;
        generate_anagram(stack, sum_word, 1);

        if linked.is_empty(stack) then
            put("ERROR: No matches found in dictionary");new_line;
        else 
            put("Matches: ");new_line;
            while not linked.is_empty(stack) loop
                pop(stack, word);
                put(word);new_line;
            end loop;
            new_line;
        end if;


end Word_Jumble;
