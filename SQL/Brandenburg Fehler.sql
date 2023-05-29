
SELECT distinct b.Land_ID, b.Region_ID, b.Kreis_ID, b.Gemeinde_ID, b.Ortsteil_ID, b.Land, b.Kreis, b.Gemeinde, b.ort
FROM Brandenburg b
where EXISTS (
   SELECT a.Land_ID, a.Region_ID, a.Kreis_ID, a.Gemeinde_ID, a.Ortsteil_ID, a.Kreis, a.Gemeinde, count(*) AS test
   FROM Brandenburg_District_Township a
   WHERE b.Land_ID = a.Land_ID AND b.Region_ID = a.Region_ID AND b.Kreis_ID = a.Kreis_ID AND b.Gemeinde_ID = a.Gemeinde_ID AND b.Ortsteil_ID = a.Ortsteil_ID
   GROUP BY a.Land_ID, a.Region_ID, a.Kreis_ID, a.Gemeinde_ID, a.Ortsteil_ID, a.Kreis, a.Gemeinde
   having count(*) > 1
   )
