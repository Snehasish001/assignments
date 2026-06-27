SET SERVEROUTPUT ON;

DECLARE
   R EMP%ROWTYPE;
BEGIN
   SELECT *
   INTO R
   FROM EMP
   WHERE ROWNUM = 1;

   DBMS_OUTPUT.PUT_LINE(
      R.ECODE || ' | ' ||
      R.ENAME || ' | ' ||
      R.DCODE || ' | ' ||
      R.GRADE || ' | ' ||
      R.BASIC || ' | ' ||
      TO_CHAR(R.JN_DT,'DD-MON-YYYY')
   );
END;
/