SELECT order_date,
       CONCAT(name,'(age:',age,')') as person_information
FROM person_order,person
WHERE person_order.person_id = person.id
ORDER BY order_date,person_information