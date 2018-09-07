//
// BusinessTier:  business logic, acting as interface between UI and data store.
//

using System;
using System.Collections.Generic;
using System.Data;


namespace BusinessTier
{

  //
  // Business:
  //
  public class Business
  {
    //
    // Fields:
    //
    private string _DBFile;
    private DataAccessTier.Data dataTier;


    //
    // Constructor:
    //
    public Business(string DatabaseFilename)
    {
      _DBFile = DatabaseFilename;

      dataTier = new DataAccessTier.Data(DatabaseFilename);
    }


    //
    // TestConnection:
    //
    // Returns true if we can establish a connection to the database, false if not.
    //
    public bool TestConnection()
    {
      return dataTier.TestConnection();
    }


    //
    // GetUser:
    //
    // Retrieves User object based on USER ID; returns null if user is not
    // found.
    //
    // NOTE: if the user exists in the Users table, then a name and occupation
    // is returned.  If the user does not exist in the Users table, then the user
    // id is looked up in the Reviews table.  If found, then the user is an
    // "anonymous" user, so a User object with name = "<UserID>" and no occupation
    // ("") is returned.  In other words, name = the user’s id surrounded by < >.
    //
    public User GetUser(int UserID)
    {
      DataTable user = dataTier.ExecuteNonScalarQuery(string.Format("SELECT Users.UserName, Users.Occupation FROM Users WHERE Users.UserID='{0}';", UserID)).Tables["TABLE"];

      if (user != null)
      {
        DataRow row = user.Rows[0];
        if (row["UserName"].ToString() == "")
        {
          return new User(UserID, string.Format("<{0}>", UserID), "");
        }
        return new User(UserID, row["UserName"].ToString(), row["Occupation"].ToString());
      }
      
      return null;
    }


    //
    // GetNamedUser:
    //
    // Retrieves User object based on USER NAME; returns null if user is not
    // found.
    //
    // NOTE: there are "named" users from the Users table, and anonymous users
    // that only exist in the Reviews table.  This function only looks up "named"
    // users from the Users table.
    //
    public User GetNamedUser(string UserName)
    {
      UserName = UserName.Replace("'", "''");

      DataTable user = dataTier.ExecuteNonScalarQuery(string.Format("SELECT Users.UserID, Users.Occupation FROM Users WHERE Users.UserName='{0}';", UserName)).Tables["TABLE"];

      if (user != null)
      {
        DataRow row = user.Rows[0];
        return new User(int.Parse(row["UserID"].ToString()), UserName, row["Occupation"].ToString());
      }

      return null;
    }


    //
    // GetAllNamedUsers:
    //
    // Returns a list of all the users in the Users table ("named" users), sorted 
    // by user name.
    //
    // NOTE: the database also contains lots of "anonymous" users, which this 
    // function does not return.
    //
    public IReadOnlyList<User> GetAllNamedUsers()
    {
      List<User> users = new List<User>();

      DataTable dt = dataTier.ExecuteNonScalarQuery(string.Format("SELECT * FROM Users ORDER BY Users.UserName ASC;")).Tables["TABLE"];

      foreach (DataRow row in dt.Rows)
      {
        if (row["UserName"] != null)
        {
          users.Add(new User(int.Parse(row["UserID"].ToString()), row["UserName"].ToString(), row["Occupation"].ToString()));
        }
      }

      return users;
    }


    //
    // GetMovie:
    //
    // Retrieves Movie object based on MOVIE ID; returns null if movie is not
    // found.
    //
    public Movie GetMovie(int MovieID)
    {
      DataTable movie = dataTier.ExecuteNonScalarQuery(string.Format("SELECT Movies.MovieName FROM Movies WHERE Movies.MovieID={0};", MovieID)).Tables["TABLE"];

      if (movie != null)
      {
        DataRow row = movie.Rows[0];
        return new Movie(MovieID, row["MovieName"].ToString());
      }

      return null;     
    }


    //
    // GetAllMovies:
    //
    // Returns a list of all the movies in the database, sorted by movie name.
    //
    public IReadOnlyList<Movie> GetAllMovies()
    {
      List<Movie> movies = new List<Movie>();

      DataTable dt = dataTier.ExecuteNonScalarQuery(string.Format("SELECT * FROM Movies ORDER BY Movies.MovieName ASC;")).Tables["TABLE"];

      foreach (DataRow row in dt.Rows)
      {
        movies.Add(new Movie(int.Parse(row["MovieID"].ToString()), row["MovieName"].ToString()));
      }

      return movies;
    }

