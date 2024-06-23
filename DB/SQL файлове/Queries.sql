----Прости под заявки и заявки на 2 или повече релации----
-- Напишете заявка, която извежда всички 
--компютърни мишки с цена под 100$,
--както и цената им.
select mouse_name, price
from mouse
where price < 100

-- Напишете заявка, която извежда всички 
--слушалки с микрофон,
--както и гаранцията им.
select hp_name,warranty
from headphones
where microphone = 'Y'

-- Напишете заявка, която извежда всички 
--имена на картите с памет,
--които са цветни.
select m.mem_name
from memory m
where rgb_light like 'Y'

-- Напишете заявка, която извежда всички 
--номера(id) на видеокарти,
--чиито гаранции са над 5 години.
select vc.item_id,vc.vc_name
from videocard vc
where warranty > 5

-- Напишете заявка, която извежда  
--номера на дебтната карта,
--на клиент,чието име е Slavi Bond.
select customer_cardn as Slavi_Bond
from customer
where cust_name = 'SLAVI'
and cust_surname = 'BOND'

-- Напишете заявка, която извежда всички 
--имена на продукти,
--които са с цена под 1000$ и с гаранция-над 3 години.
select hp.hp_name as product_name
from headphones hp
where warranty > 3
and price < 1000
union
select m.mouse_name
from mouse m
where warranty > 3
and price < 1000
union
select mem.mem_name
from memory mem
where warranty > 3
and price < 1000
union
select vc.vc_name
from videocard vc
where warranty > 3
and price < 1000
--Напишете заявка, 
--която извежда всички двойки
--имена на карти с памет,
--които имат еднакви размери и гаранции.
select mem1.mem_name, mem2.mem_name
from memory mem1,
memory mem2
where mem1.size = mem2.size
and mem1.warranty = mem2.warranty
and mem1.mem_name < mem2.mem_name
order by 1, 2
--Напишете заявка, която
--извежда имената на клиентите,
--чийто адрес се състои от точно
--2 думи.
select c.cust_name as name,
c.cust_surname
from customer c,
custaddress ca
where ca.customer_id = c.id
and ca.street_name like '% %'
and ca.street_name not like '% % %'

/*Напишете заявка,която изкарва производителите , които произвеждат както мишки , така и слушалки*/
select prod_brand
from product
where prod_type = 'mouse'
intersect
select prod_brand
from product
where prod_type = 'headphone'

/*Напишете заявка, която изкарва името и цената на всички слушалки, които струват повече от слушалки с име 'ASUS DELTA'(използвайте псевдоними name  и price за име и цена)*/
select h1.hp_name as 'name',h1.price as price
from headphones h1,headphones h2
where h2.hp_name = 'ASUS DELTA'
and h1.price > h2.price


/*Подзаявки*/
------1------
/*Напишете заявка , която изкарва имената на всички слушалки, за които все още не е платено*/
select  hp1.hp_name
from headphones hp1
where hp1.item_id in (select c1.item_id from corder c1 where payment_status ='UNSUCCESSFUL')

----2-----
/*Напишете заявка,която извежда име и цена на всички слушалки , които струват повече от 'LOGITECH G332'*/
select h1.hp_name,h1.price
from headphones h1
where h1.price > (select h2.price from headphones h2 where h2.hp_name='LOGITECH G332')

---3-----
/*Напишете заявка,която извежда името и марката на продуктът(слушалки,мишки,видеокарти и memory) с най-висока цена,като използвате псевдонимите съответно name за име и brand за марка  */

select hw.name,p.prod_brand as brand
from product p,(select hp_name as 'name',item_id,price from headphones
				union
				select mouse_name ,item_id,price from mouse
				union
				select mem_name,item_id,price from memory
				union
				select vc_name,item_id,price from videocard) hw
where hw.item_id = p.id
and hw.price >= ALL(select price from headphones
					union
					select price from mouse
					union
					select price from videocard
					union
					select price from memory)

-----4-----
/*Напишете заявка, която изкарва името името ,цената и марката на видеокартите ,чиито гаранционен период е по-голям от гаранционния период на  тези видеокарти със същата големина(size)*/


select v1.vc_name as 'name' , v1.price,p1.prod_brand
from videocard v1 ,product p1
where v1.item_id = p1.id
and v1.warranty >= ALL(select v2.warranty from videocard v2 where v2.size = v1.size)


---5---
/*Напишете заявка,която изкарва името,марката и цената на най-скъпата мишка,за която успешно е платено*/
select m1.mouse_name as name ,p1.prod_brand as brand, m1.price
from mouse m1,product p1
where m1.item_id = p1.id
and m1.item_id in(select m2.item_id from mouse m2 where m2.item_id in (select c1.item_id from corder c1 where c1.payment_status = 'SUCCESSFUL'))
and m1.price >= ALL(select m2.price from mouse m2 where m2.item_id in (select c1.item_id from corder c1 where c1.payment_status = 'SUCCESSFUL'))
/*Съедининея*/
------1-----
/*Напишете заявка , която извежда първото име и фамилията на тези клиенти , които имат продукт в wishlist-а и успешно са заплатили за него*/
select distinct cu1.cust_name as 'name',cu1.cust_surname as surname
from corder c1 JOIN customer cu1
ON c1.customer_id = cu1.id
where c1.payment_status = 'SUCCESSFUL'
and c1.item_id in (select w1.item_id from wishlist w1 where w1.customer_id = cu1.id)

