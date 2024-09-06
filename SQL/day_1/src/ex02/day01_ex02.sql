SELECT first.pizza_name
FROM menu first
WHERE NOT EXISTS (
    SELECT *
    FROM menu second
    WHERE second.pizza_name = first.pizza_name
    AND second.id < first.id
)
ORDER BY first.pizza_name DESC;