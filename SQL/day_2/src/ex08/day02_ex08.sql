SELECT DISTINCT person.name
FROM person
JOIN person_order ON person.id = person_order.person_id
JOIN menu ON person_order.menu_id = menu.id
AND menu.pizza_name LIKE 'pepperoni%'
                 OR menu.pizza_name LIKE 'mushroom%'
WHERE person.gender = 'male'
  AND (person.address = 'Moscow' OR person.address = 'Samara')
ORDER BY person.name DESC