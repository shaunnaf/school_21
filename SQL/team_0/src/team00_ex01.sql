CREATE TABLE nodes(
    point1 varchar,
    point2 varchar,
    cost int
);

INSERT INTO nodes (point1,point2,cost)
VALUES('a','b',10),
      ('b','a',10),
      ('a','c',15),
      ('c','a',15),
      ('a','d',20),
      ('d','a',20),
      ('b','c',35),
      ('c','b',35),
      ('b','d',25),
      ('d','b',25),
      ('c','d',30),
      ('d','c',30);


WITH allcost AS (SELECT min(n1.cost + n2.cost + n3.cost + n4.cost) as min_total_cost,
                        MAX(n1.cost  + n2.cost  + n3.cost  + n4.cost) as max_total_cost
                 FROM nodes n1
                     JOIN nodes n2 ON n1.point2 = n2.point1
                     JOIN nodes n3 ON n2.point2 = n3.point1
                     JOIN nodes n4 ON n3.point2 = n4.point1
                 WHERE n1.point1 = 'a'
                   AND n4.point2 = 'a'
                   AND n3.point1 != n1.point1
                   AND n4.point1 != n2.point1
                 )

SELECT (n1.cost + n2.cost + n3.cost + n4.cost) as total_cost,
       '{' || n1.point1 || ',' || n1.point2 || ',' || n2.point2 || ',' || n3.point2 || ',' || n4.point2 || '}' as tour
FROM nodes n1
JOIN nodes n2 ON n1.point2 = n2.point1
JOIN nodes n3 ON n2.point2 = n3.point1
JOIN nodes n4 ON n3.point2 = n4.point1
CROSS JOIN allcost
WHERE n1.point1 = 'a'
    AND n4.point2 = 'a'
    AND n3.point1 != n1.point1
    AND n4.point1 != n2.point1
    AND ((n1.cost + n2.cost + n3.cost + n4.cost) = allcost.min_total_cost
    OR (n1.cost + n2.cost + n3.cost + n4.cost)  = allcost.max_total_cost)
ORDER BY total_cost,tour;


