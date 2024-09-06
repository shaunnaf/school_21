SELECT name,count(*) as count_of_visits
FROM person
join person_visits ON person.id = person_visits.person_id
group by name
having count(*) > 3
