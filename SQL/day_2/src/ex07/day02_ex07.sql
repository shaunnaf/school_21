SELECT pizzeria.name
FROM pizzeria
JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
AND person_visits.visit_date = '2022-01-08'
JOIN person ON person_visits.person_id = person.id
AND person.name = 'Dmitriy'
JOIN menu ON pizzeria.id = menu.pizzeria_id
AND price < 800