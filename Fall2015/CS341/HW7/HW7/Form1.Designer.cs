namespace HW7
{
    partial class AOSP
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.InitialPriceValue = new System.Windows.Forms.TextBox();
            this.ExercisePriceValue = new System.Windows.Forms.TextBox();
            this.UpperBoundValue = new System.Windows.Forms.TextBox();
            this.LowerBoundValue = new System.Windows.Forms.TextBox();
            this.IntrestRateValue = new System.Windows.Forms.TextBox();
            this.TimePeriodValue = new System.Windows.Forms.TextBox();
            this.SimulationRunsValue = new System.Windows.Forms.TextBox();
            this.RunSims = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Initial price:";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 44);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Exercise price:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 85);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(72, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Upper bound:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 229);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(81, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Simulation runs:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 191);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 13);
            this.label5.TabIndex = 4;
            this.label5.Text = "Time period:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 156);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(60, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "Intrest rate:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 120);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(72, 13);
            this.label7.TabIndex = 6;
            this.label7.Text = "Lower bound:";
            // 
            // InitialPriceValue
            // 
            this.InitialPriceValue.Location = new System.Drawing.Point(130, 6);
            this.InitialPriceValue.Name = "InitialPriceValue";
            this.InitialPriceValue.Size = new System.Drawing.Size(100, 20);
            this.InitialPriceValue.TabIndex = 7;
            this.InitialPriceValue.Text = "30.00";
            this.InitialPriceValue.WordWrap = false;
            this.InitialPriceValue.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // ExercisePriceValue
            // 
            this.ExercisePriceValue.Location = new System.Drawing.Point(130, 41);
            this.ExercisePriceValue.Name = "ExercisePriceValue";
            this.ExercisePriceValue.Size = new System.Drawing.Size(100, 20);
            this.ExercisePriceValue.TabIndex = 8;
            this.ExercisePriceValue.Text = "30.00";
            this.ExercisePriceValue.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // UpperBoundValue
            // 
            this.UpperBoundValue.Location = new System.Drawing.Point(130, 82);
            this.UpperBoundValue.Name = "UpperBoundValue";
            this.UpperBoundValue.Size = new System.Drawing.Size(100, 20);
            this.UpperBoundValue.TabIndex = 9;
            this.UpperBoundValue.Text = "1.40";
            this.UpperBoundValue.TextChanged += new System.EventHandler(this.textBox3_TextChanged);
            // 
            // LowerBoundValue
            // 
            this.LowerBoundValue.Location = new System.Drawing.Point(130, 117);
            this.LowerBoundValue.Name = "LowerBoundValue";
            this.LowerBoundValue.Size = new System.Drawing.Size(100, 20);
            this.LowerBoundValue.TabIndex = 10;
            this.LowerBoundValue.Text = "0.80";
            this.LowerBoundValue.TextChanged += new System.EventHandler(this.textBox4_TextChanged);
            // 
            // IntrestRateValue
            // 
            this.IntrestRateValue.Location = new System.Drawing.Point(130, 153);
            this.IntrestRateValue.Name = "IntrestRateValue";
            this.IntrestRateValue.Size = new System.Drawing.Size(100, 20);
            this.IntrestRateValue.TabIndex = 11;
            this.IntrestRateValue.Text = "1.08";
            this.IntrestRateValue.TextChanged += new System.EventHandler(this.textBox5_TextChanged);
            // 
            // TimePeriodValue
            // 
            this.TimePeriodValue.Location = new System.Drawing.Point(130, 188);
            this.TimePeriodValue.Name = "TimePeriodValue";
            this.TimePeriodValue.Size = new System.Drawing.Size(100, 20);
            this.TimePeriodValue.TabIndex = 12;
            this.TimePeriodValue.Text = "30";
            this.TimePeriodValue.TextChanged += new System.EventHandler(this.textBox6_TextChanged);
            // 
            // SimulationRunsValue
            // 
            this.SimulationRunsValue.Location = new System.Drawing.Point(130, 226);
            this.SimulationRunsValue.Name = "SimulationRunsValue";
            this.SimulationRunsValue.Size = new System.Drawing.Size(100, 20);
            this.SimulationRunsValue.TabIndex = 13;
            this.SimulationRunsValue.Text = "10000000";
            this.SimulationRunsValue.TextChanged += new System.EventHandler(this.textBox7_TextChanged);
            // 
            // RunSims
            // 
            this.RunSims.Location = new System.Drawing.Point(15, 269);
            this.RunSims.Name = "RunSims";
            this.RunSims.Size = new System.Drawing.Size(75, 23);
            this.RunSims.TabIndex = 14;
            this.RunSims.Text = "Run";
            this.RunSims.UseVisualStyleBackColor = true;
            this.RunSims.Click += new System.EventHandler(this.RunSims_Click);
            // 
            // AOSP
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(388, 503);
            this.Controls.Add(this.RunSims);
            this.Controls.Add(this.SimulationRunsValue);
            this.Controls.Add(this.TimePeriodValue);
            this.Controls.Add(this.IntrestRateValue);
            this.Controls.Add(this.LowerBoundValue);
            this.Controls.Add(this.UpperBoundValue);
            this.Controls.Add(this.ExercisePriceValue);
            this.Controls.Add(this.InitialPriceValue);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "AOSP";
            this.Text = "Asian Option Stock Pricing";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox InitialPriceValue;
        private System.Windows.Forms.TextBox ExercisePriceValue;
        private System.Windows.Forms.TextBox UpperBoundValue;
        private System.Windows.Forms.TextBox LowerBoundValue;
        private System.Windows.Forms.TextBox IntrestRateValue;
        private System.Windows.Forms.TextBox TimePeriodValue;
        private System.Windows.Forms.TextBox SimulationRunsValue;
        private System.Windows.Forms.Button RunSims;
    }
}

