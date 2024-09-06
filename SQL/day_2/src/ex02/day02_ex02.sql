SELECT COALESCE(person.name,'-') as person_name,
       person_visits.visit_date,
       COALESCE(pizzeria.name, '-') AS pizzeria_name
FROM person
LEFT JOIN person_visits ON person.id = person_visits.person_id
                          AND person_visits.visit_date BETWEEN '2022-01-01' AND '2022-01-03'
FULL JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
ORDER BY COALESCE(person.name, '-'),
         person_visits.visit_date,
         COALESCE(pizzeria.name, '-')