# Lab 8 CURSORS

## Sample Syntax


### Implicit Cursor

```sql
DECLARE
  dname CONSTANT student.dept_name%TYPE := 'History';
BEGIN
  DELETE FROM student WHERE dept_name = dname;
  IF SQL%FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Delete succeeded');
  ELSE
    DBMS_OUTPUT.PUT_LINE('No students found');
  END IF;
END;
/
```

### Explicit Cursor

```sql
DECLARE
  CURSOR C1 IS SELECT name FROM Student WHERE dept_name = 'Comp. Sci.';
  sname student.name%TYPE;
BEGIN
  OPEN C1;
  LOOP
    FETCH C1 INTO sname;
    EXIT WHEN C1%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE(sname);
  END LOOP;
  CLOSE C1;
END;
/
```

### Cursor FOR LOOP

```sql
DECLARE
  CURSOR C1 IS SELECT * FROM Department;
BEGIN
  FOR dept IN C1 LOOP
    IF dept.Budget > 0 THEN
      DBMS_OUTPUT.PUT_LINE(dept.dept_name || ' ' || dept.Budget);
    END IF;
  END LOOP;
END;
/
```

### WHERE CURRENT OF

```sql
DECLARE
  CURSOR C1 IS SELECT * FROM Department FOR UPDATE;
BEGIN
  FOR dept IN C1 LOOP
    IF dept.Budget <= 70000 THEN
      UPDATE Department SET Budget = Budget * 1.2 WHERE CURRENT OF C1;
    END IF;
  END LOOP;
END;
/
```

### Parameterized Cursor

```sql
DECLARE
  CURSOR C(dname IN instructor.dept_name%TYPE) IS
    SELECT * FROM Instructor WHERE dept_name = dname;
BEGIN
  FOR tmp IN C('Comp. Sci.') LOOP
    DBMS_OUTPUT.PUT_LINE(tmp.name);
  END LOOP;
END;
/
```

### Transaction (COMMIT, ROLLBACK, SAVEPOINT)

```sql
DECLARE
  Total_bal account.balance%TYPE;
BEGIN
  UPDATE account SET balance = balance - 200;
  SAVEPOINT deposit;
  UPDATE account SET balance = balance + 1000;
  SELECT SUM(balance) INTO Total_bal FROM account;
  IF Total_bal > 5000 THEN
    ROLLBACK TO deposit;
  END IF;
  COMMIT;
END;
/
```

---


### Creating necessary tables 

```sql
create table salary_raise (
        Instructor_Id   varchar(5),
        Raise_date      date,
        Raise_amt       numeric(8,2),
        primary key (Instructor_Id, Raise_date),
        foreign key (Instructor_Id) references instructor (ID)
            on delete cascade
);

create table gpa (
        ID          varchar(5),
        gpa         numeric(3,2),
        primary key (ID),
        foreign key (ID) references student (ID)
            on delete cascade
);

create table student_courses (
        student_id   varchar(5),
        course_id    varchar(8),
        sec_id       varchar(8),
        semester     varchar(6),
        year         numeric(4,0),
        primary key (student_id, course_id, sec_id, semester, year),
        foreign key (student_id) references student (ID)
            on delete cascade,
       foreign key (course_id, sec_id, semester, year) references section
           on delete cascade
);
```
---
## Lab Codes

### 1. The HRD manager has decided to raise the salary of all the Instructors in a given department number by 5%. Whenever any such raise is given to the instructor, a record for the same is maintained in the `salary_raise` table. It includes the Instructor Id, the date when the raise was given, and the actual raise amount. Write a PL/SQL block to update the salary of each Instructor and insert a record in the `salary_raise` table.

### Solution:

```sql
SET SERVEROUTPUT ON;
DECLARE
  v_raise_amt NUMBER(8,2);
BEGIN
  FOR r IN (SELECT ID, dept_name FROM instructor) LOOP
    SELECT salary * 0.05
    INTO v_raise_amt
    FROM instructor
    WHERE ID = r.ID;
    UPDATE instructor
    SET salary = salary + v_raise_amt
    WHERE ID = r.ID;
    INSERT INTO salary_raise (Instructor_Id, Raise_date, Raise_amt)
    VALUES (r.ID, SYSDATE, v_raise_amt);
  END LOOP;
  COMMIT;
END;
/
```

---

### 2. Write a PL/SQL block that will display the ID, name, dept_name, and tot_cred of the first 10 students with the lowest total credit.

### Solution:

```sql
SET SERVEROUTPUT ON;

DECLARE
  CURSOR c_students IS
    SELECT ID, name, dept_name, tot_cred
    FROM student
    ORDER BY tot_cred ASC
    FETCH FIRST 10 ROWS ONLY;
  v_id student.ID%TYPE;
  v_name student.name%TYPE;
  v_dept_name student.dept_name%TYPE;
  v_tot_cred student.tot_cred%TYPE;
BEGIN
  FOR r IN c_students LOOP
    v_id := r.ID;
    v_name := r.name;
    v_dept_name := r.dept_name;
    v_tot_cred := r.tot_cred;
    DBMS_OUTPUT.PUT_LINE('ID: ' || v_id || ', Name: ' || v_name || 
                         ', Department: ' || v_dept_name || 
                         ', Total Credits: ' || v_tot_cred);
  END LOOP;
END;
/
```

