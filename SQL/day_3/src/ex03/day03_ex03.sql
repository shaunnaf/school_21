WITH visit_by_gender AS (SELECT person_visits.pizzeria_id,
                             person.gender,
                             count(*) AS visit_count
                      FROM person
                          JOIN person_visits ON person_visits.person_id = person.id
                      GROUP BY person_visits.pizzeria_id, person.gender
                      ),
    pizzeria_more_visits AS (SELECT vg1.pizzeria_id
                             FROM visit_by_gender AS vg1
                            LEFT JOIN visit_by_gender AS vg2
                                ON vg1.pizzeria_id = vg2.pizzeria_id
                                       AND vg1.gender != vg2.gender
                                WHERE vg1.visit_count > COALESCE(vg2.visit_count,0)
                                )
SELECT DISTINCT pizzeria.name AS pizzeria_name
FROM pizzeria_more_visits
JOIN pizzeria ON pizzeria_more_visits.pizzeria_id = pizzeria.id
ORDER BY pizzeria_name

