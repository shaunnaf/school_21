SELECT pizzeria.name,pizzeria.rating
FROM pizzeria
LEFT JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id
GROUP BY pizzeria.name,pizzeria.rating
HAVING count(person_visits.pizzeria_id) = 0


