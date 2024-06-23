---Views----
Create View cheapMice
as SELECT *
FROM mouse m
where m.price < 100;

GO

Create View cheapHeadphones
as SELECT *
FROM headphones
where price < 200;

GO

Create View cheapMemories
as SELECT *
FROM mouse m
where m.price < 300;

GO

Create View cheapVideoCards
as SELECT *
FROM mouse m
where m.price < 200;

GO

Create View CustomersBigWishList
as
SELECT w.customer_id, COUNT(w.item_id) as "num_products"
FROM wishlist w
GROUP BY (w.customer_id)
HAVING COUNT(w.item_id) > 10

GO

Create View RazerProducts
as
SELECT *
FROM product
where prod_brand = '%Razer%'
GO
-------Indexes----------
CREATE INDEX idx_memory_price
ON memory(price)
CREATE INDEX idx_memory_item_id
ON memory(item_id)
CREATE INDEX idx_videocard_price
ON videocard(price)
CREATE INDEX idx_mouse_price
ON mouse(price)
CREATE INDEX idx_headphones_price
ON headphones(price)
CREATE INDEX idx_customer_id
ON corder(customer_id)
CREATE INDEX idx_customer_id
ON customer(cust_name, cust_surname)
CREATE UNIQUE INDEX idx_wishlist
ON wishlist(customer_id, item_id)
--------triggers
GO
CREATE TRIGGER Remove_Item_Wishlist_On_Insert ON corder
	AFTER INSERT
AS
BEGIN
	SET NOCOUNT ON
	DECLARE @Customer_id int 
	DECLARE @Item_id int
	SELECT @Customer_id = INSERTED.customer_id
	from INSERTED
	SELECT @Item_id = INSERTED.item_id
	from INSERTED


	DELETE FROM wishlist
	where customer_id = @Customer_id
	and item_id = @Item_id;

END

GO

CREATE TRIGGER delete_ifmore_all on corder
AFTER INSERT
AS
begin
SET NOCOUNT ON

DECLARE @Quan int
SELECT @Quan = INSERTED.quantity from INSERTED
DECLARE @ID int
SELECT @ID = inserted.item_id from inserted
DECLARE @Type varchar(15)
SELECT @Type = (select prod_type from product where id = @ID)
if exists(select m1.item_id from (select item_id,quantity from headphones
									union
									select item_id,quantity from mouse
									union
									select item_id,quantity from videocard
									union
									select item_id,quantity from memory) m1 where item_id = @ID and m1.quantity < @Quan) 
	begin
	rollback transaction
	end
else
	if exists(select 1 from headphones where item_id = @ID)
		begin
		UPDATE headphones
		SET quantity = quantity - @Quan from headphones where item_id = @ID
		end
	else if exists (select 1 from mouse where item_id = @ID)
		begin
		UPDATE mouse
		SET quantity = quantity - @Quan from mouse where item_id = @ID
		end
	else if exists(select 1 from videocard where item_id = @ID)
		begin
		UPDATE videocard
		SET quantity = quantity - @Quan from videocard where item_id = @ID
		end
	else if exists(select 1 from memory where item_id = @ID)
		begin
		UPDATE memory
		SET quantity = quantity - @Quan from memory where item_id = @ID
		end
end



