-- Q1
-- Based on the University database Schema in Lab 2, write a row trigger that records
-- along with the time any change made in the Takes (ID, course-id, sec-id, semester,
-- year, grade) table in log_change_Takes (Time_Of_Change, ID, courseid,sec-id,
-- semester, year, grade).

create table log_change_takes(time_of_change timestamp, id varchar(5), course_id varchar(8), sec_id varchar(8), semester varchar(6), year numeric(4, 0), grade varchar(2), primary key(id, course_id, sec_id, semester, year));
create or replace trigger takes_trigger 
after insert or update of id, course_id, sec_id, semester, year, grade on takes 
for each row 
begin 
    insert into log_change_takes values(sysdate, :new.id, :new.course_id, :new.sec_id, :new.semester, :new.year, :new.grade);
end;
/

--test
insert into takes values('70557', 'CS-101', 1, 'Fall', 2009, 'A');
select * from log_change_takes;

-- TIME_OF_CHANGE
-- ---------------------------------------------------------------------------
-- ID    COURSE_I SEC_ID   SEMEST       YEAR GR
-- ----- -------- -------- ------ ---------- --
-- 25-MAR-25 02.38.19.000000 PM
-- 70557 CS-101   1        Fall         2009 A
