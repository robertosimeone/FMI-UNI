USE master
GO
if exists (select * from sysdatabases where name='pcstore')
	DROP DATABASE pcstore
GO

CREATE DATABASE pcstore
GO
USE pcstore
GO

CREATE TABLE product(
 id int NOT NULL,
 prod_type varchar(15) NOT NULL,
 prod_brand varchar(10) NOT NULL
 );

CREATE TABLE videocard(
	item_id int NOT NULL,
	vc_name varchar(22) NOT NULL,
	size int NOT NULL,
	warranty int,
	price float NOT NULL,
	quantity int NOT NULL 
);

CREATE TABLE memory(
	item_id int NOT NULL,
	mem_name varchar(22) NOT NULL,
	rgb_light char(1) NOT NULL,
	size int NOT NULL,
	warranty int,
	price float NOT NULL,
	quantity int NOT NULL
);

CREATE TABLE mouse(
	item_id int NOT NULL,
	mouse_name varchar(22) NOT NULL,
	sensor varchar(7) NOT NULL,
	mouse_sens int NOT NULL,
	warranty int,
	price float NOT NULL,
	quantity int NOT NULL 
);
CREATE TABLE headphones(
	item_id int NOT NULL,
	hp_name varchar(22) NOT NULL,
	microphone char(1) NOT NULL,
	warranty int,
	price float NOT NULL,
	quantity int NOT NULL 

);
CREATE TABLE corder(
	item_id int NOT NULL,
	order_id int NOT NULL,
	customer_id int NOT NULL,
	payment_status varchar(15) NOT NULL,
	quantity int NOT NULL
);

CREATE TABLE customer(
	id int NOT NULL,
	cust_name varchar(15) NOT NULL,
	cust_surname varchar(15) NOT NULL,
	customer_cardn char(16),
);

CREATE TABLE custaddress(
	customer_id int NOT NULL,
	city_name varchar(16) NOT NULL,
	street_name varchar(16) NOT NULL,
	ap_building varchar(16) NOT NULL
);

CREATE TABLE wishlist(
	customer_id int NOT NULL,
	item_id int NOT NULL
);

---------------------------------------------/*PRIMARY KEYS*/

ALTER TABLE videocard ADD CONSTRAINT PK_videocards PRIMARY KEY(vc_name); 

ALTER TABLE memory ADD CONSTRAINT PK_memory PRIMARY KEY(mem_name);

ALTER TABLE product ADD	CONSTRAINT PK_product PRIMARY KEY (id);

ALTER TABLE mouse ADD CONSTRAINT PK_mouse PRIMARY KEY(mouse_name);

ALTER TABLE headphones ADD CONSTRAINT PK_headphones PRIMARY KEY(hp_name);

ALTER TABLE corder ADD CONSTRAINT PK_corder PRIMARY KEY(item_id,order_id);

ALTER TABLE customer ADD CONSTRAINT PK_customer PRIMARY KEY(id);

ALTER TABLE custaddress ADD CONSTRAINT PK_custaddress PRIMARY KEY(customer_id);

ALTER TABLE wishlist ADD CONSTRAINT PK_wishlist PRIMARY KEY(customer_id,item_id);

---------------------------------------------/*FOREIGN KEYS*/



ALTER TABLE memory ADD CONSTRAINT FK_memory_product FOREIGN KEY(item_id) REFERENCES product(id)

ALTER TABLE videocard ADD CONSTRAINT FK_videocard_product FOREIGN KEY(item_id) REFERENCES product(id)

ALTER TABLE headphones ADD CONSTRAINT FK_headphones_product FOREIGN KEY(item_id) REFERENCES product(id)

ALTER TABLE mouse ADD CONSTRAINT FK_mouse_product FOREIGN KEY(item_id) REFERENCES product(id)

ALTER TABLE corder ADD CONSTRAINT FK_corder_product FOREIGN KEY(item_id) REFERENCES product(id)

ALTER TABLE corder ADD CONSTRAINT FK_corder_customer FOREIGN KEY(customer_id) REFERENCES customer(id)

