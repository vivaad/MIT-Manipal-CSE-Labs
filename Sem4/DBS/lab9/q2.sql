-- Q2
-- Based on the University Database Schema in Lab 2, write a procedure which takes
-- the dept_name as input parameter and lists all the instructors associated with the
-- department as well as list all the courses offered by the department. Also, write an
-- anonymous block with the procedure call.

CREATE or REPLACE PROCEDURE list(dn department.dept_name%TYPE) IS
BEGIN
    for inst in (select name from instructor where dept_name= dn)
    loop 
        dbms_output.put_line(inst.name);
    end loop;

    for cr in (select title from course where dept_name= dn)
    loop
        dbms_output.put_line(cr.title);
    end loop;
end;
/

-- set serveroutput on;
-- SQL> begin
--   2  list('Biology');
--   3  end;
--   4  /

-- OUTPuT
-- Crick
-- Intro. to Biology
-- Genetics
-- Computational Biology