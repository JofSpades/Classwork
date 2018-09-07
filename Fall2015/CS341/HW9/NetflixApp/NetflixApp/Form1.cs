//
// Netflix Database Application using N-tier Design
//
// Maxwell Petersen
// U. of Illinois, Chicago
// CS341, Fall 2015
// Homework 9
//

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;


namespace NetflixApp
{
  public partial class Form1 : Form
  {
    //
    // Class members:
    //
    private string m_connectionInfo;
    private BusinessTier.Business businessTier = new BusinessTier.Business("netflix.mdf");

    //
    // Constructor:
    //
    public Form1()
    {
      InitializeComponent();

      string filename, version;

      version = "v11.0";    // for VS 2013:
      //version = "MSSQLLocalDB";  // for VS 2015:
      filename = "netflix.mdf";

      m_connectionInfo = String.Format(@"Data Source=(LocalDB)\{0};AttachDbFilename=|DataDirectory|\{1};Integrated Security=True;", 
        version, 
        filename);
    }


    //
    // Form1_Load:  called just before the form is displayed to the user:
    //
    private void Form1_Load(object sender, EventArgs e)
    {
    }


    private void tbarRating_Scroll(object sender, EventArgs e)
    {
      lblRating.Text = tbarRating.Value.ToString();
    }

    //
    // Add Review:
    //
    private void cmdInsertReview_Click(object sender, EventArgs e)
    {
      //
      // Get the movie name from the list of movies:
      //
      if (this.listBox1.SelectedIndex < 0)
      {
        MessageBox.Show("Please select a movie...");
        return;
      }

      string MovieName = this.listBox1.Text;

      //
      // And the user name from the list of users:
      //
      if (this.listBox2.SelectedIndex < 0)
      {
        MessageBox.Show("Please select a user...");
        return;
      }

      string UserName = this.listBox2.Text;

      //
      // NOTE: since a movie and a user is selected, the movie and user IDs are 
      // available from the associated text boxes:
      //
      int movieid = Convert.ToInt32(this.txtMovieID.Text);
      int userid = Convert.ToInt32(this.txtUserID.Text);

      //
      // Insert movie review:
      //
      var rowsModified = businessTier.AddReview(movieid, userid, int.Parse(lblRating.Text));
      //
      // display results:
      //
      if (rowsModified != null) // success!
      {
        MessageBox.Show("Success, review added.");
      }
      else
      {
        MessageBox.Show("**Failure, insert was not added (?) **");
      }
    }


    //
    // All Movies:
    //
    private void cmdAllMovies_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();

      var movies = businessTier.GetAllMovies();
      foreach (BusinessTier.Movie m in movies)
      {
        this.listBox1.Items.Add(m.MovieName);
      }
    }


    //
    // When the user selects a movie, display movie id and average rating...
    //
    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      string name;

      name = this.listBox1.Text;  // selected movie:

      var movie = businessTier.GetMovie(name);

