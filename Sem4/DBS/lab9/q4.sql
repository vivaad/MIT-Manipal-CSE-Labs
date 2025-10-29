-- Q4
-- Based on the University Database Schema in Lab 2, write a procedure which takes
-- the dept-name as input parameter and lists all the students associated with the
-- department as well as list all the courses offered by the department. Also, write an
-- anonymous block with the procedure call.

set serveroutput on;
create or replace procedure dept_student_courses(dname varchar) is
cursor stud is (select name from student where dept_name=dname);
cursor course is (select title from course where dept_name=dname);
begin
	dbms_output.put_line('Students');
	for i in stud loop
		dbms_output.put_line(i.name);
	end loop;
	dbms_output.put_line('Courses');
	for i in course loop
		dbms_output.put_line(i.title);
	end loop;
end;
/

-- set SERVEROUTPUT on;
-- begin dept_student_courses end;
-- /

-- OUTPUT:
-- Students
-- Tanaka
-- Courses
-- Intro. to Biology
-- Genetics
-- Computational Biology