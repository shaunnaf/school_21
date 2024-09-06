SELECT address,pizzeria.name,count(*) AS count_of_orders
FROM person
join person_order on person_order.id = person.id
join menu on person_order.menu_id = menu.id
join pizzeria on pizzeria.id = menu.pizzeria_id
group by address, pizzeria.name
order by address