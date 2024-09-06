SELECT pizzeria.name AS pizzeria_name
FROM pizzeria
JOIN menu ON pizzeria.id = menu.pizzeria_id
JOIN person_order ON menu.id = person_order.menu_id
JOIN person ON person_order.person_id = person.id
WHERE person.gender = 'female'
GROUP BY pizzeria.name
HAVING COUNT(DISTINCT person.id) = (
    SELECT COUNT(DISTINCT p.id)
    FROM pizzeria pz
    JOIN menu m ON pz.id = m.pizzeria_id
    JOIN person_order po ON m.id = po.menu_id
    JOIN person p ON po.person_id = p.id
    WHERE pizzeria.name = pz.name
    )

UNION

SELECT pizzeria.name AS pizzeria_name
FROM pizzeria
JOIN menu ON pizzeria.id = menu.pizzeria_id
JOIN person_order ON menu.id = person_order.menu_id
JOIN person ON person_order.person_id = person.id
WHERE person.gender = 'male'
GROUP BY pizzeria.name
HAVING COUNT(DISTINCT person.id) = (
    SELECT COUNT(DISTINCT p.id)
    FROM pizzeria pz
    JOIN menu m ON pz.id = m.pizzeria_id
    JOIN person_order po ON m.id = po.menu_id
    JOIN person p ON po.person_id = p.id
    WHERE pizzeria.name = pz.name
    )
ORDER BY pizzeria_name