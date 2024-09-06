SELECT dates.missing_date FROM (
    SELECT generate_series (date '2022-01-01', '2022-01-10', '1 day')::date AS missing_date
    ) AS dates
LEFT JOIN person_visits ON dates.missing_date = person_visits.visit_date
                               AND (person_visits.person_id = '1'
                                        OR person_visits.person_id = '2')
WHERE person_visits.visit_date IS NULL
ORDER BY dates.missing_date