----2------
/*Напишете заявка ,която извежда името , марката и цената на продуктите , които са били поръчвани поне  веднъж(които са в corder )*/
select hw.name ,p1.prod_brand,hw.price
from product p1  JOIN (select mouse_name as 'name',price,item_id from mouse
					union
					select hp_name as 'name',price,item_id  from headphones
					union 
					select  vc_name as 'name',price,item_id from videocard
					union
					select mem_name as 'name',price,item_id  from memory) hw
ON p1.id = hw.item_id
where p1.id  in (select item_id from corder)


-----3----
/*Напишете заявка, която извежда името и цената на всеки продукт, който никога не е бил поръчван*/
select hw.name,hw.price
from product p1 JOIN (select mouse_name as 'name',item_id,price from mouse
						union
						select hp_name as 'name',item_id,price from headphones
						union
						select  vc_name as 'name',item_id,price from videocard
						union
						select mem_name as 'name',item_id,price from memory) hw
ON p1.id = hw.item_id
LEFT JOIN corder c1 ON p1.id = c1.item_id
where c1.item_id is null


-----4----
/*Напишете заявка която извежда име,микроофон,цена и производител  всички слушалки, направени от производителя на мишката 'HYPERX PULSEFIRE'*/
select hp.hp_name as 'name',hp.price,p2.prod_brand as brand
from headphones hp JOIN product p2 
ON hp.item_id = p2.id
where p2.prod_brand  =	(select p1.prod_brand
						from mouse m1 JOIN product p1
						ON m1.item_id = p1.id
						where m1.mouse_name = 'HYPERX PULSEFIRE')


------5-----
/*Напишете заявка,която извежда името,фамилията и адресът на всички клиенти, които още не са заплатили*/

select c1.cust_name as 'name',c1.cust_surname as surname,ca.city_name+' '+ca.street_name+' '+ca.ap_building as 'address'
from customer c1 JOIN custaddress ca
ON c1.id = ca.customer_id
where c1.id in (select customer_id from corder where payment_status = 'UNSUCCESSFUL')



--1. Напишете заявка, която извежда за всяка марка мишка извежда 
--най-ниската и най-високата цена за съответната марка.

SELECT p.prod_brand, MIN(m.price) as "min_price", MAX(m.price) as "max_price"
FROM PRODUCT p
JOIN MOUSE m
ON m.item_id = p.id
GROUP BY prod_brand


--2. Напишете заявка, която извежда броя на брандовете слушалки с цена поне 200лв.

SELECT COUNT(p.id) as "brands_num"
FROM headphones h
JOIN product p
ON p.id = h.item_id
WHERE h.price >= 200



--3. Напишете заявка, която извежда броя на паметите с размер над 4GB, за тези марки,
--които имат поне 2 памети в базата данни

SELECT p.prod_brand, COUNT(p.id) as "num_mems"
FROM memory m
JOIN product p
ON P.id = m.item_id
WHERE m.size > 4
GROUP BY p.prod_brand
HAVING COUNT(p.id) >= 2



--4 Да се напише заявка, която да извежда, дали най-често срещаният
--резултат на транзакция и броя на срещанията му

SELECT res.num_meetings, res.payment_status
FROM (SELECT co1.payment_status, COUNT(co1.order_id) as "num_meetings"
	FROM corder co1
	GROUP BY co1.payment_status) res
	WHERE res.num_meetings >= ALL(SELECT COUNT(co2.order_id) as "num_meetings"
									FROM corder co2
									GROUP BY co2.payment_status)




--5. Напишете заявка, която извежда средната цена на видео картите според различната им гаранция

SELECT v.warranty, AVG(v.price) as "avg_price"
FROM videocard v
GROUP BY v.warranty 


--6. Да се напише заявка, която извежда броя на любими продукти за всеки клиент

SELECT customer_id, COUNT(w.item_id) as "num_fav_prod"
FROM wishlist w
GROUP BY w.customer_id

--7. Напишете заявка, която извежда марките, които са произвели поне 2
--различни памети и в името си съдържат "data".


SELECT p.prod_brand, COUNT(m.mem_name) as "mem_cnt"
FROM memory m
JOIN product p
ON p.id = m.item_id
WHERE UPPER(p.prod_brand) LIKE UPPER('%data%')
GROUP BY p.prod_brand
HAVING COUNT(m.mem_name) >= 2


--8. Да се напише заявка, която да извежда средния размер на паметите 
--на брандове, които произвеждат и видеокарти.

SELECT p.prod_brand, AVG(m.size) as "avg_size"
FROM product p
JOIN memory m
ON p.id = m.item_id
WHERE p.prod_brand in (SELECT p2.prod_brand
						FROM product p2
						JOIN videocard v
						ON v.item_id = p2.id)
GROUP BY p.prod_brand


--9. Да се напише заявка, която извежда сумата от цените на всички продукти

SELECT SUM(t.sum) as "whole sum"
FROM(SELECT SUM(price) as "sum"
	FROM MOUSE
	UNION
	SELECT SUM(price) as "sum"
	FROM HEADPHONES
	UNION
	SELECT SUM(price) as "sum"
	FROM MEMORY
	UNION
	SELECT SUM(price) as "sum"
	FROM VIDEOCARD) t

--10. Да се напише заявка, която извежда колко продукта е закупил УСПЕШНО
--клиент общо от всичките си покупки



SELECT customer_id, COUNT(co.order_id) as "num_products"
FROM corder co
WHERE co.payment_status like 'SUCCESSFUL'
GROUP BY customer_id

