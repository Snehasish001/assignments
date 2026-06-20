/*=========================================================
1(a) CREATE EMP TABLE
=========================================================*/

CREATE TABLE EMP(
    ECODE CHAR(5) PRIMARY KEY,
    ENAME CHAR(20),
    DCODE CHAR(5),
    GRADE CHAR(1),
    BASIC NUMBER(8,2),
    JN_DT DATE
);

/*=========================================================
1(b) INSERT SAMPLE ROWS
=========================================================*/

INSERT ALL
    INTO EMP VALUES ('E001','RAHUL','D01','A',25000,TO_DATE('10-JAN-2020','DD-MON-YYYY'))
    INTO EMP VALUES ('E002','AMIT','D01','A',28000,TO_DATE('15-FEB-2021','DD-MON-YYYY'))
    INTO EMP VALUES ('E003','SUMAN','D01','B',22000,TO_DATE('20-MAR-2022','DD-MON-YYYY'))
    INTO EMP VALUES ('E004','RINA','D02','A',30000,TO_DATE('12-APR-2020','DD-MON-YYYY'))
    INTO EMP VALUES ('E005','ANITA','D02','B',24000,TO_DATE('22-MAY-2021','DD-MON-YYYY'))
    INTO EMP VALUES ('E006','ARUN','D02','B',26000,TO_DATE('11-JUN-2022','DD-MON-YYYY'))
    INTO EMP VALUES ('E007','JOY','D03','A',35000,TO_DATE('05-JUL-2019','DD-MON-YYYY'))
    INTO EMP VALUES ('E008','PRIYA','D03','C',20000,TO_DATE('16-AUG-2020','DD-MON-YYYY'))
    INTO EMP VALUES ('E009','SOURAV','D03','C',21000,TO_DATE('25-SEP-2021','DD-MON-YYYY'))
SELECT * FROM DUAL;

COMMIT;


/*=========================================================
2. CHANGE COLUMN HEADINGS
=========================================================*/

COLUMN ECODE HEADING 'EMPLOYEE CODE';
COLUMN ENAME HEADING 'NAME';
COLUMN DCODE HEADING 'DEPT.CODE';
COLUMN JN_DT HEADING 'JOINING DATE';
COLUMN

SELECT ECODE, ENAME, DCODE, JN_DT
FROM EMP;

/*=========================================================
3. SET COLUMN FORMATS
=========================================================*/

/* BASIC displayed as 7,000 */
COLUMN BASIC FORMAT 999,999.99;

/* Show complete heading for GRADE */
COLUMN GRADE HEADING 'GRADE';

/* Date shown as JANUARY 01,2000 */
COLUMN JN_DT FORMAT A20;

/*=========================================================
SELECT WITH REQUIRED DATE FORMAT
=========================================================*/

SELECT ECODE,
       ENAME,
       DCODE,
       GRADE,
       BASIC,
       TO_CHAR(JN_DT,'MONTH DD,YYYY') JN_DT
FROM EMP;


/*=========================================================
4(a) DISPLAY ATTRIBUTES OF ALL COLUMNS
=========================================================*/

COLUMN;


/*=========================================================
4(b) DISPLAY ATTRIBUTES OF PARTICULAR COLUMN
=========================================================*/

COLUMN JN_DT;


/*=========================================================
4(c) SUPPRESS NEWLY SET ATTRIBUTES OF JN_DT
=========================================================*/

COLUMN JN_DT OFF;

/* Test */
SELECT * FROM EMP;


/*=========================================================
4(d) RESET ATTRIBUTES OF JN_DT
=========================================================*/
COLUMN JN_DT HEADING 'JOINING DATE'
COLUMN JN_DT FORMAT A20

COLUMN JN_DT        -- show attributes

COLUMN JN_DT CLEAR  -- reset attributes

COLUMN JN_DT        -- verify reset

/*=========================================================
4(e) RESET ATTRIBUTES OF ALL COLUMNS
=========================================================*/

CLEAR COLUMNS;


/*=========================================================
4(f) DISPLAY ATTRIBUTES OF ALL COLUMNS
=========================================================*/

COLUMN;


/*=========================================================
5(a) DISPLAY RECORDS ORDERED BY DEPARTMENT
DCODE SHOWN ONLY ONCE
=========================================================*/

BREAK ON DCODE;

SELECT ECODE,
       ENAME,
       DCODE,
       GRADE,
       BASIC
FROM EMP
ORDER BY DCODE;


/*=========================================================
5(b) SKIP ONE LINE AFTER EACH DEPARTMENT
=========================================================*/

BREAK ON DCODE SKIP 1;

SELECT ECODE,
       ENAME,
       DCODE,
       GRADE,
       BASIC
FROM EMP
ORDER BY DCODE;


/*=========================================================
5(c) ORDER BY DEPARTMENT AND GRADE
DO NOT REPEAT DCODE & GRADE
=========================================================*/

BREAK ON DCODE SKIP 1 ON GRADE;
SELECT ECODE,
       ENAME,
       DCODE,
       GRADE,
       BASIC
FROM EMP
ORDER BY DCODE, GRADE;


/*=========================================================
5(d) COMPUTE AVERAGES AND TOTALS
=========================================================*/

/* Break settings */
BREAK ON DCODE SKIP 1 ON GRADE SKIP 1;

/* Average BASIC for each grade */
COMPUTE AVG OF BASIC ON GRADE;

/* Average and Total BASIC for each department */
COMPUTE AVG OF BASIC ON DCODE;
COMPUTE SUM OF BASIC ON DCODE;

/* Overall Average and Total BASIC */
COMPUTE AVG OF BASIC ON REPORT;
COMPUTE SUM OF BASIC ON REPORT;

/* Final Report */

SELECT ECODE,
       ENAME,
       DCODE,
       GRADE,
       BASIC
FROM EMP
ORDER BY DCODE, GRADE;


/*=========================================================
OPTIONAL: CLEAR BREAKS & COMPUTES AFTER USE
=========================================================*/

CLEAR BREAKS;
CLEAR COMPUTES;