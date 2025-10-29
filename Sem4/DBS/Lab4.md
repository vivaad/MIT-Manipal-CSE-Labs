


# LAB4 - COMPLEX QUERIES ON SQL

## Group By

1. **Find the number of students in each course.**
```sql
select course_id, count(id)
from takes
group by course_id;
```

2. **Find those departments where the average number of students are greater than 10.**
```sql
select dept_name, count(id) count_students
from student
group by dept_name
having count(id) > 10;
```

3. **Find the total number of courses in each department.**
```sql
select dept_name, count(dept_name) courses_number
from course
group by dept_name;
```

4. **Find the names and average salaries of all departments whose average salary is greater than 42000.**
```sql
select dept_name, avg(salary) avg_sal
from instructor
group by dept_name
having avg(salary) > 42000;
```

5. **Find the enrolment of each section that was offered in Spring 2009.**
```sql
select sec_id, count(id)
from takes
where semester = 'Spring' and year = 2009
group by sec_id;
```

## Ordering the display of Tuples (Use ORDER BY ASC/DESC)

6. **List all the courses with prerequisite courses, then display course id in increasing order.**
```sql
select course_id, prereq_id
from prereq
order by course_id asc;
```

7. **Display the details of instructors sorting the salary in decreasing order.**
```sql
select *
from instructor
order by salary desc;
```

## Derived Relations

8. **Find the maximum total salary across the departments.**
```sql
with max_salary_dept(dept_name, max_sum_salary) as (
    select dept_name, sum(salary) as max_sum_salary
    from instructor
    group by dept_name
)
select dept_name, max_sum_salary
from max_salary_dept
where max_sum_salary = (select max(max_sum_salary) from max_salary_dept);
```

9. **Find the average instructors’ salaries of those departments where the average salary is greater than 42000.**
```sql
with avg_salary_dept(dept_name, avg_salary) as (
    select dept_name, avg(salary) as avg_salary
    from instructor
    group by dept_name
)
select dept_name, avg_salary
from avg_salary_dept
where avg_salary > 42000;
```

10. **Find the sections that had the maximum enrolment in Spring 2010.**
```sql
with sec_enroll(sec_id, max_num) as (
    select sec_id, count(id) as max_num
    from takes
    group by sec_id
)
select sec_id, max_num
from sec_enroll
where max_num = (select max(max_num) from sec_enroll);
```

11. **Find the names of all instructors who teach all students that belong to 'CSE' department.**
```sql
select name, T.id
from instructor T
where not exists (
    (select id from student where dept_name = 'Comp. Sci.')
    minus
    (select takes.id from takes, teaches S
     where takes.course_id = S.course_id
       and S.id = T.id)
);
```

12. **Find the average salary of those departments where the average salary is greater than 50000 and total number of instructors in the department are more than 5.**
```sql
with avg_salary_dept(dept_name, avg_salary, count_instructor) as (
    select dept_name, avg(salary) as avg_salary, count(*) as count_instructor
    from instructor
    group by dept_name
)
select dept_name, avg_salary, count_instructor
from avg_salary_dept
where avg_salary > 50000 and count_instructor > 5;
```

## With Clause

13. **Find all departments with the maximum budget.**
```sql
with max_budget_dept(dept_name, max_budget) as (
    select dept_name, max(budget) as max_budget
    from department
    group by dept_name
)
select dept_name, max_budget
from max_budget_dept
where max_budget = (select max(max_budget) from max_budget_dept);
```

14. **Find all departments where the total salary is greater than the average of the total salary at all departments.**
```sql
with total_salary_per_dept as (
    select dept_name, sum(salary) as total_salary
    from instructor
    group by dept_name
), avg_total_salary as (
    select avg(total_salary) as avg_salary
    from total_salary_per_dept
)
select dept_name, total_salary
from total_salary_per_dept
where total_salary > (select avg_salary from avg_total_salary);
```

## Transactions (Use ROLLBACK and SAVEPOINT)

15. **Transfer all the students from CSE department to IT department.**
```sql
BEGIN;

-- Set a savepoint before updating
SAVEPOINT before_update;

UPDATE student
SET dept_name = 'IT'
WHERE dept_name = 'CSE';

-- Inspect changes or decide to rollback
ROLLBACK TO SAVEPOINT before_update;

-- Commit if satisfied (Optional)
COMMIT;

```

16. **Increase salaries of instructors whose salary is over $100,000 by 3%, and all others receive a 5% raise.**
```sql
begin;

update instructor
set salary = salary * 1.03
where salary > 100000;

update instructor
set salary = salary * 1.05
where salary <= 100000;

commit;

```