ALTER TABLE custaddress ADD CONSTRAINT FK_custaddress_customer FOREIGN KEY(customer_id) REFERENCES customer(id)

ALTER TABLE wishlist ADD CONSTRAINT FK_wishlist_customer FOREIGN KEY(customer_id) REFERENCES customer(id)

ALTER TABLE wishlist ADD CONSTRAINT FK_wishlist_product FOREIGN KEY(item_id) REFERENCES product(id)

---------------------------------------------/*CHECK*/


ALTER TABLE memory ADD CONSTRAINT CK_memory
CHECK(size > 0 and warranty > 0 and price > 0 and rgb_light in ('Y', 'N'))

ALTER TABLE videocard ADD CONSTRAINT CK_videocard
CHECK(size > 0 and warranty > 0 and price > 0);

ALTER TABLE mouse ADD CONSTRAINT CK_mouse
CHECK(warranty > 0 and price > 0);

ALTER TABLE headphones ADD CONSTRAINT CK_headphones
CHECK(warranty > 0 and price > 0 and microphone in ('Y','N'));

ALTER TABLE corder ADD CONSTRAINT CK_corder
CHECK(quantity > 0);

-------------------------------------/*PRODUCT*/

INSERT INTO product VALUES (1,'mouse','ZOWIE');
INSERT INTO product VALUES (2,'mouse','ZOWIE');
INSERT INTO product VALUES (3,'mouse','HYPERX');
INSERT INTO product VALUES (4,'mouse','LOGITECH');
INSERT INTO product VALUES (5,'mouse','LOGITECH');
INSERT INTO product VALUES (6,'mouse','LOGITECH');
INSERT INTO product VALUES (7,'mouse','LOGITECH');
INSERT INTO product VALUES (8,'mouse','Razer');
INSERT INTO product VALUES (9,'mouse','LOGITECH');
INSERT INTO product VALUES (10,'mouse','Roccat');

INSERT INTO product VALUES (11,'headphone','HYPERX');
INSERT INTO product VALUES (12,'headphone','MAXELL');
INSERT INTO product VALUES (13,'headphone','LOGITECH');
INSERT INTO product VALUES (14,'headphone','ASUS');
INSERT INTO product VALUES (15,'headphone','Sony');
INSERT INTO product VALUES (16,'headphone','Sony');
INSERT INTO product VALUES (17,'headphone','Sony');
INSERT INTO product VALUES (18,'headphone','BOSE');
INSERT INTO product VALUES (19,'headphone','AKG');
INSERT INTO product VALUES (20,'headphone','BOSE');

INSERT INTO product VALUES (21,'memory','ADATA');
INSERT INTO product VALUES (22,'memory','HYPERX');
INSERT INTO product VALUES (23,'memory','CORSAIR');
INSERT INTO product VALUES (24,'memory','CORSAIR');
INSERT INTO product VALUES (25, 'memory','ADATA');
INSERT INTO product VALUES (26,'memory','ADATA');
INSERT INTO product VALUES (27,'memory','G.Skill');
INSERT INTO product VALUES (28,'memory','PATRIOT');
INSERT INTO product VALUES (29,'memory','G.Skill');

INSERT INTO product VALUES (30,'videocard','ASUS');
INSERT INTO product VALUES (31,'videocard','ZOTAC');
INSERT INTO product VALUES (32,'videocard','EVGA');
INSERT INTO product VALUES (33,'videocard','NVIDIA');
INSERT INTO product VALUES (34,'videocard','NVIDIA');
INSERT INTO product VALUES (35,'videocard','NVIDIA');
INSERT INTO product VALUES (36,'videocard','AMD');
INSERT INTO product VALUES (37,'videocard','AMD');
INSERT INTO product VALUES (38,'videocard','NVIDIA');
INSERT INTO product VALUES (39,'videocard','NVIDIA');
INSERT INTO product VALUES (40,'videocard','AMD');

---------------------------------------------/*HEADPHONES*/

