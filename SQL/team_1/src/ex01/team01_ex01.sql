insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

CREATE OR REPLACE FUNCTION nearest_rate(b_currency_id bigint, b_date timestamp) RETURNS numeric AS $$
DECLARE res numeric = NULL;
BEGIN
SELECT rate_to_usd INTO res FROM (
        (SELECT rate_to_usd, (C.updated - b_date) as time_diff FROM currency C
            WHERE C.updated > b_date and C.id = b_currency_id
            ORDER BY time_diff
            LIMIT 1
        )
        UNION
        (SELECT rate_to_usd, (b_date - C1.updated) as time_diff FROM currency C1
            WHERE C1.updated < b_date and C1.id = b_currency_id
            ORDER BY time_diff
            LIMIT 1
        )
        ORDER BY time_diff 
        LIMIT 1
    ) R;
RETURN res;
END;
$$ LANGUAGE plpgsql;

SELECT
    COALESCE(U.name, 'not defined') AS name,
    COALESCE(U.lastname, 'not defined') AS lastname,
    C.name AS currency_name,
    ROUND(B.money * nearest_rate(B.currency_id, b.updated), 2) AS currency_in_usd
FROM balance B
    LEFT JOIN "user" U ON B.user_id = U.id
    LEFT JOIN (SELECT distinct id, name from currency) C ON c.id = B.currency_id
WHERE
    C.name is not NULL
ORDER BY 1 DESC, 2, 3;
