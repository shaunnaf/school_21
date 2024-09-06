SELECT menu.pizza_name,
       menu.price,
       pizzeria.name
FROM menu
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
LEFT JOIN person_order ON person_order.menu_id = menu.id
WHERE person_order.id IS NULL
ORDER BY pizza_name,price