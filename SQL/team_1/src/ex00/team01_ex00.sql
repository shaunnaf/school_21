with cte_last_rate AS (
      SELECT currency.id, currency.name AS currency_name, 
      (SELECT rate_to_usd FROM currency 
         WHERE currency.updated IN 
            (SELECT MAX(currency.updated) FROM currency) AND id = balance.currency_id) AS last_rate
        FROM currency 
            JOIN balance ON balance.currency_id = currency.id
        GROUP BY
            currency.id,
            currency_name,
            balance.currency_id
    )
SELECT
    COALESCE(U.name, 'not defined') AS name,
    COALESCE(U.lastname, 'not defined') AS lastname,
    balance.type,
    SUM(balance.money) AS volume,
    COALESCE(currency_name, 'not defined') AS currency_name,
    COALESCE(last_rate, 1) as last_rate_to_usd,
    SUM(balance.money) * COALESCE(last_rate, 1) AS total_volume_in_usd
FROM balance 
    FULL JOIN "user" U ON U.id = balance.user_id
    Full JOIN cte_last_rate CTE_LC ON balance.currency_id = CTE_LC.id
GROUP BY
    type,
    U.id,
    currency_id,
    currency_name,
    last_rate
ORDER BY 1 DESC, 2, 3;
