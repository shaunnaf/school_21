SELECT menu.id
FROM menu
LEFT JOIN person_order ON menu.id = person_order.menu_id
WHERE person_order.id IS NULL
ORDER BY menu.id