INSERT INTO headphones VALUES (11,'HYPERX STINGER','Y',12,250,4);
INSERT INTO headphones VALUES (12,'MAXELL HYPERSHOCK','N',9,200,4);
INSERT INTO headphones VALUES (13,'LOGITECH G332','Y',22,331,4);
INSERT INTO headphones VALUES (14,'ASUS DELTA','N',2,120,4);
INSERT INTO headphones VALUES (15, 'WF-1000XM4', 'Y', 3, 200,4);
INSERT INTO headphones VALUES (16, 'WH-1000XM4', 'N', 1, 150,4);
INSERT INTO headphones VALUES (18, '700', 'N', 3, 100,4);
INSERT INTO headphones VALUES (19, 'N60NC', 'Y', 10, 1000,4);
INSERT INTO headphones VALUES (20, 'QuietComfort', 'N', 5, 200,4);

----------------------------------------------/*MOUSE*/

INSERT INTO mouse VALUES (1,'ZOWIE S1','OPTIC',1200,2,200,5);
INSERT INTO mouse VALUES (2,'ZOWIE S2','LASER',1300,3,250,5);
INSERT INTO mouse VALUES (3,'HYPERX PULSEFIRE','OPTIC',1800,4,333,5);
INSERT INTO mouse VALUES (4,'LOGITECH SPARTAN','LASER',2100,8, 320,5);
INSERT INTO mouse VALUES (5, 'G502 HERO', 'PMW', 3360, 3, 200,5);
INSERT INTO mouse VALUES (6, 'G PRO', 'PMW', 3370, 5, 20,5);
INSERT INTO mouse VALUES (7, 'G PRO X', 'PMW', 3370, 5, 100,5);
INSERT INTO mouse VALUES (8, 'Basilisk 3', 'ADNS', 3095, 7, 300,5);
INSERT INTO mouse VALUES (9, 'G505 HERO', 'PMW', 3360, 1, 60,5);
INSERT INTO mouse VALUES (10, 'Kone', 'ADNS', 3090, 2, 300,5);

-------------------------------------/*MEMORY*/

INSERT INTO memory VALUES (21,'ADATA LANCER2','Y',4,10,100,6);
INSERT INTO memory VALUES (22,'HYPERX FURY','N', 8, 2, 200,6);
INSERT INTO memory VALUES (23,'CORSAIR VENGEANCE','N', 12, 3, 300,6);
INSERT INTO memory VALUES (24,'CORSAIR MASTER','Y', 8, 10, 200,6);
INSERT INTO memory VALUES (25, 'Spectrix D80', 'N', 8, 2, 120,6);
INSERT INTO memory VALUES (26, 'Spectrix D90', 'Y', 16, 5, 360,6);
INSERT INTO memory VALUES (27, 'Trident Z RGB', 'Y', 16, 3, 240,6);
INSERT INTO memory VALUES (28, 'Signature', 'N', 32, 3, 480,6);
INSERT INTO memory VALUES (29, 'Trident X RGB', 'Y', 64, 5, 1000,6);

----------------------------/*VIDEOCARD*/

INSERT INTO videocard  VALUES (30,'ASUS 1060TI',6,12,1000,7);
INSERT INTO videocard VALUES (31,'ZOTAC 1070',8,12,1300,7);
INSERT INTO videocard VALUES (32,'EVGA 1080TI',12,12,1400,7);
INSERT INTO videocard VALUES (33,'NVIDIA 3080',16,12,2000,7);

INSERT INTO videocard VALUES (34, 'Geforce RTX 3080','9', 7, 799,7);
INSERT INTO videocard VALUES (35, 'Geforce RTX 3090','9', 2, 499,7);
INSERT INTO videocard VALUES (36, 'AMD RX 6800 XT','5', 5, 699,7);
INSERT INTO videocard VALUES (37, 'AMD RX 6900 XT','4', 10, 799,7);
INSERT INTO videocard VALUES (38, 'Geforce RTX 3060', '9', 5, 1099,7);
INSERT INTO videocard VALUES (39, 'GeForce RTX 3070', '1', 3, 699,7);
INSERT INTO videocard VALUES (40, 'AMD RX 6700 XT', '2', 3, 599,7);

