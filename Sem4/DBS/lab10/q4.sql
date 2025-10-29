--4.  Create a transparent audit system for a table Client_master (client_no, name, address, Bal_due). 
--The system must keep track of the records that are being deleted or updated. The functionality 
--being when a record is deleted or modified the original record details and the date of operation 
--are stored in the auditclient (client_no, name, bal_due, operation, userid, opdate) table, 
--then the delete or update is allowed to go through.

create table client_master(client_no number primary key, name varchar2(20), address varchar2(20), bal_due number(8, 2));
create table auditclient(client_no number primary key, name varchar2(20), bal_due number(8, 2), operation varchar2(20) check (operation in ('UPDATE', 'DELETE')), userid varchar2(20), opdate date);

create or replace trigger audit_changes 
before delete or update on client_master 
for each row 
declare v_userid varchar2(50);
begin 
    v_userid := USER;
    if deleting then 
        insert into auditclient values (:old.client_no, :old.name, :old.bal_due, 'DELETE', v_userid, SYSDATE);
    elsif updating then 
        insert into auditclient values(:old.client_no, :old.name, :old.bal_due, 'UPDATE', v_userid, SYSDATE);
    end if;
end;
/

--test 
INSERT INTO Client_master VALUES (101, 'John Doe', '123 Main St', 1000);
INSERT INTO Client_master VALUES (102, 'Jane Smith', '456 Elm St', 2000);

update client_master set name = 'John Doe Updated', bal_due = 500 where client_no = 101;
delete from client_master where client_no = 102;

select * from client_master;

-- Output:
--  CLIENT_NO NAME                 ADDRESS                 BAL_DUE
-- ---------- -------------------- -------------------- ----------
--        101 John Doe Updated     123 Main St                 500

select * from auditclient;

--  CLIENT_NO NAME                    BAL_DUE OPERATION
-- ---------- -------------------- ---------- --------------------
-- USERID               OPDATE
-- -------------------- ---------
--        101 John Doe                   1000 UPDATE
-- A50                  25-MAR-25

--        102 Jane Smith                 2000 DELETE
-- A50                  25-MAR-25