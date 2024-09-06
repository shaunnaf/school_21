EXPLAIN ANALYSE
SELECT menu.pizza_name,pizzeria.name as pizzeria_name
FROM menu
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id;

SET enable_seqscan = off;

ANALYZE menu;
ANALYZE pizzeria;