------customer---

INSERT INTO  customer VALUES (1,'TEODOR','KUKOV','1234676788234555');
INSERT INTO  customer VALUES (2,'IVAN','IVANOV','1299776225487699');
INSERT INTO  customer VALUES (3,'BORIS','BOND','1334227666332211');
INSERT INTO  customer VALUES (4,'DIMITUR','MARTINOV','4566799102649026');
INSERT INTO  customer VALUES (5,'IVAN','MARTINOV','7625390277712456');
INSERT INTO  customer VALUES (6,'BORIS','BALABANOV','4444444466666666');
INSERT INTO  customer VALUES (7,'NENCHO','TOSHEV','9283746565748392');
INSERT INTO  customer VALUES (8,'PETUR','DIMITROV','1234567888909877');
INSERT INTO  customer VALUES (9,'SLAVI','BOND','8977364399124637');
INSERT INTO  customer VALUES (10,'STILYAN','KUKROKOV','0000011122233345');
INSERT INTO  customer VALUES (11, 'GENCHO','GENEV','1217889234333329');
INSERT INTO  customer VALUES (12,'BORISLAV','BORISOV',NULL);

-------------------------/*CORDER*/

INSERT INTO corder VALUES (13,1,1,'SUCCESSFUL',3);
INSERT INTO corder VALUES (16,1,1,'SUCCESSFUL',10);
INSERT INTO corder VALUES (15,1,1,'SUCCESSFUL',2);
INSERT INTO corder VALUES (14,1,1,'SUCCESSFUL',1);
INSERT INTO corder VALUES (12,1,1,'SUCCESSFUL',3);
INSERT INTO corder VALUES (33,2,10,'UNSUCCESSFUL',3);
INSERT INTO corder VALUES (32,2,10,'SUCCESSFUL',1);
INSERT INTO corder VALUES (13,3,3,'PROCESSING',1);
INSERT INTO corder VALUES (12,3,3,'UNSUCCESSFUL',40);
INSERT INTO corder VALUES (10,3,3,'PROCESSING',1);
INSERT INTO corder VALUES (4,3,3,'PROCESSING',2);
INSERT INTO corder VALUES (3,4,8,'SUCCESSFUL',3);
INSERT INTO corder VALUES (28,4,8,'SUCCESSFUL',9);
INSERT INTO corder VALUES (25,4,8,'SUCCESSFUL',1);
INSERT INTO corder VALUES (1,4,8,'SUCCESSFUL',1);
INSERT INTO corder VALUES (2,4,8,'SUCCESSFUL',3);
INSERT INTO corder VALUES (3,14,8,'SUCCESSFUL',4);
INSERT INTO corder VALUES (33,5,10,'SUCCESSFUL',11);
INSERT INTO corder VALUES (31,5,10,'UNSUCCESSFUL',12);
INSERT INTO corder VALUES (40,6,7,'UNSUCCESSFUL',1);
INSERT INTO corder VALUES (20,7,7,'SUCCESSFUL',3);
INSERT INTO corder VALUES (19,8,2,'SUCCESSFUL',2);
INSERT INTO corder VALUES (13,8,2,'SUCCESSFUL',1);
INSERT INTO corder VALUES (18,8,2,'SUCCESSFUL',2);
INSERT INTO corder VALUES (27,8,2,'SUCCESSFUL',4);
INSERT INTO corder VALUES (31,8,2,'SUCCESSFUL',3);
INSERT INTO corder VALUES (4,8,2,'SUCCESSFUL',5);
INSERT INTO corder VALUES (9,8,2,'PROCESSING',1);
INSERT INTO corder VALUES (38,8,2,'SUCCESSFUL',1);
INSERT INTO corder VALUES (39,8,2,'SUCCESSFUL',1);
INSERT INTO corder VALUES (40,8,2,'SUCCESSFUL',2);
INSERT INTO corder VALUES (13,9,6,'SUCCESSFUL',3);
INSERT INTO corder VALUES (12,9,6,'SUCCESSFUL',5);
INSERT INTO corder VALUES (17,9,6,'SUCCESSFUL',2);
INSERT INTO corder VALUES (6,10,8,'UNSUCCESSFUL',2);
INSERT INTO corder VALUES (16,10,8,'UNSUCCESSFUL',1);
INSERT INTO corder VALUES (26,10,8,'UNSUCCESSFUL',2);
INSERT INTO corder VALUES (36,11,8,'SUCCESSFUL',3);
INSERT INTO corder VALUES (40,11,8,'PROCESSING',1);
INSERT INTO corder VALUES (30,12,4,'SUCCESSFUL',1);
INSERT INTO corder VALUES (20,13,4,'SUCCESSFUL',1);
INSERT INTO corder VALUES (10,14,1,'UNSUCCESSFUL',82);
INSERT INTO corder VALUES (1,15,4,'UNSUCCESSFUL',1);
INSERT INTO corder VALUES (11,16,3,'SUCCESSFUL',3);
INSERT INTO corder VALUES (21,16,3,'SUCCESSFUL',3);
INSERT INTO corder VALUES (31,16,3,'SUCCESSFUL',1);
INSERT INTO corder VALUES (40,16,3,'SUCCESSFUL',2);

