SET SERVEROUTPUT ON;
SET VERIFY OFF;
SET LINESIZE 200;

ACCEPT T_FROM CHAR PROMPT 'Enter From Date (DD-MON-YYYY): '
ACCEPT T_TO   CHAR PROMPT 'Enter To Date (DD-MON-YYYY): '

DECLARE
BEGIN
    DBMS_OUTPUT.PUT_LINE('PENDING DELIVERY REPORT');
    DBMS_OUTPUT.PUT_LINE('-----------------------');
    FOR R IN
    (
        SELECT
            OD.ORDER_NO,
            OD.ITEM_NO,
            OD.QTY AS ORDER_QTY,
            NVL(SUM(DD.QTY),0) AS DELIVERED_QTY,
            OD.QTY - NVL(SUM(DD.QTY),0) AS PENDING_QTY
        FROM ORDERMAST OM JOIN ORDERDETAILS OD
            ON OM.ORDER_NO = OD.ORDER_NO
        LEFT JOIN DELIVERYMAST DM
            ON OM.ORDER_NO = DM.ORDER_NO
        LEFT JOIN DELIVERY_DETAILS DD
            ON DM.DELV_NO = DD.DELV_NO AND OD.ITEM_NO = DD.ITEM_NO
        WHERE OM.ORDER_DT BETWEEN
            TO_DATE('&T_FROM','DD-MON-YYYY')
        AND TO_DATE('&T_TO','DD-MON-YYYY')
        GROUP BY
            OD.ORDER_NO,
            OD.ITEM_NO,
            OD.QTY
        HAVING
            OD.QTY - NVL(SUM(DD.QTY),0) > 0
        ORDER BY
            OD.ORDER_NO,
            OD.ITEM_NO
    )
    LOOP
        DBMS_OUTPUT.PUT_LINE(
            'ORDER NO : ' || R.ORDER_NO ||
            ' ITEM NO : ' || R.ITEM_NO ||
            ' ORDERED QTY : ' || R.ORDER_QTY ||
            ' DELIVERED QTY : ' || R.DELIVERED_QTY ||
            ' PENDING : ' || R.PENDING_QTY
        );
    END LOOP;
END;
/