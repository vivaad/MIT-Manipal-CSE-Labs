-- Q5
-- Write a function to return the Square of a given number and call it from an
-- anonymous block.

set serveroutput on;
create or replace function sqr(num number) 
return number as
begin
	return num*num;
end;
/

-- set serveroutput on;
-- begin dbms_output.put_line(sqr(3)); end;
-- /

-- OUTPUT:
-- 9