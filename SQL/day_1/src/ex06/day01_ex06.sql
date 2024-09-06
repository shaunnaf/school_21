SELECT visit_date AS action_date, person.name
FROM person_visits,person
WHERE person.id = person_visits.person_id
INTERSECT
SELECT order_date AS action_date,person.name
FROM person_order,person
WHERE person.id = person_order.person_id
ORDER BY action_date,name DESC