      if (movie == null)
      {
        MessageBox.Show("**Internal Error: movie not found");
        return;
      }
      var detail = businessTier.GetMovieDetail(movie.MovieID);
      if (detail == null)
      {
        MessageBox.Show("**Internal Error: details not found");
        return;
      }
      this.txtMovieID.Text = movie.MovieID.ToString();
      this.txtAvgRating.Text = detail.AvgRating.ToString();
    }


    //
    // Reviews for selected movie:
    //
    private void cmdMovieReviews_Click(object sender, EventArgs e)
    {
      string name;

      if (this.listBox1.SelectedIndex < 0)
      {
        MessageBox.Show("Please select a movie...");
        return;
      }

      name = this.listBox1.Text;

      //
      // NOTE: since a movie is selected, the movie id is in the associated textbox:
      //

      int movieid = Convert.ToInt32(this.txtMovieID.Text);

      var raitings = businessTier.GetMovieDetail(movieid);

      // 
      // Display the results in a subform:
      //
      SubForm frm = new SubForm();

      frm.lblHeader.Text = string.Format("Reviews for \"{0}\"", raitings.movie.ToString());

      frm.listBox1.Items.Add(name);
      frm.listBox1.Items.Add("");

      if (raitings == null)
      {
        frm.listBox1.Items.Add("No reviews...");
      }
      else
      {
        foreach (BusinessTier.Review review in raitings.Reviews)
        {
          string msg = string.Format("{0}: {1}",
            review.UserID, review.Rating);

          frm.listBox1.Items.Add(msg);
        }
      }

      frm.ShowDialog();
    }


    //
    // Summary of reviews (by each rating) for selected movie:
    //
    private void cmdReviewsSummary_Click(object sender, EventArgs e)
    {
      string name;

      if (this.listBox1.SelectedIndex < 0)
      {
        MessageBox.Show("Please select a movie...");
        return;
      }

      name = this.listBox1.Text;

      //
      // NOTE: since a movie is selected, the movie id is in the associated textbox:
      //

      int movieid = Convert.ToInt32(this.txtMovieID.Text);

      var raitings = businessTier.GetMovieDetail(movieid);

      //
      // display results:
      //
      SubForm frm = new SubForm();

      frm.lblHeader.Text = string.Format("Review Summary for \"{0}\"", raitings.movie);

      frm.listBox1.Items.Add(name);
      frm.listBox1.Items.Add("");
      
      if (raitings == null)
      {
        frm.listBox1.Items.Add("No reviews...");
      }
      else
      {
        int fives = 0;
        int fours = 0;
        int threes = 0;
        int twos = 0;
        int ones = 0;
        foreach (BusinessTier.Review review in raitings.Reviews)
        {
          if (review.Rating == 5)
          {
            ++fives;
          }
          else if (review.Rating == 4)
          {
            ++fours;
          }
          else if (review.Rating == 3)
          {
            ++threes;
          }
          else if (review.Rating == 2)
          {
            ++twos;
          }
          else if (review.Rating == 1)
          {
            ++ones;
          }
        }
        string msg = string.Format("5: {0}", fives);
        frm.listBox1.Items.Add(msg);
        msg = string.Format("4: {0}", fours);
        frm.listBox1.Items.Add(msg);
        msg = string.Format("3: {0}", threes);
        frm.listBox1.Items.Add(msg);
        msg = string.Format("2: {0}", twos);
        frm.listBox1.Items.Add(msg);
        msg = string.Format("1: {0}", ones);
        frm.listBox1.Items.Add(msg);
        frm.listBox1.Items.Add("");
        msg = string.Format("Total: {0}", businessTier.GetMovieDetail(movieid).NumReviews);
        frm.listBox1.Items.Add(msg);
      }

      frm.ShowDialog();
    }


    //
    // All Users:
    //
    private void cmdAllUsers_Click(object sender, EventArgs e)
    {
      listBox2.Items.Clear();

      var users = businessTier.GetAllNamedUsers();

      if (users == null)
      {
        MessageBox.Show("**Error: no users, is database empty?!");
      }
      else
      {
        //
        // we have ratings data, display:
        //
        foreach (BusinessTier.User user in users)
          listBox2.Items.Add(user.UserName.ToString());
      }
    }


    //
    // User has selected a user in the list:
    //
    private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      string name;

      name = this.listBox2.Text;  // selected user:

      var user = businessTier.GetNamedUser(name);

      if (user == null)
      {
        MessageBox.Show("**Error: user not found?!");

        this.txtUserID.Text = "";
        this.txtOccupation.Text = "";
      }
      else
      {
        this.txtUserID.Text = user.UserID.ToString();
        this.txtOccupation.Text = user.Occupation.ToString();
      }
    }


    //
    // Reviews for selected user:
    //
    private void cmdUserReviews_Click(object sender, EventArgs e)
    {
      string name;

      if (this.listBox2.SelectedIndex < 0)
      {
        MessageBox.Show("Please select a user...");
        return;
      }

      name = this.listBox2.Text;

      //
      // NOTE: since a user is selected, the user id is in the associated textbox:
      //

      int userid = Convert.ToInt32(this.txtUserID.Text);

      var selectedUser = businessTier.GetUserDetail(userid);

      // 
      // Display the results in a subform:
      //
      SubForm frm = new SubForm();

      frm.lblHeader.Text = string.Format("Reviews by \"{0}\"", selectedUser.user);

      frm.listBox1.Items.Add(selectedUser.user);
      frm.listBox1.Items.Add("");

      if (selectedUser == null)
      {
        frm.listBox1.Items.Add("No reviews...");
      }
      else
      {
        foreach (BusinessTier.Review review in selectedUser.Reviews)
        {
          string msg = string.Format("{0} -> {1}",
          businessTier.GetMovie(review.MovieID).MovieName, review.Rating);

          frm.listBox1.Items.Add(msg);
        }
      }

      frm.ShowDialog();
    }


    //
    // File >> Test Connection:
    //
    private void testConnectionToolStripMenuItem_Click(object sender, EventArgs e)
    {
      try
      {
        businessTier.TestConnection();
      }
      catch
      {
        MessageBox.Show("**Error: database file not found?!");
      }
    }


    //
    // File >> Exit:
    //
    private void exitToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.Close();
    }


    //
    // File >> Top Movies by Avg Rating:
    //
    private void topMoviesByRatingToolStripMenuItem_Click(object sender, EventArgs e)
    {
      var topNMovies = businessTier.GetTopMoviesByAvgRating(int.Parse(txtTopN.Text));

      if (topNMovies == null)
      {
        MessageBox.Show("**Error: no movies, is database empty?!");
      }
      else
      {
        //
        // we have ratings data, display in our subform:
        //
        SubForm frm = new SubForm();

        frm.lblHeader.Text = "Top Movies by Average Rating";

        foreach (BusinessTier.Movie movie in topNMovies)
        {
          string msg = string.Format("{0}: {1}",
            movie.MovieName, businessTier.GetMovieDetail(movie.MovieID).AvgRating);

          frm.listBox1.Items.Add(msg);
        }

        frm.ShowDialog();
      }
    }


    //
    // File >> Top Movies by Num Reviews:
    //
    private void topMoviesByNumReviewsToolStripMenuItem_Click(object sender, EventArgs e)
    {
      var topNNumReviews = businessTier.GetTopMoviesByNumReviews(int.Parse(txtTopN.Text));
      //
      // display results:
      //

      if (topNNumReviews == null)
      {
        MessageBox.Show("**Error: no movies, is database empty?!");
      }
      else
      {
        //
        // we have ratings data, display in our subform:
        //
        SubForm frm = new SubForm();

        frm.lblHeader.Text = "Top Movies by Number of Reviews";

        foreach (BusinessTier.Movie movie in topNNumReviews)
        {
          string msg = string.Format("{0}: {1}",
            movie.MovieName, businessTier.GetMovieDetail(movie.MovieID).NumReviews);

          frm.listBox1.Items.Add(msg);
        }

        frm.ShowDialog();
      }
    }


    //
    // File >> Top Users by New Reviews:
    //
    private void topUsersByNumReviewsToolStripMenuItem_Click(object sender, EventArgs e)
    {
      var topNUsers = businessTier.GetTopUsersByNumReviews(int.Parse(txtTopN.Text));
      //
      // display results:
      //

      if (topNUsers == null)
      {
        MessageBox.Show("**Error: no movies, is database empty?!");
      }
      else
      {
        //
        // we have ratings data, display in our subform:
        //
        SubForm frm = new SubForm();

        frm.lblHeader.Text = "Top Users by Number of Reviews";

        foreach (BusinessTier.User user in topNUsers)
        {
          string username = user.UserName;

          if (username == "")
            username = " <anonymous>";

          string msg = string.Format("{0}: {1}",
            username, businessTier.GetUserDetail(user.UserID).NumReviews);

          frm.listBox1.Items.Add(msg);
        }

        frm.ShowDialog();
      }
    }

  }//class
}//namespace
