show databases;

use assignments;

show tables;

select * from department;
select * from designation;
select * from employee;

-- 1.
select dept_code, min(basic) as min_basic, max(basic) as max_basic, avg(basic) as avg_basic from employee group by dept_code;

-- 2.
select dept_code, count(*) as female_employee from employee where sex = 'F' group by dept_code; 

-- 3.
select dept_code, city, count(*) as employee from employee group by dept_code, city order by dept_code, city asc;

-- 4.
SELECT DEPT_CODE,
       DESIG_CODE,
       COUNT(*) AS NO_OF_EMPLOYEES
FROM EMPLOYEE
WHERE YEAR(JN_DT) = 2000
GROUP BY DEPT_CODE, DESIG_CODE
ORDER BY NO_OF_EMPLOYEES ASC;

SELECT D.DEPT_CODE,
       D.DEPT_NAME,
       G.DESIG_DESC,
       COUNT(*) AS NO_OF_EMPLOYEES
FROM EMPLOYEE E
JOIN DEPARTMENT D
    ON E.DEPT_CODE = D.DEPT_CODE
JOIN DESIGNATION G
    ON E.DESIG_CODE = G.DESIG_CODE
WHERE YEAR(E.JN_DT) = 2000
GROUP BY D.DEPT_CODE,
         D.DEPT_NAME,
         G.DESIG_DESC
ORDER BY NO_OF_EMPLOYEES ASC;


-- 5.
SELECT DEPT_CODE,
       SUM(BASIC) AS TOTAL_BASIC
FROM EMPLOYEE
WHERE SEX = 'M'
GROUP BY DEPT_CODE
HAVING SUM(BASIC) > 50000
ORDER BY TOTAL_BASIC DESC;

-- 6
select E.emp_name, D.desig_desc, E.basic from Employee E join Designation D on e.desig_code = d.desig_code;

-- 7
select e.emp_name, d.desig_desc, de.dept_name, e.basic from employee e join designation d on e.desig_code = d.desig_code join department de on e.dept_code = de.dept_code;

-- 8.
SELECT D.DEPT_CODE
FROM DEPARTMENT D
LEFT JOIN EMPLOYEE E
    ON D.DEPT_CODE = E.DEPT_CODE
GROUP BY D.DEPT_CODE
HAVING COUNT(E.EMP_CODE) = 0;

-- 9.
select d.dept_name from employee e join department d on e.dept_code = d.dept_code group by e.dept_code having count(*) >= 1;


-- 10.
select d.dept_name from employee e join department d on e.dept_code = d.dept_code group by e.dept_code having count(*) >= 10;

-- 11.
SELECT DEPT_CODE
FROM EMPLOYEE
WHERE BASIC = (
    SELECT MAX(BASIC)
    FROM EMPLOYEE
);

-- 12. Find the Designation description of the employee with highest basic.
select d.desig_desc from employee e join designation d on e.desig_code = d.desig_code where basic = (
	select max(basic) from employee
);


-- 13. Find the no. of managers in each department.
select d.dept_name, count(*) as managers from employee e join department d on e.dept_code = d.dept_code join designation ds on e.desig_code = ds.desig_code where ds.desig_desc = 'Manager' group by d.dept_name;

-- 14. Find the maximum basic from EMP table without using MAX().
select basic as max_basic from employee order by basic desc limit 1;

-- 15. Find the minimum basic from EMP table without using MIN()
select basic as min_basic from employee order by basic asc limit 1;

-- 16. Find the name of the department with highest total basic. Do the same for highest average basic and maximum no. of employee.
select d.dept_name from employee e join department d on e.dept_code = d.dept_code order by basic desc limit 1;
SELECT d.dept_name
FROM employee e
JOIN department d
    ON e.dept_code = d.dept_code
WHERE e.basic = (
    SELECT MAX(basic)
    FROM employee
);

select d.desig_desc from employee e join designation d on e.desig_code = d.desig_code where basic = (
	select max(basic) from employee
);

SELECT d.DESIG_DESC,
       e.DEPT_CODE,
       SUM(e.BASIC) AS TOTAL_BASIC
FROM EMPLOYEE e
JOIN DESIGNATION d
    ON e.DESIG_CODE = d.DESIG_CODE
WHERE e.SEX = 'M'
GROUP BY e.DEPT_CODE, d.DESIG_DESC
HAVING SUM(e.BASIC) > 50000
ORDER BY TOTAL_BASIC DESC
LIMIT 1;


-- 17. Insert same rows into EMP table with designation code not existing in DESIGNATION table.
INSERT INTO EMPLOYEE
VALUES
('E2001','Rohan Das','DP001','D999',
 'M','Park Road','Kolkata','WB',
 '700001',30000,'2024-01-01');

-- 18. Delete the rows from EMP table with invalid DESIG_CODE. 
SELECT *
FROM EMPLOYEE E
WHERE NOT EXISTS (
    SELECT 1
    FROM DESIGNATION D
    WHERE D.DESIG_CODE = E.DESIG_CODE
);

-- 19. 
SELECT E1.EMP_NAME
FROM EMPLOYEE E1
WHERE E1.SEX = 'F'
AND E1.BASIC > (
    SELECT AVG(E2.BASIC)
    FROM EMPLOYEE E2
    WHERE E2.DEPT_CODE = E1.DEPT_CODE
);

-- 20.
SELECT COUNT(*) AS FEMALE_MANAGERS
FROM EMPLOYEE E
JOIN DESIGNATION D
    ON E.DESIG_CODE = D.DESIG_CODE
WHERE E.SEX = 'F'
AND D.DESIG_DESC = 'Manager';