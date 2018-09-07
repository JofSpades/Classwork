//
// Netflix Database Application
//
// Maxwell Petersen
// U. of Illinois, Chicago
// CS341, Fall 2015
// Homework 8
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

namespace HW8
{
    public partial class Form1 : Form
    {
        // these are decalred here to save space farther down in re decleration for every SQL querey
        // THe data tables are to minimize the amount of quereies needed to be made
        private DataTable usersDataTable;
        private DataTable moviesDataTable;
        private string filename, version, connectionInfo, sql, msg;
        private SqlCommand cmd;
        private SqlConnection db;
        //flags for which button has been clicked
        private int previousListbox1 = 0;
        private int previousListbox2 = 0;
        // stored data needed for more than one event
        private int userID, movieID;
        public Form1()
        {
            //I am getting and storing the full list of users and movies for continued use
            InitializeComponent();
            this.version = "v11.0";
            this.filename = "netflix.mdf";
            this.connectionInfo = String.Format(@"Data Source=(LocalDB)\{0};AttachDbFilename=|DataDirectory|\{1};Integrated Security=True;", version, filename);
            this.db = new SqlConnection(this.connectionInfo);
            this.db.Open();
            this.sql = string.Format(@"SELECT Movies.MovieName, Movies.MovieID FROM Movies
                                  ORDER BY Movies.MovieName ASC");
            this.cmd = new SqlCommand();
            this.cmd.Connection = this.db;
            this.cmd.CommandText = this.sql;
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);
            this.moviesDataTable = ds.Tables["TABLE"];
            this.sql = string.Format(@"SELECT Users.UserName, Users.UserID, Users.Occupation FROM Users
                                  ORDER BY Users.UserName ASC");
            this.cmd = new SqlCommand();
            this.cmd.Connection = this.db;
            this.cmd.CommandText = this.sql;
            adapter = new SqlDataAdapter(cmd);
            ds = new DataSet();
            adapter.Fill(ds);
            this.db.Close();
            this.usersDataTable = ds.Tables["TABLE"];
            this.db.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // printing out the movies and movieID's
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();

            foreach (DataRow row in this.moviesDataTable.Rows)
            {
                msg = string.Format("{0}: {1}", row[1].ToString(), row[0].ToString());
                listBox1.Items.Add(msg);
            }

            this.listBox1.Visible = true;
        }
        private void button2_Click(object sender, EventArgs e)
        {
            // printing out hte list of users
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();

            foreach (DataRow row in this.usersDataTable.Rows)
            {
                msg = string.Format("{0}: {1}: {2}", row[0].ToString(), row[1].ToString(), row[2].ToString());
                listBox1.Items.Add(msg);
            }

            this.listBox1.Visible = true;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            // printing out the list of movies to allow for selection for the reviews 
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();

            foreach (DataRow row in this.moviesDataTable.Rows)
            {
                msg = string.Format("{0}: {1}", row[1].ToString(), row[0].ToString());
                listBox1.Items.Add(msg);
            }
            // displaying the list once it has been printed
            this.listBox1.Visible = true;
            // settign the flag for the first list box to know how to deal with the selection
            previousListbox1 = 3;

        }
        private void button4_Click(object sender, EventArgs e)
        {
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            // printout of user and userID for selection
            foreach (DataRow row in this.usersDataTable.Rows)
            {
                this.msg = string.Format("{0}", row[0].ToString());
                listBox1.Items.Add(this.msg);
                this.msg = string.Format("{0}", row[1].ToString());
                listBox2.Items.Add(this.msg);
            }
            // showing the information and setting the needed flags
            this.listBox1.Visible = true;
            this.listBox2.Visible = true;
            this.previousListbox1 = 4;
            this.previousListbox2 = 4;
        }
        private void button5_Click(object sender, EventArgs e)
        {
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            //displaying the usernames, userID's, movieNames, and MovieID's for selection
            foreach (DataRow row in this.usersDataTable.Rows)
            {
                this.msg = string.Format("{0}: {1}", row[0].ToString(), row[1].ToString());
                listBox1.Items.Add(this.msg);
            }
            foreach (DataRow row in this.moviesDataTable.Rows)
            {
                msg = string.Format("{0}: {1}", row[1].ToString(), row[0].ToString());
                listBox2.Items.Add(msg);
            }
            //only showing the users to create a flow from one step to another
            this.listBox1.Visible = true;
            //setting the flags
            this.previousListbox1 = 5;
            this.previousListbox2 = 5;
        }
        private void button6_Click(object sender, EventArgs e)
        {
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            // displaying the movieNames and Movie ID's
            foreach (DataRow row in this.moviesDataTable.Rows)
            {
                msg = string.Format("{0}: {1}", row[1].ToString(), row[0].ToString());
                listBox1.Items.Add(msg);
            }

            this.listBox1.Visible = true;
            // setting the flag
            this.previousListbox1 = 6;
        }
        private void button7_Click(object sender, EventArgs e)
        {
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            // displaying the movieNames and Movie ID's
            foreach (DataRow row in this.moviesDataTable.Rows)
            {
                msg = string.Format("{0}: {1}", row[1].ToString(), row[0].ToString());
                listBox1.Items.Add(msg);
            }

            this.listBox1.Visible = true;
            // setting the flag
            this.previousListbox1 = 7;
        }
        private void button8_Click(object sender, EventArgs e)
        {
            // setup
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            //getting an "N" to compute
            int n = int.Parse(Microsoft.VisualBasic.Interaction.InputBox("Provide a value to limit number returned", "N", "10"));
            this.db = new SqlConnection(this.connectionInfo);
            this.db.Open();
            this.sql = string.Format(@"SELECT TOP {0} Movies.MovieName, Temp.AvgRating
FROM Movies
INNER JOIN
(
SELECT Reviews.MovieID,
ROUND(AVG(CAST(Reviews.Rating AS Float)), 4) as AvgRating
FROM Reviews
GROUP BY Reviews.MovieID
) AS Temp
ON Temp.MovieID = Movies.MovieID
ORDER BY Temp.AvgRating DESC, Movies.MovieName ASC;", n);
            this.cmd = new SqlCommand();
            this.cmd.Connection = this.db;
            this.cmd.CommandText = this.sql;
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);
            this.db.Close();
            DataTable ratingsDataTable = ds.Tables["TABLE"];
            //check for no reviews
            if (ratingsDataTable.Rows.Count == 0)
            {
                this.msg = "NO RAITINGS";
                this.listBox1.Items.Add(this.msg);
            }
            // dsisplaying the list of ratings the user has made
            else
            {
                foreach (DataRow row in ratingsDataTable.Rows)
                {
                    msg = string.Format("{0}: {1}", row[0].ToString(), row[1].ToString());
                    listBox1.Items.Add(msg);
                }
            }
            // show information
            this.listBox1.Visible = true;
        }
        private void button9_Click(object sender, EventArgs e)
        {
            // setup
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            //getting an "N" to compute
            int n = int.Parse(Microsoft.VisualBasic.Interaction.InputBox("Provide a value to limit number returned", "N", "10"));
            this.db = new SqlConnection(this.connectionInfo);
            this.db.Open();
            this.sql = string.Format(@"SELECT TOP {0} Movies.MovieName, Temp.count
FROM Movies
INNER JOIN
(
SELECT Reviews.MovieID,
COUNT(Reviews.ReviewID) as count
FROM Reviews
GROUP BY Reviews.MovieID
) AS Temp
ON Temp.MovieID = Movies.MovieID
ORDER BY Temp.count DESC, Movies.MovieName ASC;", n);
            this.cmd = new SqlCommand();
            this.cmd.Connection = this.db;
            this.cmd.CommandText = this.sql;
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);
            this.db.Close();
            DataTable ratingsDataTable = ds.Tables["TABLE"];
            //check for no reviews
            if (ratingsDataTable.Rows.Count == 0)
            {
                this.msg = "NO RAITINGS";
                this.listBox1.Items.Add(this.msg);
            }
            // dsisplaying the list of ratings the user has made
            else
            {
                foreach (DataRow row in ratingsDataTable.Rows)
                {
                    msg = string.Format("{0}: {1}", row[0].ToString(), row[1].ToString());
                    listBox1.Items.Add(msg);
                }
            }
            // show information
            this.listBox1.Visible = true;
        }
        private void button10_Click(object sender, EventArgs e)
        {
            // setup
            this.listBox1.Visible = false;
            this.listBox2.Visible = false;
            this.listBox3.Visible = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            //getting an "N" to compute
            int n = int.Parse(Microsoft.VisualBasic.Interaction.InputBox("Provide a value to limit number returned", "N", "10"));
            this.db = new SqlConnection(this.connectionInfo);
            this.db.Open();
            this.sql = string.Format(@"SELECT TOP {0} Users.UserName, Temp.count
FROM Users
INNER JOIN
(
SELECT Reviews.UserID,
COUNT(Reviews.ReviewID) as count
FROM Reviews
GROUP BY Reviews.UserID
) AS Temp
ON Temp.UserID = Users.UserID
ORDER BY Temp.count DESC, Users.UserName ASC;", n);
            this.cmd = new SqlCommand();
            this.cmd.Connection = this.db;
            this.cmd.CommandText = this.sql;
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);
            this.db.Close();
            DataTable ratingsDataTable = ds.Tables["TABLE"];
            //check for no reviews
            if (ratingsDataTable.Rows.Count == 0)
            {
                this.msg = "NO RAITINGS";
                this.listBox1.Items.Add(this.msg);
            }
            // dsisplaying the list of ratings the user has made
            else
            {
                foreach (DataRow row in ratingsDataTable.Rows)
                {
                    msg = string.Format("{0}: {1}", row[0].ToString(), row[1].ToString());
                    listBox1.Items.Add(msg);
                }
            }
            // show information
            this.listBox1.Visible = true;
        }
        private void button11_Click(object sender, EventArgs e)
        {
            //getting the information form the text box for the insert
            int rating;
            if (int.TryParse(this.textBox1.Text, out rating))
            {
                // checking for the provided value to be in the range (1,5)
                if (rating > 0 && rating <= 5)
                {
                    //inserting using the previously stored values
                    this.db = new SqlConnection(this.connectionInfo);
                    this.db.Open();
                    this.sql = string.Format(@"INSERT INTO Reviews (MovieID, USerID, Rating)
VALUES ({0},{1},{2});", this.movieID, this.userID, rating);
                    this.cmd = new SqlCommand();
                    this.cmd.Connection = this.db;
                    this.cmd.CommandText = this.sql;
                    this.cmd.ExecuteNonQuery();
                    this.db.Close();
                    MessageBox.Show("Inserted the new rating");
                }
                else
                {
                    // error for improper value
                    MessageBox.Show("Value not between 1 and 5");
                }
            }
        }
        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            // flag for get movie reviews
            if (this.previousListbox1 == 3)
            {
                // obtaining the selected movie
                int index = listBox1.SelectedIndex;
                // error check
                if (index != -1)
                {
                    // saving a copy of the movies for indexing
                    var content = this.moviesDataTable.Rows;
                    this.db = new SqlConnection(this.connectionInfo);
                    this.db.Open();
                    this.sql = string.Format(@"SELECT Reviews.UserID, Reviews.Rating FROM Reviews
WHERE Reviews.MovieID = {0}
ORDER BY Reviews.Rating DESc,Reviews.UserID ASC", content[index][1]);
                    this.cmd = new SqlCommand();
                    this.cmd.Connection = this.db;
                    this.cmd.CommandText = this.sql;
                    SqlDataAdapter adapter = new SqlDataAdapter(cmd);
                    DataSet ds = new DataSet();
                    adapter.Fill(ds);
                    this.db.Close();
                    DataTable ratingsDataTable = ds.Tables["TABLE"];
                    // adding the name
                    this.msg = string.Format("{0}:", content[index][0]);
                    this.listBox2.Items.Add(this.msg);
                    // if no reviews displaying so
                    if (ratingsDataTable.Rows.Count == 0)
                    {
                        msg = "NO RATINGS";
                        this.listBox2.Items.Add(this.msg);
                    }
                    // display the list of reviews by user ID
                    else
                    {
                        foreach (DataRow row in ratingsDataTable.Rows)
                        {
                            this.msg = string.Format("{0}: {1}", row[0].ToString(), row[1].ToString());
                            listBox2.Items.Add(this.msg);
                        }
                    }
                    // showing the information
                    this.listBox2.Visible = true;
                }
            }
                //flag for reviws by user
            else if (this.previousListbox1 == 4)
            {
                // obtaining index
                int index = listBox1.SelectedIndex;
                this.listBox3.Items.Clear();
                //error check
                if (index != -1)
                {
                    var content = this.usersDataTable.Rows;
                    this.db = new SqlConnection(this.connectionInfo);
                    this.db.Open();
                    this.sql = string.Format(@"SELECT Movies.MovieName, reviewList.Rating FROM Movies
INNER JOIN
(
    SELECT Reviews.Rating, Reviews.MovieID FROM Reviews
    WHERE Reviews.UserID = {0}
) AS reviewList
ON Movies.MovieID = reviewList.MovieID
ORDER BY Movies.MovieName ASC;", content[index][1]);
                    this.cmd = new SqlCommand();
                    this.cmd.Connection = this.db;
                    this.cmd.CommandText = this.sql;
                    SqlDataAdapter adapter = new SqlDataAdapter(cmd);
                    DataSet ds = new DataSet();
                    adapter.Fill(ds);
                    this.db.Close();
                    DataTable ratingsDataTable = ds.Tables["TABLE"];
                    //check for no reviews
                    if (ratingsDataTable.Rows.Count == 0)
                    {
                        this.msg = "NO RAITINGS";
                        this.listBox3.Items.Add(this.msg);
                    }
                        // dsisplaying the list of ratings the user has made
                    else
                    {
                        foreach (DataRow row in ratingsDataTable.Rows)
                        {
                            msg = string.Format("{0}: {1}", row[0].ToString(), row[1].ToString());
                            listBox3.Items.Add(msg);
                        }
                    }
                    // show information
                    this.listBox3.Visible = true;
                }
            }
                // insert flag
            else if (this.previousListbox1 == 5)
            {
                //obtaining index
                int index = this.listBox1.SelectedIndex;
                // error check
                if (index != -1)
                {
                    //saving the selected user ID
                    var content = this.usersDataTable.Rows;
                    this.userID = int.Parse(content[index][1].ToString());
                    // allowing for the movie to be selected
                    this.listBox2.Visible = true;
                }
            }
                //flag for average rating of a movie
            else if (this.previousListbox1 == 6)
            {
                //obtaining the index
                int index = listBox1.SelectedIndex;
                this.listBox2.Items.Clear();
                //error check
                if (index != -1)
                {
                    var content = this.moviesDataTable.Rows;
                    this.db = new SqlConnection(this.connectionInfo);
                    this.db.Open();
                    this.sql = string.Format(@"SELECT ROUND(AVG(CAST(Reviews.Rating AS FLOAT)), 4) FROM Reviews
WHERE Reviews.MovieID = {0}", content[index][1]);
                    this.cmd = new SqlCommand();
                    this.cmd.Connection = this.db;
                    this.cmd.CommandText = this.sql;
                    object result = cmd.ExecuteScalar();
                    this.db.Close();
                    // printing hte movie name
                    this.msg = string.Format("{0}", content[index][0].ToString());
                    this.listBox2.Items.Add(this.msg);
                    //printing the average
                    this.msg = string.Format("Average: {0}", result);
                    this.listBox2.Items.Add(this.msg);
                    // showing the information
                    this.listBox2.Visible = true;
                }
            }
            else if (this.previousListbox1 == 7)
            {
                //obtaining the index
                int index = listBox1.SelectedIndex;
                this.listBox2.Items.Clear();
                //error check
                if (index != -1)
                {
                    var content = this.moviesDataTable.Rows;
                    object result = null;
                    // printing hte movie name
                    this.msg = string.Format("{0}", content[index][0].ToString());
                    this.listBox2.Items.Add(this.msg);
                    this.db = new SqlConnection(this.connectionInfo);
                    this.db.Open();
                    for (int i = 5; i > 0; --i)
                    {
                        this.sql = string.Format(@"SELECT COUNT(Reviews.Rating) FROM Reviews
WHERE Reviews.Rating = {1} AND Reviews.MovieID = {0}", content[index][1], i);
                        this.cmd = new SqlCommand();
                        this.cmd.Connection = this.db;
                        this.cmd.CommandText = this.sql;
                        result = cmd.ExecuteScalar();
                        //printing the amount of each review amount
                        this.msg = string.Format("{0}: {1}", i, result);
                        this.listBox2.Items.Add(this.msg);
                    }
                    this.sql = string.Format(@"SELECT COUNT(Reviews.Rating) FROM Reviews
WHERE Reviews.MovieID = {0}", content[index][1]);
                    this.cmd = new SqlCommand();
                    this.cmd.Connection = this.db;
                    this.cmd.CommandText = this.sql;
                    result = cmd.ExecuteScalar();
                    //printing the amount of each review amount
                    this.msg = string.Format("Total count: {0}", result);
                    this.listBox2.Items.Add(this.msg);
                    this.db.Close();
                    // showing the information
                    this.listBox2.Visible = true;
                }
            }
            else if (this.previousListbox1 == 8)
            {
                // obtaining index
                int index = listBox1.SelectedIndex;
                this.listBox3.Items.Clear();
                //error check
                if (index != -1)
                {
                    var content = this.usersDataTable.Rows;
                    this.db = new SqlConnection(this.connectionInfo);
                    this.db.Open();
                    this.sql = string.Format(@"SELECT TOP 10 Movies.MovieName, Temp.AvgRating
FROM Movies
INNER JOIN
(
SELECT Reviews.MovieID,
ROUND(AVG(CAST(Reviews.Rating AS Float)), 4) as AvgRating
FROM Reviews
GROUP BY Reviews.MovieID
) AS Temp
ON Temp.MovieID = Movies.MovieID
ORDER BY Temp.AvgRating DESC, Movies.MovieName ASC;");
                    this.cmd = new SqlCommand();
                    this.cmd.Connection = this.db;
                    this.cmd.CommandText = this.sql;
                    SqlDataAdapter adapter = new SqlDataAdapter(cmd);
                    DataSet ds = new DataSet();
                    adapter.Fill(ds);
                    this.db.Close();
                    DataTable ratingsDataTable = ds.Tables["TABLE"];
                    //check for no reviews
                    if (ratingsDataTable.Rows.Count == 0)
                    {
                        this.msg = "NO RAITINGS";
                        this.listBox3.Items.Add(this.msg);
                    }
                    // dsisplaying the list of ratings the user has made
                    else
                    {
                        foreach (DataRow row in ratingsDataTable.Rows)
                        {
                            msg = string.Format("{0}: {1}", row[0].ToString(), row[1].ToString());
                            listBox3.Items.Add(msg);
                        }
                    }
                    // show information
                    this.listBox3.Visible = true;
                }
            }
        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            //flag for user ratings list
            if (this.previousListbox2 == 4)
            {
                // getting index
                int index = listBox2.SelectedIndex;
                this.listBox3.Items.Clear();
                //error check
                if (index != -1)
                {
                    var content = this.usersDataTable.Rows;
                    this.db = new SqlConnection(this.connectionInfo);
                    this.db.Open();
                    this.sql = string.Format(@"SELECT Movies.MovieName, reviewList.Rating FROM Movies
INNER JOIN
(
    SELECT Reviews.Rating, Reviews.MovieID FROM Reviews
    WHERE Reviews.UserID = {0}
) AS reviewList
ON Movies.MovieID = reviewList.MovieID
ORDER BY Movies.MovieName ASC;", content[index][1]);
                    this.cmd = new SqlCommand();
                    this.cmd.Connection = this.db;
                    this.cmd.CommandText = this.sql;
                    SqlDataAdapter adapter = new SqlDataAdapter(cmd);
                    DataSet ds = new DataSet();
                    adapter.Fill(ds);
                    this.db.Close();
                    DataTable ratingsDataTable = ds.Tables["TABLE"];
                    // if no ratings say so
                    if (ratingsDataTable.Rows.Count == 0)
                    {
                        this.msg = "NO RAITINGS";
                        this.listBox3.Items.Add(this.msg);
                    }
                    else
                    {
                        // else display the list
                        foreach (DataRow row in ratingsDataTable.Rows)
                        {
                            msg = string.Format("{0}: {1}", row[0].ToString(), row[1].ToString());
                            listBox3.Items.Add(msg);
                        }
                    }
                    // showing the information
                    this.listBox3.Visible = true;
                }
            }
                // insert flag
            else if (this.previousListbox2 == 5)
            {
                // obtaining selected index
                int index = this.listBox1.SelectedIndex;
                if (index != -1)
                    // error check
                {
                    //making sure a movie has been selected and saving the movieID
                    var content = this.moviesDataTable.Rows;
                    this.movieID = int.Parse(content[index][1].ToString());
                    this.button11.Visible = true;
                    this.textBox1.Visible = true;
                }
            }
        }
        private void listBox3_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
