SELECT person.name as person_name,menu.pizza_name,pizzeria.name as pizzeria_name
FROM person_order
JOIN person ON person.id = person_order.person_id
JOIN menu ON menu.id = person_order.menu_id
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
ORDER BY person_name,pizza_name,pizzeria_name;