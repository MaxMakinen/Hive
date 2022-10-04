SELECT `name` AS `name`
FROM distrib
WHERE LOWER(`name`) LIKE '%y%y%' OR LOWER(`name`) LIKE '%yy%'
OR id_distrib IN ('42', '62', '63', '64', '65', '66', '67', '68', '69', '71', '88', '89', '90')
LIMIT 2,5;