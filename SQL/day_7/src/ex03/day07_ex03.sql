SELECT name, SUM(count) AS total_count
FROM (
    (SELECT name, count(*) AS count
       FROM person_visits
        JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
       GROUP BY name)
union ALL
       (SELECT name, count(*) AS count
       FROM person_order
           JOIN menu
       ON person_order.menu_id = menu.id
           JOIN pizzeria on menu.pizzeria_id = pizzeria.id
       GROUP BY name
        )
) AS combined_results
GROUP BY name
ORDER BY total_count desc,name