SELECT 
genre.id_genre AS `id_genre`, 
IFNULL(genre.name, " ") AS `name_genre`,
IFNULL(distrib.id_distrib, " ") AS `id_distrib`,
distrib.name AS `name_distrib`, 
film.title AS `title_film`
FROM genre 
INNER JOIN film ON genre.id_genre = film.id_genre
INNER JOIN distrib ON film.id_distrib = distrib.id_distrib
WHERE genre.id_genre BETWEEN '4' AND '8';