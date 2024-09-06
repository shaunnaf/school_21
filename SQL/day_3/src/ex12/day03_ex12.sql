INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT
    gs.new_id,
    p.id AS person_id,
    gp.menu_id,
    '2022-02-25' AS order_date
FROM (
    SELECT
        generate_series(
            (SELECT MAX(id) + 1 FROM person_order),
            (SELECT MAX(id) + (SELECT COUNT(*) FROM person) FROM person_order)
        ) AS new_id
) AS gs
JOIN person p ON gs.new_id - (SELECT MAX(id) FROM person_order) = p.id
CROSS JOIN (SELECT id AS menu_id FROM menu WHERE pizza_name = 'greek pizza') AS gp
ORDER BY
    gs.new_id;
