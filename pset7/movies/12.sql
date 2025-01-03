SELECT title FROM movies WHERE movies.id IN 
(
    SELECT stars.movie_id 
    FROM stars 
    WHERE stars.person_id = (SELECT id FROM people WHERE name = 'Johnny Depp')
)
AND movies.id IN
(
    SELECT stars.movie_id 
    FROM stars 
    WHERE stars.person_id = (SELECT id FROM people WHERE name = 'Helena Bonham Carter')
);