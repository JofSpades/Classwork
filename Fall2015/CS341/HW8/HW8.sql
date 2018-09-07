SELECT Movies.MovieID, Movies.MovieName FROM Movies;
-----------------------------------------------------------------------------------------
SELECT Users.UserName, Users.UserID, Users.Occupation FROM Users;
-----------------------------------------------------------------------------------------
SELECT Reviews.UserID, Reviews.Raiting FROM Reviews
INNER JOIN
(
	SELECT Movies.MovieID, Movies.MovieName
	WHERE Movies.MovieID = {0}
) AS selectedMovie
WHERE Reviews.MovieID = selectedMovie.MovieID;
-----------------------------------------------------------------------------------------
SELECT Users.UserName FROM Users
ORDER BY Users.UserName ASC;

SELECT reviewsList.Raiting, Movies.MovieName FROM Movies
INNER JOIN
(
	SELECT Reviews.Raiting, Reviews.MovieID FROM Reviews
	INNER JOIN
	(
		SELECT Users.UserID FROM Users
		WHERE Users.UserName = {0}
	) AS userName
	WHERE Reviews.UserID = userName.UserID
) AS reviewsList
WHERE Movies.MovieID = reviewsList.MovieID
ORDER BY Movies.MovieName ASC
