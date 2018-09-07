//
// GUI-based Asian Options Stock Pricing program.
//
// Maxwell Petersen
// U. of Illinois, Chicago
// CS341, Fall 2015
// Homework 7
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

namespace HW7
{
    public partial class AOSP : Form
    {
        private double initialPrice;
        private double exercisePrice;
        private double upperBound;
        private double lowerbound;
        private double intrestRate;
        private int timePeriod;
        private long simulationRuns;

        public AOSP()
        {
            InitializeComponent();
            initialPrice = 30.00;
            exercisePrice = 30.0;
            upperBound = 1.40;
            lowerbound = 0.80;
            intrestRate = 1.08;
            timePeriod = 30;
            simulationRuns = 10000000;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            this.initialPrice = Double.Parse(this.InitialPriceValue.Text);
        }

        private void textBox7_TextChanged(object sender, EventArgs e)
        {
            this.simulationRuns = int.Parse(this.SimulationRunsValue.Text);
        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {
            this.timePeriod = int.Parse(this.TimePeriodValue.Text);
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            this.intrestRate = Double.Parse(this.IntrestRateValue.Text);
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            this.lowerbound = Double.Parse(this.LowerBoundValue.Text);
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            this.upperBound = Double.Parse(this.UpperBoundValue.Text);
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            this.exercisePrice = Double.Parse(this.ExercisePriceValue.Text);
        }

        private void RunSims_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;

            int start = System.Environment.TickCount;

            double price = AsianOptionsLib.Pricing.Simulation(this.initialPrice, this.exercisePrice, this.upperBound, this.lowerbound, this.intrestRate, this.timePeriod, this.simulationRuns);
            price = Math.Truncate(price * 100) / 100;

            int stop = System.Environment.TickCount;
            double elapsedTimeInSecs = (stop - start) / 1000.0;

            this.Cursor = Cursors.Default;

            MessageBox.Show("** Simulation complete:\n   Price: $" + price + "\n   Time:   " + elapsedTimeInSecs + " secs\n");
        }
    }
}