### Output:

```
ID: 70557, Name: Snow, Department: Physics, Total Credits: 0
ID: 12345, Name: Shankar, Department: Comp. Sci., Total Credits: 32
```

---

### 3. Print the Course details and the total number of students registered for each course along with the course details. (Course-id, title, dept-name, credits, instructor_name, building, room-number, time-slot-id, tot_student_no)

### Solution:

```sql
SET SERVEROUTPUT ON;
DECLARE
  CURSOR c_courses IS
    SELECT s.course_id, c.title, c.dept_name, c.credits, 
           i.name AS instructor_name, 
           s.building, s.room_number, s.time_slot_id,
           COUNT(t.ID) AS tot_student_no
    FROM section s
    JOIN course c ON s.course_id = c.course_id
    LEFT JOIN teaches t ON t.course_id = s.course_id AND t.sec_id = s.sec_id AND t.semester = s.semester AND t.year = s.year
    LEFT JOIN instructor i ON t.ID = i.ID
    GROUP BY s.course_id, c.title, c.dept_name, c.credits, 
             i.name, s.building, s.room_number, s.time_slot_id;
  v_course_id section.course_id%TYPE;
  v_title course.title%TYPE;
  v_dept_name course.dept_name%TYPE;
  v_credits course.credits%TYPE;
  v_instructor_name instructor.name%TYPE;
  v_building section.building%TYPE;
  v_room_number section.room_number%TYPE;
  v_time_slot_id section.time_slot_id%TYPE;
  v_tot_student_no NUMBER;
BEGIN
  FOR r IN c_courses LOOP
    v_course_id := r.course_id;
    v_title := r.title;
    v_dept_name := r.dept_name;
    v_credits := r.credits;
    v_instructor_name := r.instructor_name;
    v_building := r.building;
    v_room_number := r.room_number;
    v_time_slot_id := r.time_slot_id;
    v_tot_student_no := r.tot_student_no;
    DBMS_OUTPUT.PUT_LINE('Course ID: ' || v_course_id || ', Title: ' || v_title || 
                         ', Dept: ' || v_dept_name || ', Credits: ' || v_credits || 
                         ', Instructor: ' || v_instructor_name || ', Building: ' || v_building || 
                         ', Room: ' || v_room_number || ', Time Slot: ' || v_time_slot_id || 
                         ', Total Students: ' || v_tot_student_no);
  END LOOP;
END;
/
```

### Output:

```
Course ID: HIS-351, Title: World History, Dept: History, Credits: 3, Instructor: El Said, Building: Painter, Room: 514, Time Slot: C, Total Students: 1
Course ID: BIO-101, Title: Intro. to Biology, Dept: Biology, Credits: 4, Instructor: Crick, Building: Painter, Room: 514, Time Slot: B, Total Students: 1
```

---

### 4. Find all students who take the course with Course-id: CS101 and if he/she has less than 30 total credits (`tot_cred`), deregister the student from that course.

### Solution:

```sql
SET SERVEROUTPUT ON;
DECLARE
  CURSOR c_students IS
    SELECT t.ID, t.course_id, t.sec_id, t.semester, t.year
    FROM takes t
    JOIN student s ON t.ID = s.ID
    WHERE t.course_id = 'CS-101' AND s.tot_cred < 30;
BEGIN
  FOR r IN c_students LOOP
    DELETE FROM takes
    WHERE ID = r.ID AND course_id = r.course_id AND sec_id = r.sec_id AND semester = r.semester AND year = r.year;
    DBMS_OUTPUT.PUT_LINE('Student ID: ' || r.ID || ' deregistered from course ' || r.course_id);
  END LOOP;
  COMMIT;
END;
/
```

---

### 5. Alter Student Table (refer Lab No. 8 Exercise) by resetting column LetterGrade to 'F'. 
Then write a PL/SQL block to update the table by mapping GPA to the corresponding letter grade for each student.

### Solution:

```sql
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c_students IS
        SELECT ID, tot_cred FROM student;
    v_gpa NUMBER;
BEGIN
    UPDATE student
    SET LetterGrade = 'F';
    FOR student_record IN c_students LOOP
        v_gpa := student_record.tot_cred;
        IF v_gpa >= 90 THEN
            UPDATE student
            SET LetterGrade = 'A'
            WHERE ID = student_record.ID;
        ELSIF v_gpa >= 80 THEN
            UPDATE student
            SET LetterGrade = 'B'
            WHERE ID = student_record.ID;
        ELSIF v_gpa >= 70 THEN
            UPDATE student
            SET LetterGrade = 'C'
            WHERE ID = student_record.ID;
        ELSIF v_gpa >= 60 THEN
            UPDATE student
            SET LetterGrade = 'D'
            WHERE ID = student_record.ID;
        ELSE
            UPDATE student
            SET LetterGrade = 'F'
            WHERE ID = student_record.ID;
        END IF;
    END LOOP;
    COMMIT;
END;
/
```

