--EX1. 
create table emp_deleted (emp_id char(9) primary key, emp_name varchar(15), emp_sal decimal(10, 2));
create or replace trigger emp_trigger 
before delete on employee
for each row 
begin 
    insert into emp_deleted values(:old.ssn, :old.fname, :old.salary);
end;
/
--test
delete from employee where ssn = 653298653;
select * from emp_deleted;

--1.  Based on the University database Schema in Lab 2, write a row trigger that records 
--along with the time any change made in the Takes (ID, course-id, sec-id, semester, 
--year, grade) table in log_change_Takes (Time_Of_Change, ID, courseid,sec-id, 
--semester, year, grade). 
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

--2. Based on the University database schema in Lab: 2, write a row trigger to insert 
--the existing values of the Instructor (ID, name, dept-name, salary) table into a new 
--table Old_ Data_Instructor (ID, name, dept-name, salary) when the salary table is 
--updated. 
create table old_data_instructor(id varchar(5) primary key, name varchar(20), dept_name varchar(20), salary numeric(8, 2));
create or replace trigger salary_trigger 
after update of salary on instructor 
for each row 
begin 
    insert into old_data_instructor values (:old.id, :old.name, :old.dept_name, :old.salary);
end;
/
--test
update instructor set salary = salary * 1.1 where id = 12121;
select * from old_data_instructor;

--3. Based on the University Schema, write a database trigger on Instructor that checks the following: 
-- The name of the instructor is a valid name containing only alphabets. 
-- The salary of an instructor is not zero and is positive 
-- The salary does not exceed the budget of the department to which the instructor belongs. 

create or replace trigger validate_instructor 
before insert or update on instructor 
for each row 
declare v_dep_budg number;
begin 
    if not regexp_like(:new.name, '^[A-Za-z]+$') then 
        dbms_output.put_line('Alert: Instructor name "'|| :new.name || '" contains non-alphabetic characters');
    end if;
    if :new.salary <= 0 then 
        dbms_output.put_line('Alert: Instructor salary (' || :new.salary || ') must be +ve');
    end if;
    select budget into v_dep_budg from department where dept_name = :new.dept_name;
    if :new.salary > v_dep_budg then 
        dbms_output.put_line('Alert: Instructor salary (' || :new.salary || ') exceeds the budget of the department (' || v_dep_budg || ')');
    end if;
end;
/


--4.  Create a transparent audit system for a table Client_master (client_no, name, address, Bal_due). 
--The system must keep track of the records that are being deleted or updated. The functionality 
--being when a record is deleted or modified the original record details and the date of operation 
--are stored in the auditclient (client_no, name, bal_due, operation, userid, opdate) table, 
--then the delete or update is allowed to go through. 

create table client_master(client_no number primary key, name varchar2(20), address varchar2(20), bal_due number(8, 2));
create table auditclient(client_no number primary key, name varchar2(20), bal_due number(8, 2), operation varchar2(20) check (operation in ('UPDATE', 'DELETE')), userid varchar2(20), opdate date);

create or replace trigger audit_changes 
before delete or update on client_master 
for each row 
declare v_userid varchar2(50);
begin 
    v_userid := USER;
    if deleting then 
        insert into auditclient values (:old.client_no, :old.name, :old.bal_due, 'DELETE', v_userid, SYSDATE);
    elsif updating then 
        insert into auditclient values(:old.client_no, :old.name, :old.bal_due, 'UPDATE', v_userid, SYSDATE);
    end if;
end;
/

--test 
INSERT INTO Client_master VALUES (101, 'John Doe', '123 Main St', 1000);
INSERT INTO Client_master VALUES (102, 'Jane Smith', '456 Elm St', 2000);

update client_master set name = 'John Doe Updated', bal_due = 500 where client_no = 101;
delete from client_master where client_no = 102;

select * from client_master;
select * from auditclient;

--5.  Based on the University database Schema in Lab 2, create a view Advisor_Student 
--which is a natural join on Advisor, Student and Instructor tables. Create an 
--INSTEAD OF trigger on Advisor_Student to enable the user to delete the 
--corresponding entries in Advisor table. 

CREATE OR REPLACE VIEW Advisor_Student AS
    SELECT s.s_id AS student_id, s.name AS student_name, 
           a.i_id AS instructor_id, i.name AS instructor_name
    FROM Advisor a
    NATURAL JOIN Student s
    NATURAL JOIN Instructor i;

CREATE OR REPLACE TRIGGER delete_advisor_insteadof
INSTEAD OF DELETE ON Advisor_Student
FOR EACH ROW
BEGIN
    -- Delete the corresponding record from the Advisor table
    DELETE FROM Advisor
    WHERE s_id = :OLD.student_id AND i_id = :OLD.instructor_id;
END;
/
--test
-- Sample data for Student table
INSERT INTO Student (s_id, name, dept_name, tot_cred)
VALUES (1, 'John Doe', 'Computer Science', 30);

-- Sample data for Instructor table
INSERT INTO Instructor (i_id, name, dept_name, salary)
VALUES (101, 'Dr. Smith', 'Computer Science', 70000);

-- Sample data for Advisor table
INSERT INTO Advisor (s_id, i_id)
VALUES (1, 101);

SELECT * FROM Advisor_Student;

DELETE FROM Advisor_Student
WHERE student_id = 1 AND instructor_id = 101;

SELECT * FROM Advisor;
