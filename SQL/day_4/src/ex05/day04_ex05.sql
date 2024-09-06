CREATE VIEW v_price_with_discount AS
    SELECT person.name AS name,
           menu.pizza_name,
           menu.price,
           CAST(menu.price-menu.price*0.1 AS INT) AS discount_name
FROM person
JOIN person_order ON person.id = person_order.person_id
JOIN menu ON menu.id = person_order.menu_id
ORDER BY name, pizza_name