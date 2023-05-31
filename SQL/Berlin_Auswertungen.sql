SELECT a.Strasse_ID, count(*) AS Anzahl
FROM (SELECT DISTINCT Strasse_ID, Bezirk_ID FROM Berlin) A
GROUP BY A.Strasse_ID
HAVING Count(*) > 1
ORDER BY 2 DESC;

SELECT A.Strasse, count(*) AS Anzahl
FROM (SELECT DISTINCT Strasse_ID, Strasse FROM Berlin) A
GROUP BY A.Strasse
HAVING Count(*) > 1
ORDER BY 2 DESC;

SELECT Strasse_ID, Strasse, count(*) AS Anzahl
FROM Berlin
GROUP BY Strasse_ID, Strasse 
ORDER BY 3 DESC

