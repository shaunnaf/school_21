SELECT address,
       round(max(age) - (min(age)/max(age)),2) as formula,
       round(avg(age),2) as average,
       round(max(age) - (min(age)/max(age)),2) > round(avg(age),2) as comparison
FROM person
GROUP BY address
ORDER BY address