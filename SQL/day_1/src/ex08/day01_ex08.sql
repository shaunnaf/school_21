SELECT order_date, CONCAT(name,'(age:',age,')') as person_information
FROM person_order
NATURAL JOIN(SELECT id as person_id,name,age FROM person) as tmp
ORDER BY order_date, person_information