-------------------------/*CUSTOMER ADDRESS*/ 
INSERT INTO custaddress VALUES(1,'SOFIA','TOMA IKONOPISEC',1);
INSERT INTO custaddress VALUES(2,'BURGAS','IOSIF',11);
INSERT INTO custaddress VALUES(3,'VARNA','SIMEONOVSKA',22);
INSERT INTO custaddress VALUES(4,'SOFIA','BELI GULUB',9);
INSERT INTO custaddress VALUES(5,'BURGAS','KRIVA',16);
INSERT INTO custaddress VALUES(6,'PLOVDIV','DIMITROVSKA',48);
INSERT INTO custaddress VALUES(7,'SOFIA','LEKI ISKUR',39);
INSERT INTO custaddress VALUES(8,'RUSE','SVETI PETUR',4);

-------------------------/*WISHLIST*/ 

INSERT INTO wishlist VALUES (1,3);
INSERT INTO wishlist VALUES (2,10);
INSERT INTO wishlist VALUES (3,8);
INSERT INTO wishlist VALUES (1,40);
INSERT INTO wishlist VALUES (1,39);
INSERT INTO wishlist VALUES (10,7);
INSERT INTO wishlist VALUES (9,31);
INSERT INTO wishlist VALUES (9,20);
INSERT INTO wishlist VALUES (9,1);
INSERT INTO wishlist VALUES (9,2);
INSERT INTO wishlist VALUES (9,3);
INSERT INTO wishlist VALUES (7,7);
INSERT INTO wishlist VALUES (7,33);
INSERT INTO wishlist VALUES (6,5);
INSERT INTO wishlist VALUES (6,6);
INSERT INTO wishlist VALUES (6,7);
INSERT INTO wishlist VALUES (6,8);
INSERT INTO wishlist VALUES (6,9);
INSERT INTO wishlist VALUES (6,10);
INSERT INTO wishlist VALUES (6,17);
INSERT INTO wishlist VALUES (6,18);
INSERT INTO wishlist VALUES (6,40);
INSERT INTO wishlist VALUES (6,39);
INSERT INTO wishlist VALUES (6,37);
INSERT INTO wishlist VALUES (4,31);
INSERT INTO wishlist VALUES (4,20);
INSERT INTO wishlist VALUES (4,2);
INSERT INTO wishlist VALUES (8,2);
INSERT INTO wishlist VALUES (8,13);
INSERT INTO wishlist VALUES (8,17);
INSERT INTO wishlist VALUES (8,33);
INSERT INTO wishlist VALUES (8,25);












