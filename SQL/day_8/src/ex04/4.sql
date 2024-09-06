-- Session #1
begin transaction isolation level read committed;
select * from pizzeria where  name  = 'Pizza Hut';
select * from pizzeria where  name  = 'Pizza Hut';
commit;
select * from pizzeria where  name  = 'Pizza Hut';

--Session #2
begin transaction isolation level read committed;
update pizzeria set rating = 3.0 where name  = 'Pizza Hut';
commit;
select * from pizzeria where  name  = 'Pizza Hut';