SELECT p1.name AS person_name1,
       p2.name AS person_name2,
       p1.address AS common_address
FROM person p1
JOIN person p2 ON p1.address = p2.address AND p1.id > p2.id
ORDER BY p1.name, p2.name, p1.address