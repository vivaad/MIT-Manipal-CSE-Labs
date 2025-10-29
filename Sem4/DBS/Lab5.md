# LAB5 - ER MODEL AND SQL

### Question 1
**Retrieve the birth date and address of the employee(s) whose name is ‘John B. Smith’. Retrieve the name and address of all employees who work for the ‘Research’ department.**

```sql
-- Retrieve birth date and address of 'John B. Smith'
SELECT Bdate, Address 
FROM EMPLOYEE 
WHERE Fname = 'John' AND Minit = 'B' AND Lname = 'Smith';

-- Retrieve name and address of all employees in the 'Research' department
SELECT E.Fname, E.Lname, E.Address 
FROM EMPLOYEE E 
JOIN DEPARTMENT1 D ON E.Dno = D.Dnumber 
WHERE D.Dname = 'Research';
```

---

### Question 2
**For every project located in ‘Stanford’, list the project number, the controlling department number, and the department manager’s last name, address, and birth date.**

```sql
SELECT P.Pnumber, P.Dnum, M.Lname, M.Address, M.Bdate 
FROM PROJECT P 
JOIN DEPARTMENT1 D ON P.Dnum = D.Dnumber 
JOIN EMPLOYEE M ON D.Mgr_ssn = M.Ssn 
WHERE P.Plocation = 'Stanford';
```

---

### Question 3
**For each employee, retrieve the employee’s first and last name and the first and last name of his or her immediate supervisor.**

```sql
SELECT E.Fname, E.Lname, S.Fname AS Supervisor_Fname, S.Lname AS Supervisor_Lname 
FROM EMPLOYEE E 
LEFT JOIN EMPLOYEE S ON E.Super_ssn = S.Ssn;
```

---

### Question 4
**Make a list of all project numbers for projects that involve an employee whose last name is ‘Smith’, either as a worker or as a manager of the department that controls the project.**

```sql
SELECT DISTINCT P.Pnumber 
FROM PROJECT P 
JOIN WORKS_ON W ON P.Pnumber = W.Pno 
JOIN EMPLOYEE E ON W.Essn = E.Ssn 
WHERE E.Lname = 'Smith' 

UNION 

SELECT DISTINCT P.Pnumber 
FROM PROJECT P 
JOIN DEPARTMENT1 D ON P.Dnum = D.Dnumber 
JOIN EMPLOYEE E ON D.Mgr_ssn = E.Ssn 
WHERE E.Lname = 'Smith';
```

---

### Question 5
**Show the resulting salaries if every employee working on the ‘ProductX’ project is given a 10 percent raise.**

```sql
SELECT E.Fname, E.Lname, E.Salary * 1.1 AS New_Salary 
FROM EMPLOYEE E 
JOIN WORKS_ON W ON E.Ssn = W.Essn 
JOIN PROJECT P ON W.Pno = P.Pnumber 
WHERE P.Pname = 'ProductX';
```

---

### Question 6
**Retrieve a list of employees and the projects they are working on, ordered by department and, within each department, ordered alphabetically by last name, then first name.**

```sql
SELECT E.Fname, E.Lname, P.Pname 
FROM EMPLOYEE E 
JOIN WORKS_ON W ON E.Ssn = W.Essn 
JOIN PROJECT P ON W.Pno = P.Pnumber 
ORDER BY E.Dno, E.Lname, E.Fname;
```

---

### Question 7
**Retrieve the name of each employee who has a dependent with the same first name and is the same sex as the employee.**

```sql
SELECT E.Fname, E.Lname 
FROM EMPLOYEE E 
JOIN DEPENDENT D ON E.Ssn = D.Essn 
WHERE E.Fname = D.Dependent_name AND E.Sex = D.Sex;
```

---

### Question 8
**Retrieve the names of employees who have no dependents.**

```sql
SELECT E.Fname, E.Lname 
FROM EMPLOYEE E 
LEFT JOIN DEPENDENT D ON E.Ssn = D.Essn 
WHERE D.Essn IS NULL;
```

---

### Question 9
**List the names of managers who have at least one dependent.**

```sql
SELECT E.Fname, E.Lname 
FROM EMPLOYEE E 
JOIN DEPENDENT D ON E.Ssn = D.Essn 
WHERE E.Ssn IN (SELECT Mgr_ssn FROM DEPARTMENT1);
```

---

### Question 10
**Find the sum of the salaries of all employees, the maximum salary, the minimum salary, and the average salary.**

```sql
SELECT SUM(Salary), MAX(Salary), MIN(Salary), AVG(Salary) 
FROM EMPLOYEE;
```

---

### Question 11
**For each project, retrieve the project number, the project name, and the number of employees who work on that project.**

```sql
SELECT P.Pnumber, P.Pname, COUNT(W.Essn) AS Employee_Count 
FROM PROJECT P 
LEFT JOIN WORKS_ON W ON P.Pnumber = W.Pno 
GROUP BY P.Pnumber, P.Pname;
```

---

### Question 12
**For each project on which more than two employees work, retrieve the project number, the project name, and the number of employees who work on the project.**

```sql
SELECT P.Pnumber, P.Pname, COUNT(W.Essn) AS Employee_Count 
FROM PROJECT P 
JOIN WORKS_ON W ON P.Pnumber = W.Pno 
GROUP BY P.Pnumber, P.Pname 
HAVING COUNT(W.Essn) > 2;
```

---

### Question 13
**For each department that has more than five employees, retrieve the department number and the number of its employees who are making more than 40,000.**

```sql
SELECT D.Dnumber, COUNT(E.Ssn) AS Employee_Count 
FROM DEPARTMENT1 D 
JOIN EMPLOYEE E ON D.Dnumber = E.Dno 
WHERE E.Salary > 40000 
GROUP BY D.Dnumber 
HAVING COUNT(E.Ssn) > 5;
```

--- 
