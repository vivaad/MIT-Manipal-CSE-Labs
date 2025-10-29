
-- Q2
-- Based on the University database schema in Lab: 2, write a row trigger to insert
-- the existing values of the Instructor (ID, name, dept-name, salary) table into a new
-- table Old_ Data_Instructor (ID, name, dept-name, salary) when the salary table is
-- updated.

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

-- ID    NAME                 DEPT_NAME                SALARY
-- ----- -------------------- -------------------- ----------
-- 12121 Wu                   Finance                   90000