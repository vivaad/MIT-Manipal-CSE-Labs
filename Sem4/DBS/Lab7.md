# Lab 7: PL/SQL Basics

## Objective
This lab is focused on understanding and implementing various PL/SQL concepts such as loops, conditional statements, exception handling, and database manipulation in PL/SQL.

---

## Questions and Answers

### 1. Write a PL/SQL block to display the GPA of a given student.

#### Solution:
```sql
DECLARE 
    ROLL STUD.RNO%TYPE;
    GPA STUD.GPA%TYPE;
BEGIN
    ROLL := &ROLLNO;
    SELECT GPA INTO GPA FROM STUD WHERE ROLL = ROLL;
    DBMS_OUTPUT.PUT_LINE('GPA of student ' || TO_CHAR(ROLL) || ' is ' || TO_CHAR(GPA));
END;
/
```

---

### 2. Write a PL/SQL block to display the letter grade (0-4: F; 4-5: E; 5-6: D; 6-7: C; 7-8: B; 8-9: A; 9-10: A+) of a given student.

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE
    gpa NUMBER(3,1);
    grade CHAR(2);
BEGIN
    gpa := &GPA;
    
    IF gpa < 4 THEN
        grade := 'F';
    ELSIF gpa < 5 THEN
        grade := 'E';
    ELSIF gpa < 6 THEN
        grade := 'D';
    ELSIF gpa < 7 THEN
        grade := 'C';
    ELSIF gpa < 8 THEN
        grade := 'B';
    ELSIF gpa < 9 THEN
        grade := 'A';
    ELSE
        grade := 'A+';
    END IF;
    
    DBMS_OUTPUT.PUT_LINE('The letter grade is: ' || grade);
END;
/
```

---

### 3. Input the date of issue and date of return for a book. Calculate and display the fine with the appropriate message using a PL/SQL block.

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE
    issue_date DATE := TO_DATE('&ISSUE_DATE', 'YYYY-MM-DD');
    return_date DATE := TO_DATE('&RETURN_DATE', 'YYYY-MM-DD');
    fine NUMBER := 0;
    late_days NUMBER;
BEGIN
    late_days := return_date - issue_date;
    
    IF late_days > 30 THEN
        fine := late_days * 5;
        DBMS_OUTPUT.PUT_LINE('Fine: Rs. ' || fine);
    ELSIF late_days > 15 THEN
        fine := late_days * 2;
        DBMS_OUTPUT.PUT_LINE('Fine: Rs. ' || fine);
    ELSIF late_days > 7 THEN
        fine := late_days;
        DBMS_OUTPUT.PUT_LINE('Fine: Rs. ' || fine);
    ELSE
        DBMS_OUTPUT.PUT_LINE('No fine');
    END IF;
END;
/
```

---

### 4. Write a PL/SQL block to print the letter grade of all students (RollNo: 1 - 5).

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE
    rno NUMBER;
    gpa NUMBER(3,1);
    grade CHAR(2);
BEGIN
    FOR rno IN 1..5 LOOP
        SELECT GPA INTO gpa FROM STUD WHERE RNO = rno;

        IF gpa < 4 THEN
            grade := 'F';
        ELSIF gpa < 5 THEN
            grade := 'E';
        ELSIF gpa < 6 THEN
            grade := 'D';
        ELSIF gpa < 7 THEN
            grade := 'C';
        ELSIF gpa < 8 THEN
            grade := 'B';
        ELSIF gpa < 9 THEN
            grade := 'A';
        ELSE
            grade := 'A+';
        END IF;

        DBMS_OUTPUT.PUT_LINE('RollNo ' || rno || ' has grade: ' || grade);
    END LOOP;
END;
/
```

---

### 5. Alter StudentTable by appending an additional column `LetterGrade VARCHAR2(2)`. Then write a PL/SQL block to update the table with letter grade of each student.

#### Solution:
```sql
ALTER TABLE STUD ADD (LetterGrade VARCHAR2(2));

SET SERVEROUTPUT ON
DECLARE
    rno NUMBER;
    gpa NUMBER(3,1);
    grade CHAR(2);
BEGIN
    FOR rno IN 1..5 LOOP
        SELECT GPA INTO gpa FROM STUD WHERE RNO = rno;

        IF gpa < 4 THEN
            grade := 'F';
        ELSIF gpa < 5 THEN
            grade := 'E';
        ELSIF gpa < 6 THEN
            grade := 'D';
        ELSIF gpa < 7 THEN
            grade := 'C';
        ELSIF gpa < 8 THEN
            grade := 'B';
        ELSIF gpa < 9 THEN
            grade := 'A';
        ELSE
            grade := 'A+';
        END IF;

        UPDATE STUD SET LetterGrade = grade WHERE RNO = rno;
    END LOOP;
END;
/
```

---

### 6. Write a PL/SQL block to find the student with the maximum GPA without using aggregate function.

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE
    rno NUMBER;
    max_gpa NUMBER := 0;
    student_rno NUMBER;
BEGIN
    FOR rno IN 1..5 LOOP
        SELECT GPA INTO max_gpa FROM STUD WHERE RNO = rno;
        
        IF max_gpa > max_gpa THEN
            student_rno := rno;
        END IF;
    END LOOP;

    DBMS_OUTPUT.PUT_LINE('Student with max GPA: ' || student_rno);
END;
/
```

