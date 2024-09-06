CREATE INDEX idx_person_name
ON person (UPPER(name));

SET enable_seqscan = off;

EXPLAIN ANALYSE
SELECT name, age
FROM person
WHERE UPPER(name) = 'ANNA'