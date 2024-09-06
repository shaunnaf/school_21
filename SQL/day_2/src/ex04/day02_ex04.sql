SELECT menu.pizza_name AS pizza_name,
       pizzeria.name AS pizzeria_name,
       menu.price
FROM pizzeria
JOIN menu ON menu.pizzeria_id = pizzeria.id
                 AND (menu.pizza_name LIKE 'mushroom%'
                          OR menu.pizza_name LIKE 'pepperoni%')
ORDER BY menu.pizza_name, pizzeria.name