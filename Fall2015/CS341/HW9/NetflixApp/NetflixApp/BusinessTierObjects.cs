//
// BusinessTier objects:  these classes define the objects serving as data 
// transfer between UI and business tier.  These objects carry the data that
// is normally displayed in the presentation tier.  The classes defined here:
//
//    Movie
//    Review
//    User
//    MovieDetail
//    UserDetail
//
// NOTE: the presentation tier should not be creating instances of these objects,
// but instead calling the BusinessTier logic to obtain these objects.  You can 
// create instances of these objects if you want, but doing so has no impact on
// the underlying data store --- to change the data store, you have to call the
// BusinessTier logic.
//

using System;
using System.Collections.Generic;


namespace BusinessTier
{

  //
  // Movie:
  //
  public class Movie
  {
    public readonly int MovieID;
    public readonly string MovieName;

    public Movie(int movieId, string movieName)
    {
      MovieID = movieId;
      MovieName = movieName;
    }

  }//class


  //
  // Review:
  //
  public class Review
  {
    public readonly int ReviewID;
    public readonly int MovieID;
    public readonly int UserID;
    public readonly int Rating;

    public Review(int reviewId, int movieId, int userId, int rating)
    {
      ReviewID = reviewId;
      MovieID = movieId;
      UserID = userId;
      Rating = rating;
    }
  }//class


  //
  // User:
  //
  public class User
  {
    public readonly int UserID;
    public readonly string UserName;
    public readonly string Occupation;

    public User(int userId, string userName, string occupation)
    {
      UserID = userId;
      UserName = userName;
      Occupation = occupation;
    }
  }

 
  //
  // MovieDetail:
  //
  // Given a movie object, returns details about this movie --- reviews, average 
  // rating given, etc.  
  //
  // NOTE: the reviews are returned in order by rating (descending 5, 4, 3, ...),
  // with secondary sort based on user id (ascending).
  //
  public class MovieDetail
  {
    public readonly Movie movie;
    public readonly double AvgRating;
    public readonly int NumReviews;
    public readonly IReadOnlyList<Review> Reviews;

    public MovieDetail(Movie m, double avgRating, int numReviews, IReadOnlyList<Review> reviews)
    {
      movie = m;
      AvgRating = avgRating;
      NumReviews = numReviews;
      Reviews = reviews;
    }
  }


  //
  // UserDetail:
  //
  // Given a user object, returns details about this user --- reviews, average 
  // rating given, etc.
  //
  // NOTE: the reviews are returned in order by rating (descending 5, 4, 3, ...),
  // with secondary sort based on movie id (ascending).
  //
  public class UserDetail
  {
    public readonly User user;
    public readonly double AvgRating;
    public readonly int NumReviews;
    public readonly IReadOnlyList<Review> Reviews;

    public UserDetail(User u, double avgRating, int numReviews, IReadOnlyList<Review> reviews)
    {
      user = u;
      AvgRating = avgRating;
      NumReviews = numReviews;
      Reviews = reviews;
    }
  }

}//namespace
