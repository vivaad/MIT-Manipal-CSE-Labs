--PROCEDURE 
--EX1. Create a procedure to print Hello world and execute the procedure. 
create or replace procedure print_hello is 
begin 
    dbms_output.put_line('Hello World');
end;
/
set serveroutput on; 
begin 
    print_hello;
end;
/

--FUNCTIONS
--EX1.  Create a function to return the sum of two numbers
create or replace function sum_num(a number, b number)
return number as 
    tot number;
begin 
    tot := a + b;
    return tot;
end;
/
set serveroutput on;
begin 
    dbms_output.put_line(sum_num(5,4));
end;
/
--EX2. : A function that, given the name of a department, returns the 
--count of the number of instructors in that department. 
create or replace function dept_count(dept_name varchar)
return integer as 
d_count integer;
begin 
    select count(*) into d_count 
    from instructor where instructor.dept_name = dept_count.dept_name;
    return d_count;
end;
/ 

select dept_name, budget from department where dept_count(dept_name)>2;

--PROCEDURES
--EX1. A procedure that, given the name of a department, returns the 
--count of the number of instructors in that department.
create or replace procedure dept_count_proc(dept_name in varchar, d_count out integer) is
begin 
    select count(*) into d_count from instructor where instructor.dept_name = dept_count_proc.dept_name;
end;
/
set serveroutput on;
declare d_count integer;
begin 
    dept_count_proc('Physics', d_count);
    dbms_output.put_line(d_count);
end;
/

--EX2. The procedure p has two IN parameters, one OUT parameter, and 
--one IN OUT parameter. The OUT and IN OUT parameters are passed by 
--value (the default). The anonymous block invokes p twice, with 
--different actual parameters. Before each invocation, the anonymous 
--block prints the values of the actual parameters. The procedure p 
--prints the initial values of its formal parameters. After each 
--invocation, the anonymous block prints the values of the actual 
--parameters again.
create or replace procedure p(a PLS_INTEGER, b in pls_integer, c out pls_integer, d in out binary_float) IS
begin 
    dbms_output.put_line('Inside procedure p: ');
    dbms_output.put_line('In a = ');
    dbms_output.put_line(NVL(to_char(a), 'null'));
    dbms_output.put_line('In b = ');
    dbms_output.put_line(NVL(to_char(b), 'null'));
    dbms_output.put_line('Out c = ');
    dbms_output.put_line(NVL(to_char(c), 'null'));
    dbms_output.put_line('In out d = ' || to_char(d));
    c := a+10;
    d := 10/b;
end;
/
declare 
    aa constant pls_integer := 1;
    bb pls_integer := 2;
    cc pls_integer := 3;
    dd binary_float := 4;
    ee pls_integer;
    ff binary_float := 5;
begin
    dbms_output.put_line('Before invoking p: ');
    dbms_output.put('aa = ');
    dbms_output.put_line(NVL(to_char(aa), 'null'));
    dbms_output.put('bb = ');
    dbms_output.put_line(NVL(to_char(bb), 'null'));
    dbms_output.put('cc = ');
    dbms_output.put_line(NVL(to_char(cc), 'null'));
    dbms_output.put_line('dd = ' || to_char(dd));
    dbms_output.put('ee = ');
    dbms_output.put_line(NVL(to_char(ee), 'null'));
    dbms_output.put_line('ff = ' || to_char(ff));

    p(aa, bb, cc, dd);

    dbms_output.put_line('After invoking procedure: ');
    dbms_output.put('aa = ');
    dbms_output.put_line(NVL(to_char(aa), 'null'));
    dbms_output.put('bb = ');
    dbms_output.put_line(NVL(to_char(bb), 'null'));
    dbms_output.put('cc = ');
    dbms_output.put_line(NVL(to_char(cc), 'null'));
    dbms_output.put_line('dd = ' || to_char(dd));

    p(1, (bb+3)*4, ee, ff);

    dbms_output.put('ee = ');
    dbms_output.put_line(NVL(to_char(ee), 'null'));
    dbms_output.put_line('ff = '|| to_char(ff));
end;
/

--EXERCISE
--1. Write a procedure to display a message “Good Day to You”.
create or replace procedure message is 
begin 
    dbms_output.put_line('Good Day to You');
end;
/
begin 
    message;
end;
/

--2. Based on the University Database Schema in Lab 2, write a procedure 
--which takes the dept_name as input parameter and lists all the 
--instructors associated with the department as well as list all the 
--courses offered by the department. Also, write an anonymous block 
--with the procedure call.
create or replace procedure listinst(dept_name instructor.dept_name%type) IS
begin 
    cursor c is select * from instructor 
