-- SELECT "CHRIS" AS "QUERY RUNNER", now() AS "QUERY DATE";

CREATE DATABASE airsupply;

USE airsupply;

CREATE TABLE vendor (
vendor_id VARCHAR(10),
vendor_name VARCHAR(32),
PRIMARY KEY (vendor_id)
) ENGINE=INNODB;

CREATE TABLE product (
product_id VARCHAR(10),
vendor_id VARCHAR(10),
product_name VARCHAR(32),
product_description VARCHAR(128),
product_price DECIMAL(5,2),
PRIMARY KEY (product_id),
FOREIGN KEY (vendor_id) REFERENCES vendor(vendor_id)
) ENGINE=INNODB;

CREATE TABLE orders (
order_id VARCHAR(10),
accounts_payable_terms INT,
order_date DATE,
arrival_date DATE,
PRIMARY KEY (order_id)
) ENGINE=INNODB;

CREATE TABLE line (
order_id VARCHAR(10),
line_number INT,
vendor_id VARCHAR(10),
product_id VARCHAR(10),
product_name VARCHAR(32),
product_description VARCHAR(128),
product_price DECIMAL(5,2),
order_quantity INT,
cost_per_order DECIMAL(7,2),
PRIMARY KEY (order_id, line_number),
FOREIGN KEY (order_id) REFERENCES orders(order_id),
FOREIGN KEY (vendor_id) REFERENCES vendor(vendor_id),
FOREIGN KEY (product_id) REFERENCES product(product_id)
) ENGINE=INNODB;