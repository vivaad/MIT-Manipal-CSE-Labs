## LAB2 - INTEGRITY CONSTRAINTS IN SQL

#### Task 1: Create Employee Table with Constraints

```sql
-- Create Employee table with constraints
create table Employee (
    EmpNo number(5) primary key, 
    EmpName varchar(15) not null, 
    Gender varchar(1) not null, 
    Salary number(5) not null, 
    Address varchar(10) not null, 
    DNo number(3), 
    check (Gender in ('M', 'F'))
);
```

---

#### Task 2: Create Department Table with Constraints

```sql
-- Create Department table with constraints
create table Department (
    DeptNo number(3) primary key, 
    DeptName varchar(10) unique, 
    Location varchar(15)
);
```

---

#### Task 3: Add Foreign Key for Department Number

```sql
-- Add foreign key constraint on DNo in Employee table that references DeptNo in Department table
alter table Employee 
add constraint DNo foreign key (DNo) references Department(DeptNo);
```

---

#### Task 4: Insert Tuples into Employee and Department Tables

```sql
-- Insert tuples into Department and Employee tables
insert into Department values(231, 'Literature', 'Patna');
insert into Employee values(10011, 'Kalki', 'F', 25000, 'Chennai', 231);
```

---

#### Task 5: Try Inserting Invalid Data that Violates Constraints

```sql
-- Try to insert invalid data into Department and Employee tables (this will violate constraints)
insert into Department values(231, 'SST', 'Ranchi');  -- Duplicate DeptNo
insert into Employee values(10011, 'Prerna', 'O', 26000, 'Delhi', 231);  -- Invalid Gender value
```

---

#### Task 6: Modifying or Deleting Violating Data (Cannot Delete/Modify Due to Constraints)

```sql
-- We cannot modify/delete a tuple violating constraints because it cannot be inserted in the first place.
```

---

#### Task 7: Modify the Foreign Key Constraint to Enable Cascading Deletes

```sql
-- Modify the foreign key constraint to delete employees when the department is deleted
ALTER TABLE Employee 
DROP CONSTRAINT fk_dno;
ALTER TABLE Employee 
ADD CONSTRAINT fk_dno 
FOREIGN KEY (DNo) REFERENCES Department(DeptNo) 
ON DELETE CASCADE;
```

---

#### Task 8: Create a Named Constraint for Default Salary and Test the Constraint

```sql
-- Create a named constraint for default salary value
ALTER TABLE Employee 
MODIFY (Salary DEFAULT 10000);

-- Test the constraint by inserting a new record with default salary
insert into Employee (EmpNo, EmpName, Gender, Address, DNo) values (10012, 'Ravi', 'M', 'Bangalore', 231);
```

---

#### Task 9: List All Students with Names and Their Department Names

```sql
-- Retrieve all students with names and department names
select name, dept_name from student;
```

---

#### Task 10: List All Instructors in the CSE Department

```sql
-- Retrieve names of instructors from the 'Comp. Sci.' department
select name from instructor where dept_name = 'Comp. Sci.';
```

---

#### Task 11: Find Course Names in the CSE Department with 3 Credits

```sql
-- Retrieve course titles in 'Comp. Sci.' department with 3 credits
select title from course where dept_name = 'Comp. Sci.' and credits = 3.0;
```

---

#### Task 12: Show All Courses Registered by Student ID 12345

```sql
-- Retrieve course titles registered by the student with ID 12345
select title from course, takes 
where takes.course_id = course.course_id 
and takes.id = 12345;
```

---

#### Task 13: List Instructors with Salary Between 40,000 and 90,000

```sql
-- Retrieve instructors whose salary is between 40,000 and 90,000
select name from instructor where salary > 40000 and salary < 90000;
```

---

#### Task 14: Find IDs of Instructors Who Have Never Taught a Course

```sql
-- Retrieve IDs of instructors who have never taught a course
select id from instructor where id not in (select id from teaches);
```

---

#### Task 15: Find Student Names, Course Names, and Year for Students Who Attended Classes in Room 303

```sql
-- Retrieve student names, course names, and year for students who attended classes in room 303
select name, title, year 
from student 
natural join takes 
natural join course 
natural join section 
where room_number = '303';
```

---

#### Task 16: Find Names and Course IDs for Students Who Took Courses in 2015

```sql
-- Retrieve names and course IDs for students who took courses in 2015
select name, course_id 
from student 
natural join takes 
where year = 2015;
```

---

#### Task 17: Find Instructors Whose Salary is Greater than at Least One Instructor in the CSE Department

```sql
-- Retrieve names of instructors whose salary is greater than at least one instructor in 'Comp. Sci.' department
SELECT DISTINCT T.name
FROM instructor T, instructor S
WHERE T.salary > S.salary
  AND S.dept_name = 'Comp. Sci.';
```

---

#### Task 18: Find Instructors Whose Department Name Includes the Substring ‘ch’

```sql
-- Retrieve names of instructors whose department name includes 'ch'
select name from instructor where dept_name like '%ch%';
```

---

#### Task 19: List Student Names and Length of Their Names

```sql
-- Retrieve student names and the length of each student's name
select name, length(name) from student;
```

---

#### Task 20: List Department Names and 3 Characters from the 3rd Position of Each Department Name

```sql
-- Retrieve department names and 3 characters starting from the 3rd position of each department name
select dept_name, substr(dept_name, 3, 3) from department;
```

---

#### Task 21: List Instructor Names in Uppercase

```sql
-- Retrieve instructor names in uppercase
select upper(name) from instructor;
```

---

#### Task 22: Replace NULL with Value (e.g., 0) for a Column in Any Table

```sql
-- Replace NULL values in Salary column of Instructor table with 0
select name, NVL(salary, 0) from instructor;
```

---

#### Task 23: Display Salary and Salary/3 Rounded to Nearest Hundred for Instructors

```sql
-- Display salary and salary/3 rounded to the nearest hundred
select salary, round(salary / 3, -2) as salary_divided from instructor;
```

---

#### Task 24: Display Employee Birth Dates in Various Formats

```sql
-- Display birth date in 'DD-MON-YYYY' format
select to_char(birth_date, 'DD-MON-YYYY') from employee;

-- Display birth date in 'DD-MON-YY' format
select to_char(birth_date, 'DD-MON-YY') from employee;

-- Display birth date in 'DD-MM-YY' format
select to_char(birth_date, 'DD-MM-YY') from employee;
```

---

#### Task 25: List Employee Names and Birth Year in Different Formats

```sql
-- Display employee names and birth year fully spelled out
select emp_name, to_char(birth_date, 'YYYY') from employee;

-- Display employee names and birth year in first letter capitalized format
select emp_name, to_char(birth_date, 'Year') from employee;

-- Display employee names and birth year in lowercase
select emp_name, to_char(birth_date, 'year') from employee;
```

---