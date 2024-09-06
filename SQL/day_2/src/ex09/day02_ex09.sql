SELECT distinct person.name
FROM person
JOIN person_order ON person_order.person_id = person.id
JOIN menu ON menu.id = person_order.menu_id
AND (menu.pizza_name LIKE 'cheese%')
WHERE person.gender = 'female'
intersect
SELECT distinct person.name
FROM person
JOIN person_order ON person_order.person_id = person.id
JOIN menu ON menu.id = person_order.menu_id
AND (menu.pizza_name LIKE 'pepperoni%')
WHERE person.gender = 'female'
ORDER BY name
