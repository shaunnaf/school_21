SELECT * FROM
    (SELECT name AS object_name FROM person ORDER BY name) FIRST
UNION ALL
SELECT * FROM
    (SELECT pizza_name AS object_name FROM menu ORDER BY pizza_name) SECOND