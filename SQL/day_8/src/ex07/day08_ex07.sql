-- Session #1
    begin;
    update pizzeria set rating = 2 where id = 1;
    update pizzeria set rating = 2 where id = 2;
    commit;
	select * from pizzeria where id = 1;
	select * from pizzeria where id = 2;
	
    --Session #2
    begin;
    update pizzeria set rating = 1 where id = 2;
    update pizzeria set rating = 1 where id = 1;
    commit;
	select * from pizzeria where id = 1;
	select * from pizzeria where id = 2;