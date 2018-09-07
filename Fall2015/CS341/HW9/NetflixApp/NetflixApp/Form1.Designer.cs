namespace NetflixApp
{
	partial class Form1
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
      this.listBox1 = new System.Windows.Forms.ListBox();
      this.cmdInsertReview = new System.Windows.Forms.Button();
      this.lblRating = new System.Windows.Forms.Label();
      this.tbarRating = new System.Windows.Forms.TrackBar();
      this.cmdAllMovies = new System.Windows.Forms.Button();
      this.txtTopN = new System.Windows.Forms.TextBox();
      this.menuStrip1 = new System.Windows.Forms.MenuStrip();
      this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.testConnectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
      this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.topToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.topMoviesByRatingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.topMoviesByNumReviewsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.topUsersByNumReviewsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.txtMovieID = new System.Windows.Forms.TextBox();
      this.txtAvgRating = new System.Windows.Forms.TextBox();
      this.cmdAllUsers = new System.Windows.Forms.Button();
      this.listBox2 = new System.Windows.Forms.ListBox();
      this.label3 = new System.Windows.Forms.Label();
      this.txtOccupation = new System.Windows.Forms.TextBox();
      this.txtUserID = new System.Windows.Forms.TextBox();
      this.label4 = new System.Windows.Forms.Label();
      this.label5 = new System.Windows.Forms.Label();
      this.cmdMovieReviews = new System.Windows.Forms.Button();
      this.cmdUserReviews = new System.Windows.Forms.Button();
      this.cmdReviewsSummary = new System.Windows.Forms.Button();
      ((System.ComponentModel.ISupportInitialize)(this.tbarRating)).BeginInit();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // listBox1
      // 
      this.listBox1.FormattingEnabled = true;
      this.listBox1.ItemHeight = 24;
      this.listBox1.Location = new System.Drawing.Point(12, 106);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new System.Drawing.Size(380, 364);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
      // 
      // cmdInsertReview
      // 
      this.cmdInsertReview.BackColor = System.Drawing.Color.Aqua;
      this.cmdInsertReview.Location = new System.Drawing.Point(430, 333);
      this.cmdInsertReview.Name = "cmdInsertReview";
      this.cmdInsertReview.Size = new System.Drawing.Size(95, 66);
      this.cmdInsertReview.TabIndex = 11;
      this.cmdInsertReview.Text = "Insert Review";
      this.cmdInsertReview.UseVisualStyleBackColor = false;
      this.cmdInsertReview.Click += new System.EventHandler(this.cmdInsertReview_Click);
      // 
      // lblRating
      // 
      this.lblRating.AutoSize = true;
      this.lblRating.Location = new System.Drawing.Point(465, 297);
      this.lblRating.Name = "lblRating";
      this.lblRating.Size = new System.Drawing.Size(20, 24);
      this.lblRating.TabIndex = 13;
      this.lblRating.Text = "3";
      // 
      // tbarRating
      // 
      this.tbarRating.BackColor = System.Drawing.Color.White;
      this.tbarRating.LargeChange = 1;
      this.tbarRating.Location = new System.Drawing.Point(407, 246);
      this.tbarRating.Maximum = 5;
      this.tbarRating.Minimum = 1;
      this.tbarRating.Name = "tbarRating";
      this.tbarRating.Size = new System.Drawing.Size(134, 45);
      this.tbarRating.TabIndex = 12;
      this.tbarRating.Value = 3;
      this.tbarRating.Scroll += new System.EventHandler(this.tbarRating_Scroll);
      // 
      // cmdAllMovies
      // 
      this.cmdAllMovies.Location = new System.Drawing.Point(12, 42);
      this.cmdAllMovies.Name = "cmdAllMovies";
      this.cmdAllMovies.Size = new System.Drawing.Size(380, 40);
      this.cmdAllMovies.TabIndex = 16;
      this.cmdAllMovies.Text = "All Movies";
      this.cmdAllMovies.UseVisualStyleBackColor = true;
      this.cmdAllMovies.Click += new System.EventHandler(this.cmdAllMovies_Click);
      // 
      // txtTopN
      // 
      this.txtTopN.Location = new System.Drawing.Point(444, 156);
      this.txtTopN.Name = "txtTopN";
      this.txtTopN.Size = new System.Drawing.Size(63, 29);
      this.txtTopN.TabIndex = 5;
      this.txtTopN.Text = "10";
      this.txtTopN.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
      // 
      // menuStrip1
      // 
      this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.topToolStripMenuItem});
      this.menuStrip1.Location = new System.Drawing.Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new System.Drawing.Size(956, 24);
      this.menuStrip1.TabIndex = 17;
      this.menuStrip1.Text = "menuStrip1";
      // 
      // fileToolStripMenuItem
      // 
      this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.testConnectionToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem});
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      // 
      // testConnectionToolStripMenuItem
      // 
      this.testConnectionToolStripMenuItem.Name = "testConnectionToolStripMenuItem";
      this.testConnectionToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
      this.testConnectionToolStripMenuItem.Text = "Test Connection";
      this.testConnectionToolStripMenuItem.Click += new System.EventHandler(this.testConnectionToolStripMenuItem_Click);
      // 
      // toolStripMenuItem1
      // 
      this.toolStripMenuItem1.Name = "toolStripMenuItem1";
      this.toolStripMenuItem1.Size = new System.Drawing.Size(157, 6);
      // 
      // exitToolStripMenuItem
      // 
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
      this.exitToolStripMenuItem.Text = "Exit";
      this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
      // 
      // topToolStripMenuItem
      // 
      this.topToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.topMoviesByRatingToolStripMenuItem,
            this.topMoviesByNumReviewsToolStripMenuItem,
            this.topUsersByNumReviewsToolStripMenuItem});
      this.topToolStripMenuItem.Name = "topToolStripMenuItem";
      this.topToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
      this.topToolStripMenuItem.Text = "Top";
      // 
      // topMoviesByRatingToolStripMenuItem
      // 
      this.topMoviesByRatingToolStripMenuItem.Name = "topMoviesByRatingToolStripMenuItem";
      this.topMoviesByRatingToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
      this.topMoviesByRatingToolStripMenuItem.Text = "Top Movies by Avg Rating";
      this.topMoviesByRatingToolStripMenuItem.Click += new System.EventHandler(this.topMoviesByRatingToolStripMenuItem_Click);
      // 
      // topMoviesByNumReviewsToolStripMenuItem
      // 
      this.topMoviesByNumReviewsToolStripMenuItem.Name = "topMoviesByNumReviewsToolStripMenuItem";
      this.topMoviesByNumReviewsToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
      this.topMoviesByNumReviewsToolStripMenuItem.Text = "Top Movies by Num Reviews";
      this.topMoviesByNumReviewsToolStripMenuItem.Click += new System.EventHandler(this.topMoviesByNumReviewsToolStripMenuItem_Click);
      // 
      // topUsersByNumReviewsToolStripMenuItem
      // 
      this.topUsersByNumReviewsToolStripMenuItem.Name = "topUsersByNumReviewsToolStripMenuItem";
      this.topUsersByNumReviewsToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
      this.topUsersByNumReviewsToolStripMenuItem.Text = "Top Users by Num Reviews";
      this.topUsersByNumReviewsToolStripMenuItem.Click += new System.EventHandler(this.topUsersByNumReviewsToolStripMenuItem_Click);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(12, 485);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(88, 24);
      this.label1.TabIndex = 18;
      this.label1.Text = "Movie ID:";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(12, 519);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(106, 24);
      this.label2.TabIndex = 19;
      this.label2.Text = "Avg Rating:";
      // 
      // txtMovieID
      // 
      this.txtMovieID.Location = new System.Drawing.Point(127, 480);
      this.txtMovieID.Name = "txtMovieID";
      this.txtMovieID.ReadOnly = true;
      this.txtMovieID.Size = new System.Drawing.Size(81, 29);
      this.txtMovieID.TabIndex = 20;
      // 
      // txtAvgRating
      // 
      this.txtAvgRating.Location = new System.Drawing.Point(127, 516);
      this.txtAvgRating.Name = "txtAvgRating";
      this.txtAvgRating.ReadOnly = true;
      this.txtAvgRating.Size = new System.Drawing.Size(81, 29);
      this.txtAvgRating.TabIndex = 21;
      // 
      // cmdAllUsers
      // 
      this.cmdAllUsers.Location = new System.Drawing.Point(560, 42);
      this.cmdAllUsers.Name = "cmdAllUsers";
      this.cmdAllUsers.Size = new System.Drawing.Size(380, 40);
      this.cmdAllUsers.TabIndex = 22;
      this.cmdAllUsers.Text = "All Users";
      this.cmdAllUsers.UseVisualStyleBackColor = true;
      this.cmdAllUsers.Click += new System.EventHandler(this.cmdAllUsers_Click);
      // 
      // listBox2
      // 
      this.listBox2.FormattingEnabled = true;
      this.listBox2.ItemHeight = 24;
      this.listBox2.Location = new System.Drawing.Point(560, 106);
      this.listBox2.Name = "listBox2";
      this.listBox2.Size = new System.Drawing.Size(380, 364);
      this.listBox2.TabIndex = 23;
      this.listBox2.SelectedIndexChanged += new System.EventHandler(this.listBox2_SelectedIndexChanged);
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(440, 129);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(68, 24);
      this.label3.TabIndex = 24;
      this.label3.Text = "Top N:";
      // 
      // txtOccupation
      // 
      this.txtOccupation.Location = new System.Drawing.Point(686, 516);
      this.txtOccupation.Name = "txtOccupation";
      this.txtOccupation.ReadOnly = true;
      this.txtOccupation.Size = new System.Drawing.Size(137, 29);
      this.txtOccupation.TabIndex = 28;
      // 
      // txtUserID
      // 
      this.txtUserID.Location = new System.Drawing.Point(686, 480);
      this.txtUserID.Name = "txtUserID";
      this.txtUserID.ReadOnly = true;
      this.txtUserID.Size = new System.Drawing.Size(137, 29);
      this.txtUserID.TabIndex = 27;
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(563, 519);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(112, 24);
      this.label4.TabIndex = 26;
      this.label4.Text = "Occupation:";
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(563, 485);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(76, 24);
      this.label5.TabIndex = 25;
      this.label5.Text = "User ID:";
      // 
      // cmdMovieReviews
      // 
      this.cmdMovieReviews.BackColor = System.Drawing.Color.Aqua;
      this.cmdMovieReviews.Location = new System.Drawing.Point(223, 480);
      this.cmdMovieReviews.Name = "cmdMovieReviews";
      this.cmdMovieReviews.Size = new System.Drawing.Size(96, 65);
      this.cmdMovieReviews.TabIndex = 29;
      this.cmdMovieReviews.Text = "Reviews";
      this.cmdMovieReviews.UseVisualStyleBackColor = false;
      this.cmdMovieReviews.Click += new System.EventHandler(this.cmdMovieReviews_Click);
      // 
      // cmdUserReviews
      // 
      this.cmdUserReviews.BackColor = System.Drawing.Color.Aqua;
      this.cmdUserReviews.Location = new System.Drawing.Point(844, 480);
      this.cmdUserReviews.Name = "cmdUserReviews";
      this.cmdUserReviews.Size = new System.Drawing.Size(96, 65);
      this.cmdUserReviews.TabIndex = 30;
      this.cmdUserReviews.Text = "Reviews";
      this.cmdUserReviews.UseVisualStyleBackColor = false;
      this.cmdUserReviews.Click += new System.EventHandler(this.cmdUserReviews_Click);
      // 
      // cmdReviewsSummary
      // 
      this.cmdReviewsSummary.BackColor = System.Drawing.Color.Aqua;
      this.cmdReviewsSummary.Location = new System.Drawing.Point(325, 480);
      this.cmdReviewsSummary.Name = "cmdReviewsSummary";
      this.cmdReviewsSummary.Size = new System.Drawing.Size(67, 65);
      this.cmdReviewsSummary.TabIndex = 31;
      this.cmdReviewsSummary.Text = "Each";
      this.cmdReviewsSummary.UseVisualStyleBackColor = false;
      this.cmdReviewsSummary.Click += new System.EventHandler(this.cmdReviewsSummary_Click);
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.PaleGoldenrod;
      this.ClientSize = new System.Drawing.Size(956, 561);
      this.Controls.Add(this.cmdReviewsSummary);
      this.Controls.Add(this.cmdUserReviews);
      this.Controls.Add(this.cmdMovieReviews);
      this.Controls.Add(this.txtOccupation);
      this.Controls.Add(this.txtUserID);
      this.Controls.Add(this.label4);
      this.Controls.Add(this.label5);
      this.Controls.Add(this.label3);
      this.Controls.Add(this.cmdInsertReview);
      this.Controls.Add(this.lblRating);
      this.Controls.Add(this.listBox2);
      this.Controls.Add(this.tbarRating);
      this.Controls.Add(this.cmdAllUsers);
      this.Controls.Add(this.txtTopN);
      this.Controls.Add(this.txtAvgRating);
      this.Controls.Add(this.txtMovieID);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.cmdAllMovies);
      this.Controls.Add(this.listBox1);
      this.Controls.Add(this.menuStrip1);
      this.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.MainMenuStrip = this.menuStrip1;
      this.Margin = new System.Windows.Forms.Padding(6);
      this.Name = "Form1";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
      this.Text = "Database App";
      this.Load += new System.EventHandler(this.Form1_Load);
      ((System.ComponentModel.ISupportInitialize)(this.tbarRating)).EndInit();
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

		}

		#endregion

    private System.Windows.Forms.ListBox listBox1;
    private System.Windows.Forms.Button cmdInsertReview;
		private System.Windows.Forms.TrackBar tbarRating;
    private System.Windows.Forms.Label lblRating;
    private System.Windows.Forms.TextBox txtTopN;
    private System.Windows.Forms.Button cmdAllMovies;
    private System.Windows.Forms.MenuStrip menuStrip1;
    private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem testConnectionToolStripMenuItem;
    private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
    private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.TextBox txtMovieID;
    private System.Windows.Forms.TextBox txtAvgRating;
    private System.Windows.Forms.ToolStripMenuItem topToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem topMoviesByRatingToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem topMoviesByNumReviewsToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem topUsersByNumReviewsToolStripMenuItem;
    private System.Windows.Forms.Button cmdAllUsers;
    private System.Windows.Forms.ListBox listBox2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.TextBox txtOccupation;
    private System.Windows.Forms.TextBox txtUserID;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.Button cmdMovieReviews;
    private System.Windows.Forms.Button cmdUserReviews;
    private System.Windows.Forms.Button cmdReviewsSummary;
	}
}

