SELECT DISTINCT pizzeria.name AS pizzeria_name
FROM pizzeria
JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id
JOIN person ON person.id = person_visits.person_id
AND person.name = 'Andrey'
JOIN person_order ON person_visits.person_id = person_order.person_id
LEFT JOIN menu ON menu.id = person_order.menu_id
AND menu.pizzeria_id = pizzeria.id
WHERE menu.id IS NULL
ORDER BY pizzeria_name