-- Q1
-- Write a procedure to display a message “Good Day to You”

CREATE OR REPLACE PROCEDURE display_message IS
BEGIN 
    DBMS_OUTPUT.PUT_LINE('Good Day to You');
END;
/

-- SET SERVEROUTPUT on;
-- begin display_message end;
-- /

-- Output
-- Good Day to You