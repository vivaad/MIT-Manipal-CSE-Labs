# LAB1 - INTRODUCTION TO SQL

## Task 1: Create a Table for Employees

```sql
-- Create a table 'employee' with emp_no, emp_name, and emp_address
create table employee (
    emp_no number(5), 
    emp_name varchar(20), 
    emp_address varchar(20)
);
```

---

## Task 2: Insert Five Employees' Information

```sql
-- Insert information for 5 employees
insert into employee values(101, 'Prisha', 'Patna');
insert into employee values(102, 'Poorvi', 'Karwar');
insert into employee values(103, 'Pavana', 'Manipal');
insert into employee values(104, 'Shaurya', 'Mangalore');
insert into employee values(105, 'Udit', 'Manipal');
```

---

## Task 3: Display Names of All Employees

```sql
-- Display the names of all employees
select emp_name from employee;
```

---

## Task 4: Display All Employees from ‘MANIPAL’

```sql
-- Display names of employees who are from 'Manipal'
select emp_name from employee where emp_address = 'Manipal';
```

---

## Task 5: Add a Column Named Salary to Employee Table

```sql
-- Add a column 'salary' to the employee table
alter table employee add(salary number(5));
```

---

## Task 6: Assign Salary for All Employees

```sql
-- Assign a salary value of 2500 to all employees
update employee set salary = 2500;
```

---

## Task 7: View the Structure of the Table Employee Using Describe

```sql
-- View the structure of the 'employee' table
desc employee;
```

---

## Task 8: Delete All Employees from ‘MANGALORE’

```sql
-- Delete all employees who are from 'Mangalore'
delete from employee where emp_address = 'Mangalore';
```

---

## Task 9: Rename the Employee Table as Employee1

```sql
-- Rename the 'employee' table to 'employee1'
rename employee to employee1;
```

---

## Task 10: Drop the Table Employee1

```sql
-- Drop the 'employee1' table
drop table employee1;
```

---
