SELECT id AS object_id, pizza_name AS object_name
FROM menu
UNION
SELECT id AS object_id, name AS object_name
FROM person
order by object_id,object_name