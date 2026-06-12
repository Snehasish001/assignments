-- ============================================================
-- ASSIGNMENT: EMPLOYEE - DEPARTMENT - LEAVE MANAGEMENT SYSTEM
-- MYSQL 8.0+
-- ============================================================

SHOW DATABASES;
USE ASSIGNMENTS;

-- ============================================================
-- QUESTION 1
-- Design & implement the tables with necessary constraints
-- ============================================================

-- Remove old tables if they exist

DROP TABLE IF EXISTS LeaveRegister;
DROP TABLE IF EXISTS Employee;
DROP TABLE IF EXISTS Department;

-- ----------------------------
-- Department Table
-- ----------------------------

CREATE TABLE Department(
    dcode VARCHAR(10) PRIMARY KEY,
    dname VARCHAR(50) NOT NULL UNIQUE,
    no_of_employee INT DEFAULT 0
);


-- ----------------------------
-- Employee Table
-- ----------------------------

CREATE TABLE Employee(
    empcode INT PRIMARY KEY,
    ename VARCHAR(50) NOT NULL,
    address VARCHAR(100),
    city VARCHAR(50),
    basic DECIMAL(8,2),
    doj DATE DEFAULT (CURRENT_DATE),
    grade CHAR(1),
    dcode VARCHAR(10),

    CONSTRAINT chk_basic CHECK (basic BETWEEN 5000 AND 9000),
    CONSTRAINT chk_grade CHECK (grade IN ('A','B','C')),
    CONSTRAINT chk_uppercase CHECK (ename = UPPER(ename)),
    CONSTRAINT fk_emp_dept FOREIGN KEY (dcode) REFERENCES Department(dcode) ON DELETE RESTRICT
);


-- ----------------------------
-- Leave Register Table
-- ----------------------------

CREATE TABLE LeaveRegister(
    leave_id INT AUTO_INCREMENT PRIMARY KEY,
    empcode INT NOT NULL,
    leave_type VARCHAR(10) NOT NULL,
    from_date DATE NOT NULL,
    to_date DATE NOT NULL,

    CONSTRAINT fk_leave_emp FOREIGN KEY(empcode) REFERENCES Employee(empcode) ON DELETE CASCADE
);


-- ============================================================
-- Trigger : Increase employee count after insert
-- ============================================================

DELIMITER //

CREATE TRIGGER trg_emp_insert
AFTER INSERT ON Employee
FOR EACH ROW
BEGIN
    UPDATE Department
    SET no_of_employee = no_of_employee + 1
    WHERE dcode = NEW.dcode;
END//

DELIMITER ;


-- ============================================================
-- Trigger : Decrease employee count after delete
-- ============================================================

DELIMITER //

CREATE TRIGGER trg_emp_delete
AFTER DELETE ON Employee
FOR EACH ROW
BEGIN
    UPDATE Department
    SET no_of_employee = no_of_employee - 1
    WHERE dcode = OLD.dcode;
END//

DELIMITER ;


-- ============================================================
-- Insert Sample Records
-- ============================================================

INSERT INTO Department(dcode,dname) VALUES
('D1','COMPUTER SCIENCE'),
('D2','ELECTRONICS'),
('D3','MATHEMATICS');


INSERT INTO Employee (empcode,ename,address,city,basic,grade,dcode) VALUES
(101,'RAHUL','ABC ROAD','KOLKATA',7000,'A','D1'),
(102,'AMIT','XYZ ROAD','DELHI',6500,'B','D1'),
(103,'SUMAN','PQR ROAD','MUMBAI',8000,'A','D2');


INSERT INTO LeaveRegister (empcode,leave_type,from_date,to_date) VALUES
(101,'CL','2026-01-01','2026-01-03'),
(101,'EL','2026-02-10','2026-02-15'),
(102,'ML','2026-03-01','2026-03-05');



-- ============================================================
-- QUESTION 2
-- Try to violate constraints
-- ============================================================

-- ------------------------------------------------------------
-- 2(a) Salary greater than 9000
-- Expected : Error
-- ------------------------------------------------------------

INSERT INTO Employee(empcode,ename,address,city,basic,grade,dcode) VALUES
(104,'RAKESH','ABC','KOLKATA',10000,'A','D1');


-- ------------------------------------------------------------
-- 2(b) Invalid Grade
-- Expected : Error
-- ------------------------------------------------------------

INSERT INTO Employee (empcode,ename,address,city,basic,grade,dcode) VALUES
(105,'RAMESH','ABC','KOLKATA',7000,'D','D1');


-- ------------------------------------------------------------
-- 2(c) Lowercase Name
-- Expected : Error
-- ------------------------------------------------------------

INSERT INTO Employee (empcode,ename,address,city,basic,grade,dcode) VALUES
(106,'Rahul','ABC','KOLKATA',7000,'A','D1');


