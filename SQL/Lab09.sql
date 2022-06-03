-- Section 2
USE abc;

CALL sp_cust_payment(10020, 100.0, 'CASH', '2019-10-21 00:00:00', 'Cash payment of $100');
SELECT * FROM PAYMENTS;

-- DELIMITER //
-- CREATE PROCEDURE sp_cust_payment(
-- 	IN cus_code INT,
--     IN pmt_amt FLOAT,
--     IN pmt_type VARCHAR(5),
-- 	IN trans_date DATETIME,
--     IN pmt_details VARCHAR(128))
-- BEGIN
-- 	DECLARE own VARCHAR(32);
--     SELECT CUSTOMER.CUS_FNAME INTO own
-- 		FROM CUSTOMER
--         WHERE CUSTOMER.CUS_CODE = cus_code;
-- 	
--     INSERT INTO PAYMENTS(PMT_DATE, CUS_CODE, PMT_AMT, PMT_TYPE, PMT_DETAILS, OWNER) VALUES(trans_date, cus_code, pmt_amt, pmt_type, pmt_details, own);
--     UPDATE CUSTOMER
-- 		SET CUSTOMER.CUS_BALANCE = (CUSTOMER.CUS_BALANCE - pmt_amt),
-- 			CUSTOMER.CUS_DATELSTPMT = trans_date
--         WHERE CUSTOMER.CUS_CODE = cus_code;
-- 	
-- END //
-- DELIMITER ;

-- DELETE FROM LINE
-- 	WHERE INV_NUMBER = 1009;
--     
-- DELETE FROM INVOICE
-- 	WHERE INV_NUMBER = 1009;
--     
-- UPDATE CUSTOMER
-- 	SET CUS_BALANCE = 0
--     WHERE CUS_CODE = 10020;

-- UPDATE PRODUCT
-- 	SET P_QTYOH = 8
--     WHERE P_CODE LIKE '11QER/31';
-- SELECT * FROM PRODUCT;

-- CALL sp_cust_purchase(10020, '11QER/31', 3, '30', '2019-10-19 00:00:00');
-- CALL sp_cust_purchase(10020, '89-WRE-q', 3, 'CASH', '2019-10-16 00:00:00');
-- SELECT * FROM INVOICE;
-- SELECT * FROM LINE;
-- SELECT * FROM CUSTOMER;

-- DELIMITER //
-- CREATE PROCEDURE sp_cust_purchase(
-- 	IN cus_code INT, 
-- 	IN p_code VARCHAR(10), 
-- 	IN quantity INT,
--     IN inv_terms VARCHAR(5),
--     IN trans_date DATETIME)
-- BEGIN
-- -- Declaring my local variables
-- 	DECLARE inv_number INT;
--     DECLARE line_price FLOAT;
--     DECLARE on_hand INT DEFAULT 0;
--     DECLARE inv_stat VARCHAR(6) DEFAULT "OPEN";
-- -- Checking the values stored in the variables
--     SELECT PRODUCT.P_QTYOH INTO on_hand 
-- 		FROM PRODUCT 
--         WHERE PRODUCT.P_CODE LIKE p_code;
--     SELECT PRODUCT.P_PRICE INTO line_price 
-- 		FROM PRODUCT 
--         WHERE PRODUCT.P_CODE LIKE p_code;
-- 	SET line_price = line_price * quantity;
--     IF (inv_terms IN ("CASH", "CHECK", "CC")) THEN
-- 		SET inv_stat = "CLOSED";
--     END IF;
--     
--     SELECT cus_code, p_code, quantity, inv_terms, trans_date, on_hand, line_price;
--         
-- -- Check to make sure that we had the correct quantity on hand and if new quantity is lower than 0, rollback all changes
-- 	IF (on_hand >= quantity) THEN 
-- -- 		Updating on hand quantity
-- 		UPDATE PRODUCT
-- 			SET PRODUCT.P_QTYOH = PRODUCT.P_QTYOH - quantity
-- 			WHERE PRODUCT.P_CODE LIKE p_code;

-- -- 		Finding invoice number and transaction number that will be used to insert the new record
-- 		SELECT MAX(INVOICE.INV_NUMBER) INTO inv_number
-- 			FROM INVOICE;
-- 		SET inv_number = inv_number+1;

-- -- 		Inserting the new records into appropriate tables
-- 		INSERT INTO INVOICE VALUES(inv_number, cus_code, trans_date, (line_price*1.08), inv_terms, inv_stat);
-- 		INSERT INTO LINE VALUES(inv_number, 1, p_code, quantity, line_price);
--         UPDATE CUSTOMER
--                 SET CUSTOMER.CUS_DATELSTPUR = trans_date
-- 				WHERE CUSTOMER.CUS_CODE = cus_code;
-- 		IF (inv_terms IN ("30", "60", "90")) THEN
-- 			UPDATE CUSTOMER
-- 				SET CUSTOMER.CUS_BALANCE = CUSTOMER.CUS_BALANCE + (line_price*1.08)
-- 				WHERE CUSTOMER.CUS_CODE = cus_code;
-- 		END IF;
-- 	END IF;
-- END //
-- DELIMITER ;

