- Session #1
begin transaction isolation level repeatable read;
select * from pizzeria where  name  = 'Pizza Hut';
select * from pizzeria where  name  = 'Pizza Hut';
commit;
select * from pizzeria where  name  = 'Pizza Hut';

--Session #2
begin transaction isolation level repeatable read;
update pizzeria set rating = 3.6 where name  = 'Pizza Hut';
commit;
select * from pizzeria where  name  = 'Pizza Hut';