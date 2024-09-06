INSERT INTO person_discounts
SELECT ROW_NUMBER() over (ORDER BY person_id,pizzeria_id) id, person_order.person_id AS person_id,
       menu.pizzeria_id AS pizzeria_id,
    CASE
        WHEN COUNT(*) = 1 THEN 10.5
        WHEN COUNT(*) = 2 THEN 22
    ELSE 30
    END AS discount
FROM person_order
LEFT JOIN MENU
ON person_order.menu_id = menu.id
GROUP BY person_id, pizzeria_id
