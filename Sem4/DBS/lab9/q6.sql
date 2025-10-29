-- Q6
-- Based on the University Database Schema in Lab 2, write a Pl/Sql block of code
-- that lists the highest paid Instructor in each of the Department. It should make use
-- of a function department_highest which returns the highest paid Instructor for the
-- given branch.

set serveroutput on;
create or replace function dept_highest(dname varchar) 
return number as
inst_max number;
begin
	select max(salary) into inst_max from instructor where dept_name=dname;
	return inst_max;
end;
/