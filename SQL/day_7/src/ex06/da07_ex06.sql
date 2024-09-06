SELECT name,
       count(*) as count_of_orders,
       round(avg(price),2) as average_price,
       MAX(price) as max_price,
       min(price) as min_price
FROM pizzeria
JOIN menu ON pizzeria.id = menu.pizzeria_id
GROUP BY name
ORDER BY name