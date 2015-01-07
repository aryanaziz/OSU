#1 Find the film title and category name of all films in which SANDRA PECK acted
#Order the results by title, descending (use ORDER BY title DESC at the end of the query)
SELECT film.title as `Film Title`, category.`name` as 	`Category Name`
FROM 
(
	SELECT actor_id
	FROM actor
	WHERE first_name = 'Sandra'
	AND last_name = 'Peck'
) actor 
LEFT JOIN 
(
	SELECT actor_id, film_id
	FROM film_actor
) film_actor ON film_actor.actor_id = actor.actor_id
LEFT JOIN
(
	SELECT *
	FROM film
) film ON film.film_id = film_actor.film_id
LEFT JOIN
(
	SELECT *
	FROM film_category
) film_category ON film_category.film_id = film.film_id
LEFT JOIN
(
	SELECT *
	FROM category
) category ON category.category_id = film_category.category_id
ORDER BY title DESC;

#2 We want to find out how many of each category of film each actor has started in so return a table with actor's id, actor's first name, actor's last name, category name and the count
#of the number of films that the actor was in which were in that category. Order the results by the actor's id, last name, first name and category name ascending. (Please pay attention that there may be many actors with the same last names, and also there may be few actors with the exact same first names and last names)
SELECT actor.actor_id, actor.first_name, actor.last_name, category.`name` as category_name, count(film.film_id) as count_films
FROM 
(
	SELECT actor_id, first_name, last_name
	FROM actor
) actor 
LEFT JOIN 
(
	SELECT actor_id, film_id
	FROM film_actor
) film_actor ON film_actor.actor_id = actor.actor_id
LEFT JOIN
(
	SELECT *
	FROM film
) film ON film.film_id = film_actor.film_id
LEFT JOIN
(
	SELECT *
	FROM film_category
) film_category ON film_category.film_id = film.film_id
LEFT JOIN
(
	SELECT *
	FROM category
) category ON film_category.category_id = category.category_id
GROUP BY actor.actor_id, actor.first_name, actor.last_name, category.`name`
ORDER BY actor.actor_id, actor.last_name, actor.first_name, category.`name` ASC;


#3 Find the first name, last name and total combined film length of Action films for every actor whose last name starts with 'B'.
#That is the result should list the names of actors and the total lenght of Action films they have been in.(Your query should also list those actors whose last names start with 'B', but never acted in an Action film.)

SELECT actor.first_name, actor.last_name, sum(CASE WHEN category.id = 1 THEN film.length ELSE 0 END)
FROM
(
	SELECT actor_id, first_name, last_name
	FROM actor
	WHERE last_name LIKE 'B%'
) actor
LEFT JOIN 
(
	SELECT actor_id as actorid, film_id
	FROM film_actor
) film_actor ON film_actor.actorid = actor.actor_id
LEFT JOIN
(
	SELECT film_id as filmid, length
	FROM film
) film ON film.filmid = film_actor.film_id
LEFT JOIN
(
	SELECT film_id as categoryFilmId, category_id
	FROM film_category
) film_category ON film_category.categoryFilmId = film.filmid
LEFT JOIN
(
	SELECT category_id as id
	FROM category
) category ON film_category.category_id = category.id
GROUP BY actor.actor_id;

#4 Find the first name and last name of all actors who have never been in an Action film that has a length of more than 100 minutes.
SELECT overall.first_name, overall.last_name
FROM
(
	SELECT *
	FROM
	(
		SELECT actor_id, first_name, last_name
		FROM actor
	) actor
	LEFT JOIN 
	(
		SELECT actor_id as actorid, film_id
		FROM film_actor
	) film_actor ON film_actor.actorid = actor.actor_id
	LEFT JOIN
	(
		SELECT film_id as filmid, length
		FROM film
	) film ON film.filmid = film_actor.film_id
	LEFT JOIN
	(
		SELECT film_id as categoryFilmId, category_id
		FROM film_category
	) film_category ON film_category.categoryFilmId = film.filmid
	LEFT JOIN
	(
		SELECT category_id as id
		FROM category
	) category ON film_category.category_id = category.id
	HAVING category.id = 1
	AND film.length <= 100
) overall
GROUP BY overall.first_name, overall.last_name;


#5 Find the film title of all films which feature both SCARLETT DAMON and BEN HARRIS
#Order the results by title, descending (use ORDER BY title DESC at the end of the query)
#Warning, this is a tricky one and while the syntax is all things you know, you have to think oustide
#the box a bit to figure out how to get a table that shows pairs of actors in movies

SELECT title
FROM 
(
	SELECT *
	FROM
	(
		SELECT *
		FROM actor
		WHERE first_name = 'SCARLETT' AND last_name = 'DAMON'
	) actor 
	LEFT JOIN
	(
		SELECT actor_id as actorid, film_id as filmid
		FROM film_actor
	) film_actor ON actor.actor_id = film_actor.actorid
	LEFT JOIN
	(
		SELECT film_id, title
		FROM film
	) film ON film_actor.filmid = film.film_id
) scarlett
INNER JOIN
(
	SELECT *
	FROM
	(
		SELECT *
		FROM actor
		WHERE first_name = 'BEN' AND last_name = 'HARRIS'
	) actor 
	LEFT JOIN
	(
		SELECT actor_id as actorid, film_id
		FROM film_actor
	) film_actor ON actor.actor_id = film_actor.actorid
) ben ON scarlett.film_id = ben.film_id
ORDER BY title DESC
