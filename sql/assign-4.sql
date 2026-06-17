show databases;
drop database assignments;

create database assignment;
use assignment;

-- 1 a) Create EMP table with ECODE(primary key), ENAME, DCODE, GRADE, BASIC &amp; JN-DT as the
-- columns.[except BASIC &amp; JN-DT,all columns are of char type and site of Grade is 1.]
-- b)Insert number of rows.

create table emp(
	ecode char(4) primary key,
    ename varchar(40),
    dcode char(4),
    grade char(1),
    basic decimal(9,2),
    jn_dt date
);

desc emp;

INSERT INTO EMP (ECODE, ENAME, DCODE, GRADE, BASIC, JN_DT) VALUES
('E001','RAHUL','D001','A',50000.00,'2022-01-15'),
('E002','AMIT','D002','B',45000.00,'2021-06-20'),
('E003','PRIYA','D001','A',55000.00,'2020-03-10'),
('E004','SNEHA','D003','C',35000.00,'2023-02-05'),
('E005','ROHAN','D002','B',48000.00,'2021-11-18'),
('E006','ANITA','D004','A',62000.00,'2019-08-12'),
('E007','VIKAS','D003','B',42000.00,'2020-12-01'),
('E008','POOJA','D001','A',58000.00,'2022-07-25'),
('E009','ARJUN','D005','C',33000.00,'2023-04-11'),
('E010','NEHA','D002','B',47000.00,'2021-09-14'),
('E011','KARAN','D004','A',61000.00,'2018-11-30'),
('E012','RITU','D005','C',36000.00,'2024-01-20'),
('E013','MOHAN','D003','B',44000.00,'2020-05-08'),
('E014','NISHA','D001','A',59000.00,'2022-03-19'),
('E015','DEEPAK','D002','B',49000.00,'2021-10-27'),
('E016','SONALI','D004','A',65000.00,'2019-02-16'),
('E017','MANOJ','D005','C',34000.00,'2023-08-09'),
('E018','KAVITA','D003','B',43000.00,'2020-06-22'),
('E019','AJAY','D001','A',57000.00,'2022-12-05'),
('E020','MEENA','D002','B',46000.00,'2021-04-17');


select * from emp;

-- 2. change the column heading as shown below, So that in subsequent SELECT statement newly set
-- heading will be shown:
-- ECODE EMPLOYEE CODE
-- ENAME NAME
-- DCODE DEPT.CODE
-- JN-DT JONING DATE

SELECT
    ECODE AS 'EMPLOYEE CODE',
    ENAME AS 'NAME',
    DCODE AS 'DEPT.CODE',
    JN_DT AS 'JOINING DATE'
FROM EMP;


-- 3. Set the format of columns as mentioned below, So that in subsequent SELECT statement ,values
-- appear in the specified format:
-- *format of BASIC is such that a value of 7000 will be shown as7,000
-- *Format of GRADE will be such that full column name
-- appears in the display.
-- *For JN-DT format is such that 01-JAN-00 will be shown as JANURY 01,2000

SELECT
    ECODE AS 'EMPLOYEE CODE',
    ENAME AS 'NAME',
    DCODE AS 'DEPT.CODE',
    GRADE AS 'GRADE',
    FORMAT(BASIC,0) AS 'BASIC',
    DATE_FORMAT(JN_DT,'%M %d,%Y') AS 'JOINING DATE'
FROM EMP;

-- 4. a) Show the display attributes of all the columns.
-- b) Show the display attributes of particular column.
-- c) Suppress the newly set attributes of JN-DT .Try a select statement.
-- d) Reset the newly set attributes of JN-DT
-- e) Reset the newly set attributes of all columns.
-- f) Shown the display attributes of all columns.

DESCRIBE EMP;



-- 5. a)Show the records from EMP table in the ascending order of DCODE . DCODE value will be shown
-- only for the first record of that department (same of DCODE is not repeated)
SELECT *
FROM EMP
ORDER BY DCODE;


-- b) Further take measures so that ,after displaying the records of a department it skips one line .
-- c)Further take measures so that records one also ordered on the basic of GRADE with in a
-- department &amp; same GRADE value is not repeated.
SELECT *
FROM EMP
ORDER BY DCODE, GRADE;
-- d) Take measure so that at the end of each GRADE in a department it will show average Basic for that
-- grade in that department. At the end of each department, it will show the average &amp; total Basic for the
-- department. At the end of all departments it will show the overall total basic &amp; average basic.
SELECT
    DCODE,
    GRADE,
    AVG(BASIC) AS AVG_BASIC
FROM EMP
GROUP BY DCODE, GRADE
ORDER BY DCODE, GRADE;