    //
    // GetMovie:
    //
    // Retrieves Movie object based on MOVIE NAME; returns null if movie is not
    // found.
    //
    public Movie GetMovie(string MovieName)
    {
      DataTable movie = dataTier.ExecuteNonScalarQuery(string.Format("SELECT Movies.MovieID FROM Movies WHERE Movies.MovieName='{0}';", MovieName)).Tables["TABLE"];

      if (movie != null)
      {
        DataRow row = movie.Rows[0];
        return new Movie(int.Parse(row["MovieID"].ToString()), MovieName);
      }

      return null;   
    }


    //
    // AddReview:
    //
    // Adds review based on MOVIE ID, returning a Review object containing
    // the review, review's id, etc.  If the add failed, null is returned.
    //
    public Review AddReview(int MovieID, int UserID, int Rating)
    {
      if (dataTier.ExecuteActionQuery(string.Format("INSERT INTO Reviews(MovieID, UserID, Rating) Values({0}, {1}, {2});", MovieID, UserID, Rating)) == 1)
      {
        DataTable review = dataTier.ExecuteNonScalarQuery(string.Format("SELECT Reviews.ReviewID FROM Reviews WHERE Reviews.MovieID={0} AND Reviews.UserID={1} AND Reviews.Rating={2};", MovieID, UserID, Rating)).Tables["TABLE"];
        DataRow row = review.Rows[int.Parse(review.Rows.Count.ToString()) - 1];
        return new Review(int.Parse(row["ReviewID"].ToString()), MovieID, UserID, Rating);
      }
      
      return null;
    }


