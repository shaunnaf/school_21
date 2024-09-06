SELECT menu.pizza_name,
       pizzeria.name AS pizzeria_name
FROM menu
JOIN person_order ON menu.id = person_order.menu_id
JOIN person ON person.id = person_order.person_id
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
WHERE person.name = 'Denis' OR person.name = 'Anna'
ORDER BY menu.pizza_name,
         pizzeria_name