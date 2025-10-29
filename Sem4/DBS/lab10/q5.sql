-- Q5
-- Based on the University database Schema in Lab 2, create a view Advisor_Student
-- which is a natural join on Advisor, Student and Instructor tables. Create an
-- INSTEAD OF trigger on Advisor_Student to enable the user to delete the
-- corresponding entries in Advisor table.

-- Create the View (Corrected)
CREATE OR REPLACE VIEW Advisor_Student AS
SELECT DISTINCT s.ID AS s_ID, a.i_id AS a_id
FROM student s
JOIN advisor a ON a.s_ID = s.ID
JOIN instructor i ON a.i_id = i.id;

-- Create the INSTEAD OF Trigger for Insert and Delete operations
CREATE OR REPLACE TRIGGER advisor_student_trigger
INSTEAD OF INSERT OR DELETE ON Advisor_Student
FOR EACH ROW
BEGIN
    -- Handle DELETE operation: Delete corresponding record from the advisor table
    IF DELETING THEN
        DELETE FROM advisor
        WHERE s_ID = :OLD.s_ID
        AND i_ID = :OLD.a_id;  -- Use :OLD.a_id instead of :OLD.i_id
    END IF;
    
    -- Handle INSERT operation: Insert corresponding record into the advisor table
    IF INSERTING THEN
        INSERT INTO advisor (s_ID, i_id)
        VALUES (:NEW.s_ID, :NEW.a_id);  -- Use :NEW.a_id instead of :NEW.i_id
    END IF;
END;
/


-- Insert a row into the Advisor_Student view
INSERT INTO Advisor_Student (s_ID, a_id)
VALUES (101, 202);  -- Replace with appropriate student ID and instructor ID

-- Check the advisor table to confirm the insert
SELECT * FROM advisor WHERE s_ID = 101 AND i_id = 202;
