-- Q3
-- Based on the University Database Schema in Lab 2, write a Pl/Sql block of code
-- that lists the most popular course (highest number of students take it) for each of
-- the departments. It should make use of a procedure course_popular which finds
-- the most popular course in the given department.

set serveroutput on;
create or replace procedure course_popular(dname varchar) is
mm number := 0;
cid course.course_id%TYPE;
cursor c is (select course_id,count(course_id) cc from takes natural join course group by dept_name,course_id having dept_name=dname); 
begin
	for i in c loop
		if i.cc>mm then 
			mm :=i.cc;
			cid :=i.course_id;
		end if;
	end loop;
	dbms_output.put_line('Most Popular Course is '||cid);
end;
/


-- set serveroutput on;      
-- begin
-- course_popular('Biology'); 
-- end;
-- /

-- Most Popular Course is BIO-301