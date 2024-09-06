SELECT visit_date AS action_date,person_id
FROM person_visits
INTERSECT
SELECT order_date AS action_date,person_id
FROM person_order
ORDER BY action_date,person_id DESC