-- SELECT * FROM CUSTOMER;
-- SELECT * FROM chris_valencia;

-- CREATE TABLE PAYMENTS (
-- 	PMT_ID INT NOT NULL AUTO_INCREMENT,
--     PMT_DATE DATETIME,
--     CUS_CODE INT,
--     PMT_AMT FLOAT,
--     PMT_TYPE VARCHAR(5),
--     PMT_DETAILS VARCHAR(128),
--     OWNER VARCHAR(15),
--     PRIMARY KEY (PMT_ID),
--     FOREIGN KEY (CUS_CODE) REFERENCES CUSTOMER(CUS_CODE),
--     CONSTRAINT CHK_PMT_TYPE CHECK (PMT_TYPE IN ('CASH', 'CHECK', 'CC', '30', '60', '90'))
-- ) ENGINE=INNODB;

-- CREATE TABLE chris_valencia (
-- 	CUS_CODE INT,
--     PRIMARY KEY (CUS_CODE),
--     FOREIGN KEY (CUS_CODE) REFERENCES CUSTOMER(CUS_CODE)
-- ) ENGINE=INNODB;

-- INSERT INTO CUSTOMER VALUES(10020, 'Valencia', 'Chris', 'F', '626', '483-0813', NULL, 0, NULL, NULL);
-- INSERT INTO chris_valencia VALUES(10020);
-- --------------------------------------------------------------------------------------------------------

-- Section 1 question 2

--  use saleco;

--  SELECT * FROM ACCT_TRANSACTION;
--  SELECT * FROM PRODUCT;
-- --  CALL sp_purchase_order(10010, '11QER/31', 5);
--  CALL sp_purchase_order(10015, "23114-AA", 9);
--  SELECT * FROM PRODUCT;
--  SELECT * FROM ACCT_TRANSACTION;
 
 -- UPDATE PRODUCT
-- 		SET PRODUCT.P_QOH = 8
-- 		WHERE PRODUCT.P_CODE LIKE "23114-AA";

-- DELETE FROM ACCT_TRANSACTION
-- 	WHERE transaction_num = 2;

-- DELIMITER //
-- CREATE PROCEDURE sp_purchase_order(
-- 	IN cus_code INT, 
-- 	IN p_code VARCHAR(10), 
-- 	IN quantity INT)
-- BEGIN
-- -- Declaring my local variables
-- 	DECLARE inv_number INT;
--     DECLARE line_price FLOAT;
-- 	DECLARE trans_date datetime;
--     DECLARE on_hand INT DEFAULT 0;
--     DECLARE trans_num INT DEFAULT 0;
--     
-- -- Checking the values stored in the variables
--     SELECT P_QOH INTO on_hand 
-- 		FROM PRODUCT 
--         WHERE PRODUCT.P_CODE LIKE p_code;
--     SELECT P_PRICE INTO line_price 
-- 		FROM PRODUCT 
--         WHERE PRODUCT.P_CODE LIKE p_code;
-- 	SET line_price = line_price * quantity;
-- 	SELECT cus_code, p_code, quantity, on_hand, line_price;
--     
-- -- Check to make sure that we had the correct quantity on hand and if new quantity is lower than 0, rollback all changes
-- 	IF (on_hand >= quantity) THEN 
-- -- 		Updating on hand quantity
-- 		UPDATE PRODUCT
-- 			SET PRODUCT.P_QOH = PRODUCT.P_QOH - quantity
-- 			WHERE PRODUCT.P_CODE LIKE p_code;

-- -- 		Finding invoice number and transaction number that will be used to insert the new record
-- 		SELECT MAX(INVOICE.INV_NUMBER) INTO inv_number
-- 			FROM INVOICE;
-- 		SET inv_number = inv_number+1;
-- 		SELECT MAX(ACCT_TRANSACTION.transaction_num) INTO trans_num
-- 			FROM ACCT_TRANSACTION;
-- 		SET trans_num = trans_num+1;
-- 		IF trans_num IS NULL THEN
-- 			SET trans_num = 1;
-- 		END IF;

-- -- 		Inserting the new records into appropriate tables
-- 		INSERT INTO INVOICE VALUES(inv_number, cus_code, NOW());
-- 		INSERT INTO LINE VALUES(inv_number, 1, p_code, quantity, line_price);
-- 		INSERT INTO ACCT_TRANSACTION VALUES(trans_num, NOW(), cus_code, "charge", line_price);
-- 	END IF;
-- END //
-- DELIMITER ;

-- Section 1 question 1

-- use saleco;

-- create table ACCT_TRANSACTION (
-- transaction_num INT,
-- transaction_date DATE,
-- cust_code INT,
-- transaction_type VARCHAR(7) CHECK (transaction_type IN ("charge","payment")),
-- transaction_amount DECIMAL(10,2),
-- PRIMARY KEY (transaction_num),
-- FOREIGN KEY (cust_code) REFERENCES CUSTOMER(CUS_CODE)
-- )ENGINE=INNODB;