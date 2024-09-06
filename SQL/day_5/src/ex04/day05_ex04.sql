CREATE UNIQUE INDEX idx_menu_unique
ON menu (pizzeria_id,pizza_name);

SET enable_seqscan = off;

EXPLAIN ANALYSE
SELECT menu.id
FROM menu