---

### 6. Write a PL/SQL block to print the list of Instructors teaching a specified course.

### Solution:

```sql
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c_instructors (p_course_id VARCHAR) IS
        SELECT i.name, i.dept_name, i.salary
        FROM instructor i
        JOIN teaches t ON i.ID = t.ID
        WHERE t.course_id = p_course_id;
    v_course_id VARCHAR(8) := 'CS-101';
BEGIN
    FOR instructor_record IN c_instructors(v_course_id) LOOP
        DBMS_OUTPUT.PUT_LINE('Instructor Name: ' || instructor_record.name);
        DBMS_OUTPUT.PUT_LINE('Department: ' || instructor_record.dept_name);
        DBMS_OUTPUT.PUT_LINE('Salary: ' || instructor_record.salary);
        DBMS_OUTPUT.PUT_LINE('---');
    END LOOP;
END;
/
```

### Output:

```
Instructor Name: Srinivasan
Department: Comp. Sci.
Salary: 68250
---
Instructor Name: Katz
Department: Comp. Sci.
Salary: 78750
---
```

---

### 7. Write a PL/SQL block to list the students who have registered for a course taught by his/her advisor.

### Solution:

```sql
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c_students (p_advisor_id VARCHAR) IS
        SELECT s.name, s.dept_name, t.course_id, t.semester, t.year
        FROM student s
        JOIN advisor a ON s.ID = a.s_ID
        JOIN teaches t ON a.i_ID = t.ID
        WHERE a.i_ID = p_advisor_id;
    v_advisor_id VARCHAR(5) := '10101'; 
BEGIN
    FOR student_record IN c_students(v_advisor_id) LOOP
        DBMS_OUTPUT.PUT_LINE('Student Name: ' || student_record.name);
        DBMS_OUTPUT.PUT_LINE('Course ID: ' || student_record.course_id);
        DBMS_OUTPUT.PUT_LINE('Semester: ' || student_record.semester);
        DBMS_OUTPUT.PUT_LINE('Year: ' || student_record.year);
        DBMS_OUTPUT.PUT_LINE('---');
    END LOOP;
END;
/
```

### Output:

```
Student Name: Shankar
Course ID: CS-101
Semester: Fall
Year: 2009
---
Student Name: Shankar
Course ID: CS-315
Semester: Spring
Year: 2010
---
```

---

## Tables Overview:

### `salary_raise` Table:

| INSTR  | RAISE_DAT  | RAISE_AMT |
|--------|------------|-----------|
| 10101  | 21-FEB-25  | 5000      |
| 12121  | 21-FEB-25  | 4500      |
| 15151  | 21-FEB-25  | 4000      |
| 22222  | 21-FEB-25  | 6000      |
| 32343  | 21-FEB-25  | 3500      |
| 10101  | 21-FEB-25  | 3250      |
| 12121  | 21-FEB-25  | 4500      |
| 15151  | 21-FEB-25  | 2000      |
| 22222  | 21-FEB-25  | 4750      |
| 32343  | 21-FEB-25  | 3000      |
| 33456  | 21-FEB-25  | 4350      |

---

### `gpa` Table:

| ID    | GPA |
|-------|-----|
| 00128 | 3.8 |
| 12345 | 2.5 |
| 19991 | 3.4 |
| 23121 | 2.9 |
| 44553 | 3.2 |
| 45678 | 1.9 |
| 54321 | 3.0 |
| 55739 | 2.8 |
| 70557 | 1.5 |
| 76543 | 3.7 |

---

### `student_courses` Table:

| STUDE | COURSE_I | SEC_ID | SEMEST | YEAR |
|-------|----------|--------|--------|------|
| 00128 | CS-101  | 1      | Fall   | 2009 |
| 12345 | CS-101  | 1      | Fall   | 2009 |
| 19991 | HIS-351 | 1      | Spring | 2010 |
| 23121 | FIN-201 | 1      | Spring | 2010 |
| 44553 | PHY-101 | 1      | Fall   | 2009 |
| 45678 | CS-101  | 1      | Fall   | 2009 |
| 54321 | CS-101  | 1      | Fall   | 2009 |
| 55739 | MU-199  | 1      | Spring | 2010 |
| 76543 | CS-101  | 1      | Fall   | 2009 |
| 76653 | EE-181  | 1      | Spring | 2009 |
| 98765 | CS-101  | 1      | Fall   | 2009 |
| 98988 | BIO-101 | 1      | Summer | 2009 |

