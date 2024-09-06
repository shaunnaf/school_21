SELECT
    p.name,
    m.pizza_name,
    m.price,
    ROUND(m.price - (m.price * (d.discount / 100)), 2) AS discount_price,
    pz.name
FROM person_order po
JOIN menu m ON po.menu_id = m.id
JOIN person p ON po.person_id = p.id
JOIN pizzeria pz ON m.pizzeria_id = pz.id
JOIN person_discounts d ON po.person_id = d.person_id AND m.pizzeria_id = d.pizzeria_id
ORDER BY p.name, m.pizza_name;