    //
    // GetMovieDetail:
    //
    // Given a MOVIE ID, returns detailed information about this movie --- all
    // the reviews, the total number of reviews, average rating, etc.  If the 
    // movie cannot be found, null is returned.
    //
    public MovieDetail GetMovieDetail(int MovieID)
    {
      Movie movie = GetMovie(MovieID);
      if (movie != null)
      {
        object result;
        DataTable reviews;
        double averageRaiting = 0.0;
        int numberReviews = 0;
        List<Review> outReviews = new List<Review>();
        result = dataTier.ExecuteScalarQuery(string.Format(@"SELECT ROUND(AVG(CAST(Rating AS Float)), 4) AS AvgRating 
          FROM Reviews
          INNER JOIN Movies ON Reviews.MovieID = Movies.MovieID
          WHERE Movies.MovieName='{0}';", movie.MovieName.Replace("'", "''")));
        if (result != null && result != DBNull.Value)
        {
          averageRaiting = double.Parse(result.ToString());
          reviews = dataTier.ExecuteNonScalarQuery(string.Format("SELECT * FROM Reviews WHERE MovieID={0}", MovieID)).Tables["TABLE"];
          if (reviews != null)
          {
            numberReviews = reviews.Rows.Count;
            foreach (DataRow row in reviews.Rows)
            {
              outReviews.Add(new Review(int.Parse(row["ReviewID"].ToString()), MovieID, int.Parse(row["UserID"].ToString()), int.Parse(row["Rating"].ToString())));
            }
          }
        }
        return new MovieDetail(movie, averageRaiting, numberReviews, outReviews);
      }
      return null;
    }


    //
    // GetUserDetail:
    //
    // Given a USER ID, returns detailed information about this user --- all
    // the reviews submitted by this user, the total number of reviews, average 
    // rating given, etc.  If the user cannot be found, null is returned.
    //
    public UserDetail GetUserDetail(int UserID)
    {
      User selectedUser = GetUser(UserID);
      if(selectedUser != null)
      {
        object result;
        DataTable reviews;
        List<Review> outReviews = new List<Review>();
        double averageRaiting = 0.0;
        int numberReviews = 0;
        result = dataTier.ExecuteScalarQuery(string.Format(@"SELECT ROUND(AVG(CAST(Rating AS Float)), 4) AS AvgRating 
          FROM Reviews
          INNER JOIN Users ON Reviews.UserID = Users.UserID
          WHERE Users.UserName='{0}';", selectedUser.UserName.Replace("'", "''")));
        if (result != null && result != DBNull.Value)
        {
          averageRaiting = double.Parse(result.ToString());
          reviews = dataTier.ExecuteNonScalarQuery(string.Format("SELECT * FROM Reviews WHERE UserID={0}", UserID)).Tables["TABLE"];
          if (reviews != null)
          {
            numberReviews = reviews.Rows.Count;
            foreach (DataRow row in reviews.Rows)
            {
              outReviews.Add(new Review(int.Parse(row["ReviewID"].ToString()), int.Parse(row["MovieID"].ToString()), UserID, int.Parse(row["Rating"].ToString())));
            }
          }
        }
        return new UserDetail(selectedUser, averageRaiting, numberReviews, outReviews);
      }
      
      return null;
    }


    //
    // GetTopMoviesByAvgRating:
    //
    // Returns the top N movies in descending order by average rating.  If two
    // movies have the same rating, the movies are presented in ascending order
    // by name.  If N < 1, an EMPTY LIST is returned.
    //
    public IReadOnlyList<Movie> GetTopMoviesByAvgRating(int N)
    {
      List<Movie> movies = new List<Movie>();
      if (N < 1)
      {
        return movies;
      }
      DataTable movieList = dataTier.ExecuteNonScalarQuery(string.Format(@"SELECT TOP {0} Movies.MovieName, g.AvgRating, Movies.MovieID 
            FROM Movies
            INNER JOIN 
              (
                SELECT MovieID, ROUND(AVG(CAST(Rating AS Float)), 4) as AvgRating 
                FROM Reviews
                GROUP BY MovieID
              ) g
            ON g.MovieID = Movies.MovieID
            ORDER BY g.AvgRating DESC, Movies.MovieName Asc;",
        N)).Tables["TABLE"];
      if (movieList == null)
      {
        return null;
      }
      foreach (DataRow row in movieList.Rows)
      {
        movies.Add(new Movie(int.Parse(row["MovieID"].ToString()), row["MovieName"].ToString()));
      }
      return movies;
    }


    //
    // GetTopMoviesByNumReviews
    //
    // Returns the top N movies in descending order by number of reviews.  If two
    // movies have the same number of reviews, the movies are presented in ascending
    // order by name.  If N < 1, an EMPTY LIST is returned.
    //
    public IReadOnlyList<Movie> GetTopMoviesByNumReviews(int N)
    {
      List<Movie> movies = new List<Movie>();
      if (N < 1)
      {
        return movies;
      }
      DataTable movieList = dataTier.ExecuteNonScalarQuery(string.Format(@"SELECT TOP {0} Movies.MovieName, g.RatingCount, Movies.MovieID
            FROM Movies
            INNER JOIN 
              (
                SELECT MovieID, COUNT(*) as RatingCount 
                FROM Reviews
                GROUP BY MovieID
              ) g
            ON g.MovieID = Movies.MovieID
            ORDER BY g.RatingCount DESC, Movies.MovieName Asc;",
        N)).Tables["TABLE"];
      if (movieList == null)
      {
        return null;
      }
      foreach (DataRow row in movieList.Rows)
      {
        movies.Add(new Movie(int.Parse(row["MovieID"].ToString()), row["MovieName"].ToString()));
      }
      return movies;
    }


    //
    // GetTopUsersByNumReviews
    //
    // Returns the top N users in descending order by number of reviews.  If two
    // users have the same number of reviews, the users are presented in ascending
    // order by user id.  If N < 1, an EMPTY LIST is returned.
    //
    // NOTE: not all user ids map to users in the Users table.  User ids that don't
    // map over are considered "anonymous" users, and returned with their name =
    // to their userid ("<UserID>") and no occupation ("").
    //
    public IReadOnlyList<User> GetTopUsersByNumReviews(int N)
    {
      List<User> users = new List<User>();
      if (N < 1)
      {
        return users;
      }
      //
      // execute query to rank users:
      //
      // NOTE: some reviews are anonymous, i.e. we don't have a username.  So we
      // use a "RIGHT JOIN" to capture those as well.
      //
      DataTable userList = dataTier.ExecuteNonScalarQuery(string.Format(@"SELECT TOP {0} Temp.UserID, Users.UserName, Users.Occupation
            FROM Users
            RIGHT JOIN
            (
              SELECT UserID, COUNT(*) AS RatingCount
              FROM Reviews
              GROUP BY UserID
            ) AS Temp
            On Temp.UserID = Users.UserID
            ORDER BY Temp.RatingCount DESC, Users.UserName Asc;",
        N)).Tables["TABLE"];
      foreach (DataRow row in userList.Rows)
      {
        if (row["UserName"].ToString() == "")
        {
          users.Add(new User(int.Parse(row["UserID"].ToString()), string.Format("<{0}>", int.Parse(row["UserID"].ToString())), ""));
        }
        else
        {
          users.Add(new User(int.Parse(row["UserID"].ToString()), row["UserName"].ToString(), row["Occupation"].ToString()));
        }
      }
      return users;
    }

  }//class
}//namespace