-- ------------------------------------------------------------
-- 2(d) Invalid Department Code
-- Expected : Foreign Key Error
-- ------------------------------------------------------------

INSERT INTO Employee(empcode,ename,address,city,basic,grade,dcode) VALUES
(107,'SOUMEN','ABC','KOLKATA',7000,'A','D10');


-- ------------------------------------------------------------
-- 2(e) Delete Department having employees
-- Expected : Error
-- ------------------------------------------------------------

DELETE FROM Department
WHERE dcode='D1';


-- ------------------------------------------------------------
-- 2(f) Delete Employee
-- Leave records should be deleted automatically
-- ------------------------------------------------------------

DELETE FROM Employee
WHERE empcode=101;


SELECT *
FROM LeaveRegister
WHERE empcode=101;



-- ============================================================
-- QUESTION 3(a)
-- Create view showing empcode,name,dcode,basic
-- for department D1
-- ============================================================

CREATE VIEW D1_EMP_VIEW AS
SELECT empcode, ename, dcode, basic FROM Employee WHERE dcode='D1';



-- ============================================================
-- QUESTION 3(b)
-- Insert valid row through view
-- ============================================================

INSERT INTO D1_EMP_VIEW VALUES
(201,'ANIK','D1',7500);


-- ============================================================
-- QUESTION 3(b)
-- Insert invalid row through view
-- Expected : Foreign Key Error
-- ============================================================

INSERT INTO D1_EMP_VIEW VALUES
(202,'ROHIT','D5',7000);



-- ============================================================
-- QUESTION 3(c)
-- Find inserted row in original table
-- ============================================================

SELECT * FROM Employee
WHERE empcode=201;



-- ============================================================
-- QUESTION 3(d)
-- Increment basic by Rs.100
-- ============================================================

UPDATE D1_EMP_VIEW
SET basic = basic + 100;



-- ============================================================
-- QUESTION 3(e)
-- Check original table
-- ============================================================

SELECT empcode, ename, basic
FROM Employee;



-- ============================================================
-- QUESTION 3(f)
-- Delete View
-- ============================================================

DROP VIEW D1_EMP_VIEW;



-- ============================================================
-- QUESTION 4(a)
-- Create Join View
-- ============================================================

CREATE VIEW EMP_LEAVE_VIEW AS
SELECT E.empcode, E.ename, D.dname, E.basic, L.leave_type, L.from_date, L.to_date
FROM Employee E JOIN Department D ON E.dcode = D.dcode
JOIN LeaveRegister L ON E.empcode = L.empcode;



-- ============================================================
-- QUESTION 4(b)
-- Try to Insert into Join View
-- Expected : View not updatable
-- ============================================================

INSERT INTO EMP_LEAVE_VIEW VALUES
(500,'JOY','COMPUTER SCIENCE',7000,'CL','2026-04-01','2026-04-03');



-- ============================================================
-- QUESTION 4(c)
-- Try to Update Join View
-- Expected : Error
-- ============================================================

UPDATE EMP_LEAVE_VIEW
SET basic = basic + 100;



-- ============================================================
-- QUESTION 4(d)
-- Delete View
-- ============================================================

DROP VIEW EMP_LEAVE_VIEW;



-- ============================================================
-- QUESTION 5(a)
-- Create table from existing tables
-- Employees of D1 having Basic = 7000
-- ============================================================

CREATE TABLE D1_EMPLOYEE AS
SELECT E.empcode, E.ename, D.dname, E.basic
FROM Employee E JOIN Department D ON E.dcode = D.dcode
WHERE E.dcode='D1' AND E.basic=7000;



-- ============================================================
-- QUESTION 5(b)
-- Add employees with basic >= 7000
-- ============================================================

INSERT INTO D1_EMPLOYEE
SELECT E.empcode, E.ename, D.dname, E.basic
FROM Employee E JOIN Department D ON E.dcode = D.dcode
WHERE E.basic >= 7000;



-- ============================================================
-- QUESTION 5(c)
-- Add Net Pay Column
-- ============================================================

ALTER TABLE D1_EMPLOYEE
ADD netpay DECIMAL(10,2);



-- ============================================================
-- QUESTION 5(d)
-- Replace Net Pay with 1.5 * Basic
-- ============================================================

UPDATE D1_EMPLOYEE
SET netpay = basic * 1.5;



-- ============================================================
-- Display Table
-- ============================================================

SELECT * FROM D1_EMPLOYEE;



-- ============================================================
-- QUESTION 5(e)
-- Remove Net Pay Column
-- ============================================================

ALTER TABLE D1_EMPLOYEE
DROP COLUMN netpay;



-- ============================================================
-- QUESTION 6
-- Drop all tables
-- ============================================================

DROP TABLE LeaveRegister;

DROP TABLE Employee;

DROP TABLE Department;

DROP TABLE D1_EMPLOYEE;