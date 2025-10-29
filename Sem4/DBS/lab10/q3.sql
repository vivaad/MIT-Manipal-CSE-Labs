-- Q3
-- Based on the University Schema, write a database trigger on Instructor that checks
-- the following:
-- - The name of the instructor is a valid name containing only alphabets.
-- - The salary of an instructor is not zero and is positive
-- - The salary does not exceed the budget of the department to which the instructor belongs.

create or replace trigger validate_instructor 
before insert or update on instructor 
for each row 
declare v_dep_budg number;
begin 
    if not regexp_like(:new.name, '^[A-Za-z]+$') then 
        -- dbms_output.put_line('Alert: Instructor name "'|| :new.name || '" contains non-alphabetic characters');
        raise_application_error(-20001, 'invalid name');
    end if;
    if :new.salary <= 0 then 
        -- dbms_output.put_line('Alert: Instructor salary (' || :new.salary || ') must be +ve');
        raise_application_error(-20002, 'invalid salary');
    end if;
    select budget into v_dep_budg from department where dept_name = :new.dept_name;
    if :new.salary > v_dep_budg then 
        -- dbms_output.put_line('Alert: Instructor salary (' || :new.salary || ') exceeds the budget of the department (' || v_dep_budg || ')');
        raise_application_error(-20003, 'Budget exceded');
        end if;
end;
/

--test
insert into instructor values ('3232', 'ElaSaid', 'History', '0');

-- output
-- ORA-20002: invalid salary