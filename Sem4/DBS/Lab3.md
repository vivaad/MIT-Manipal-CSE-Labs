# LAB3 - INTERMEDIATE SQL

## Set Operations

### 1. Find courses that ran in Fall 2009 or in Spring 2010

```sql
-- Using UNION to get courses that ran in either Fall 2009 or Spring 2010
(select course_id from section where semester = 'Fall' and year = 2009)
UNION 
(select course_id from section where semester = 'Spring' and year = 2010);
```

---

### 2. Find courses that ran in Fall 2009 and in Spring 2010

```sql
-- Using INTERSECT to get courses that ran in both Fall 2009 and Spring 2010
(select course_id from section where semester = 'Fall' and year = 2009)
INTERSECT 
(select course_id from section where semester = 'Spring' and year = 2010);
```

---

### 3. Find courses that ran in Fall 2009 but not in Spring 2010

```sql
-- Using MINUS to get courses that ran in Fall 2009 but not in Spring 2010
(select course_id from section where semester = 'Fall' and year = 2009)
MINUS 
(select course_id from section where semester = 'Spring' and year = 2010);
```

---

### 4. Find the name of the course for which none of the students registered

```sql
-- Find courses with no students registered
select title from course where course_id not in (select course_id from takes);
```

---

## Nested Subqueries

### 5. Find courses offered in Fall 2009 and in Spring 2010

```sql
-- Find courses offered in both Fall 2009 and Spring 2010
select course_id from section 
where semester = 'Fall' and year = 2009 
and course_id in (select course_id from section where semester = 'Spring' and year = 2010);
```

---

### 6. Find the total number of students who have taken a course taught by the instructor with ID 10101

```sql
-- Find the total number of students who have taken a course taught by instructor with ID 10101
select count(distinct takes.id) 
from takes 
where (course_id, sec_id, semester, year) in 
    (select course_id, sec_id, semester, year from teaches where id = 10101);
```

---

### 7. Find courses offered in Fall 2009 but not in Spring 2010

```sql
-- Find courses offered in Fall 2009 but not in Spring 2010
select course_id from section 
where semester = 'Fall' and year = 2009 
and course_id not in (select course_id from section where semester = 'Spring' and year = 2010);
```

---

### 8. Find the names of all students whose name is the same as the instructor’s name

```sql
-- Find students whose name matches the name of any instructor
select student.name 
from student 
where student.name in (select instructor.name from instructor);
```

---

## Set Comparison

### 9. Find names of instructors with salary greater than that of some (at least one) instructor in the Biology department

```sql
-- Find instructors with salary greater than that of some instructor in Biology department
select name from instructor 
where salary > some (select salary from instructor where dept_name = 'Biology');
```

---

### 10. Find names of all instructors whose salary is greater than the salary of all instructors in the Biology department

```sql
-- Find instructors with salary greater than all instructors in Biology department
select name from instructor 
where salary > all (select salary from instructor where dept_name = 'Biology');
```

---

### 11. Find the departments that have the highest average salary

```sql
-- Find departments with the highest average salary
select dept_name, avg(salary) 
from instructor 
group by dept_name 
having avg(salary) >= all (select avg(salary) from instructor group by dept_name);
```

---

### 12. Find the names of those departments whose budget is lesser than the average salary of all instructors

```sql
-- Find departments with a budget less than the average salary of instructors
select dept_name, budget 
from department 
where budget < (select avg(salary) from instructor);
```

---

## Test for Empty Relations

### 13. Find all courses taught in both Fall 2009 and Spring 2010

```sql
-- Find courses that were taught in both Fall 2009 and Spring 2010
select course_id from section S 
where S.semester = 'Fall' and S.year = 2009 
and exists (select * from section T where T.semester = 'Spring' and T.year = 2010 and S.course_id = T.course_id);
```

---

### 14. Find all students who have taken all courses offered in the Biology department

```sql
-- Find students who have taken all courses offered in the Biology department
select S.id from student S 
where not exists (
    (select course_id from course where dept_name = 'Biology') 
    minus 
    (select course_id from takes T where S.id = T.id)
);
```

---

## Test for Absence of Duplicate Tuples

### 15. Find all courses that were offered at most once in 2009

```sql
-- Find courses offered at most once in 2009
select course_id from section 
where year = 2009 
group by course_id 
having count(*) <= 1;
```

---

### 16. Find all the students who have opted at least two courses offered by the CSE department

```sql
-- Find students who have opted for at least two courses in the CSE department
select S.id from student S 
where (select count(T.course_id) 
       from takes T, course C 
       where T.course_id = C.course_id 
       and C.dept_name = 'Comp. Sci.' 
       and T.id = S.id) >= 2;
```

---

## Subqueries in the From Clause

### 17. Find the average instructor salary of those departments where the average salary is greater than 42,000

```sql
-- Find the average instructor salary of departments where the average salary is greater than 42,000
select avg(salary) 
from instructor 
where dept_name in (
    select dept_name 
    from instructor 
    group by dept_name 
    having avg(salary) > 42000
);
```

---

## Views

### 18. Create a view `all_courses` consisting of course sections offered by the Physics department in Fall 2009, with building and room number of each section

```sql
-- Create a view for all Physics department courses offered in Fall 2009
create view all_courses as 
select course_id, title, building, room_number 
from section 
join course on section.course_id = course.course_id 
where course.dept_name = 'Physics' 
and semester = 'Fall' and year = 2009;
```

---

### 19. Select all the courses from the `all_courses` view

```sql
-- Select all the courses from the `all_courses` view
select * from all_courses;
```

---

### 20. Create a view `department_total_salary` consisting of department name and total salary of that department

```sql
-- Create a view for department name and total salary
create view department_total_salary as 
select dept_name, sum(salary) 
from instructor 
group by dept_name;
```

---