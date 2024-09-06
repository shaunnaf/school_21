(SELECT name,count(*) AS count,'visit' AS action_type
FROM person_visits
JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
GROUP BY name
order by name
limit 3)
union
(SELECT name ,count(*) AS count,'order' AS action_type
FROM person_order
JOIN menu ON person_order.menu_id = menu.id
JOIN pizzeria on menu.pizzeria_id = pizzeria.id
GROUP BY name
order by name
limit 3)
order by action_type, count desc