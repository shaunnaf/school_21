CREATE VIEW v_symmetric_union AS
    SELECT person_visits.person_id
FROM person_visits
WHERE person_visits.visit_date <= '2022-01-02'

except

SELECT person_visits.person_id
FROM person_visits
WHERE person_visits.visit_date <= '2022-01-06'

union

SELECT person_visits.person_id
FROM person_visits
WHERE person_visits.visit_date <= '2022-01-06'

except

SELECT person_visits.person_id
FROM person_visits
WHERE person_visits.visit_date <= '2022-01-02'
ORDER BY person_id