---

### 7. Implement lab exercise 4 using GOTO.

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE
    rno NUMBER;
    gpa NUMBER(3,1);
    grade CHAR(2);
BEGIN
    FOR rno IN 1..5 LOOP
        SELECT GPA INTO gpa FROM STUD WHERE RNO = rno;

        IF gpa < 4 THEN
            grade := 'F';
            GOTO PRINT_GRADE;
        ELSIF gpa < 5 THEN
            grade := 'E';
            GOTO PRINT_GRADE;
        ELSIF gpa < 6 THEN
            grade := 'D';
            GOTO PRINT_GRADE;
        ELSIF gpa < 7 THEN
            grade := 'C';
            GOTO PRINT_GRADE;
        ELSIF gpa < 8 THEN
            grade := 'B';
            GOTO PRINT_GRADE;
        ELSIF gpa < 9 THEN
            grade := 'A';
            GOTO PRINT_GRADE;
        ELSE
            grade := 'A+';
        END IF;

    <<PRINT_GRADE>>
        DBMS_OUTPUT.PUT_LINE('RollNo ' || rno || ' has grade: ' || grade);
    END LOOP;
END;
/
```

---

### 8. Based on the University database schema, write a PL/SQL block to display the details of the Instructor whose name is supplied by the user. Use exceptions to show appropriate error messages for the following cases:
- a. Multiple instructors with the same name
- b. No instructor for the given name

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE
    instructor_name VARCHAR2(50);
    instructor_count NUMBER;
BEGIN
    instructor_name := '&INSTRUCTOR_NAME';
    
    SELECT COUNT(*) INTO instructor_count
    FROM INSTRUCTOR
    WHERE NAME = instructor_name;

    IF instructor_count > 1 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Multiple instructors with the same name');
    ELSIF instructor_count = 0 THEN
        RAISE_APPLICATION_ERROR(-20002, 'No instructor found with the given name');
    ELSE
        SELECT * FROM INSTRUCTOR WHERE NAME = instructor_name;
    END IF;
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE(SQLERRM);
END;
/
```

---

## Additional Exercises

### 1. A PL/SQL block to display the grade for a given letter grade:

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE
    grade CHAR(1);
BEGIN
    grade := '&g';
    IF grade = 'A' THEN 
        DBMS_OUTPUT.PUT_LINE('EXCELLENT');
    ELSIF grade = 'B' THEN
        DBMS_OUTPUT.PUT_LINE('VERY GOOD');
    ELSIF grade = 'C' THEN
        DBMS_OUTPUT.PUT_LINE('GOOD');
    ELSIF grade = 'D' THEN
        DBMS_OUTPUT.PUT_LINE('FAIR');
    ELSIF grade = 'F' THEN
        DBMS_OUTPUT.PUT_LINE('POOR');
    ELSE 
        DBMS_OUTPUT.PUT_LINE('NO SUCH GRADE');
    END IF;
END;
/
```

---

### 2. The following PL/SQL block traces the control flow in a simple LOOP construct:

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE 
    x NUMBER := 0;
BEGIN
    LOOP
        DBMS_OUTPUT.PUT_LINE('INSIDE LOOP: X = '|| TO_CHAR(x));
        x := x + 1;
        IF X > 3 THEN 
            EXIT;
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('AFTER LOOP: X = '|| TO_CHAR(X));
END;
/
```

---

### 3. The following PL/SQL block traces the control flow in a while LOOP:

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE X NUMBER := 0;
BEGIN
    WHILE X < 4 LOOP
        DBMS_OUTPUT.PUT_LINE('INSIDE LOOP: X = '|| TO_CHAR(X));
        X := X + 1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('AFTER LOOP: X = '|| TO_CHAR(X));
END;
/
```

---

### 4. The following PL/SQL block traces the control flow in a FOR LOOP:

#### Solution:
```sql
SET SERVEROUTPUT ON
BEGIN
    DBMS_OUTPUT.PUT_LINE('LOWER BOUND < UPPER BOUND');
    FOR I IN 1..3 LOOP
        DBMS_OUTPUT.PUT_LINE(I);
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('LOWER BOUND = UPPER BOUND');
    FOR I IN 2..2 LOOP
        DBMS_OUTPUT.PUT_LINE(I);
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('LOWER BOUND > UPPER BOUND');
    FOR I IN 3..1 LOOP
        DBMS_OUTPUT.PUT_LINE(I);
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('UPPER BOUND TO LOWER BOUND');
    FOR I IN REVERSE 1..3 LOOP
        DBMS_OUTPUT.PUT_LINE(I);
    END LOOP;
END;
/
```

---

### 5. A PL/SQL block to check whether a given number is a prime number:

#### Solution:
```sql
SET SERVEROUTPUT ON
DECLARE 
    P VARCHAR2(30);
    N PLS_INTEGER := 36; --37
BEGIN
    FOR J IN 2..ROUND(SQRT(N)) LOOP
        IF N MOD J = 0 THEN
            P := ' IS NOT A PRIME NUMBER';
            GOTO PRINT_NOW;
        END IF;
    END LOOP;
    P := ' IS A PRIME NUMBER';
<<PRINT_NOW>>
    DBMS_OUTPUT.PUT_LINE(TO_CHAR(N) || P);
END;
/
```
