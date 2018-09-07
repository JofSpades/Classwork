using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.FSharp.Collections;
using Microsoft.VisualBasic;

namespace PPMImageEditor
{
  public partial class Form1 : Form
  {
    //
    // Current image being displayed:
    //
    private PixelMap CurrentImage;

    public Form1()
    {
      InitializeComponent();
    }

    // 
    // Initialize window just before it appears:
    //
    private void Form1_Load(object sender, EventArgs e)
    {
      this.radioFitImage.Checked = true;
    }

    // 
    // Exit:
    private void cmdExit_Click(object sender, EventArgs e)
    {
      this.Close();
    }

    
    //
    // Open:
    //
    private void cmdOpen_Click(object sender, EventArgs e)
    {
      openFileDialog1.Filter = "PPM Files (*.ppm)|*.ppm|All files (*.*)|*.*";
      openFileDialog1.FileName = "";
      openFileDialog1.CheckFileExists = true;
      openFileDialog1.InitialDirectory = System.Environment.CurrentDirectory;

      DialogResult dr = openFileDialog1.ShowDialog();

      if (dr == System.Windows.Forms.DialogResult.OK)
      {
        string filepath = openFileDialog1.FileName;

        CurrentImage = new PixelMap(filepath);
        picImage.Image = CurrentImage.BitMap;

        // enable the other buttons so user can manipulate image:
        cmdFS1.Enabled = true;
        cmdSaveAs.Enabled = true;
        button2.Enabled = true;
        button3.Enabled = true;
        button4.Enabled = true;
        button5.Enabled = true;
        button6.Enabled = true;
      }
      else
      {
        MessageBox.Show("Open was canceled...");
      }
    }//cmdOpen


    //
    // Test F#:
    //
    private void cmdFS1_Click(object sender, EventArgs e)
    {
      if (CurrentImage == null)  // sanity check: make sure we have an image to manipulate
        return;

      //
      // Example of calling library, which then dumps data about the given image
      // to Visual Studio's "Output" window.  Note you must run with debugging (F5)
      // in order to see the output.
      //
      //PPMImageLibrary.DebugOutput(
      //  CurrentImage.Header.Width,
      //  CurrentImage.Header.Height, 
      //  CurrentImage.Header.Depth,
      //  CurrentImage.ImageListData
      //);

      //
      // we have an image, perform transformation and display new result:
      //
      FSharpList<FSharpList<int>> newImageList;

      newImageList = PPMImageLibrary.FirstRowWhite(
        CurrentImage.Header.Width,
        CurrentImage.Header.Height,
        CurrentImage.Header.Depth,
        CurrentImage.ImageListData
      );

      //
      // create a new PixelMap here on the client-side, which creates a new bitmap
      // we then display to the user:
      //
      CurrentImage = new PixelMap(newImageList);
      picImage.Image = CurrentImage.BitMap;
    }//cmdFS1


    //
    // Save as:
    //
    private void cmdSaveAs_Click(object sender, EventArgs e)
    {
      if (CurrentImage == null)  // sanity check: make sure we have an image to save
        return;

      saveFileDialog1.Filter = "PPM Files (*.ppm)|*.ppm";
      saveFileDialog1.DefaultExt = "ppm";
      saveFileDialog1.FileName = "";
      saveFileDialog1.InitialDirectory = System.Environment.CurrentDirectory;

      DialogResult dr = saveFileDialog1.ShowDialog();

      if (dr == System.Windows.Forms.DialogResult.OK)
      {
        string filepath = saveFileDialog1.FileName;

        bool written = PPMImageLibrary.WriteP3Image(
          filepath,
          CurrentImage.Header.Width,
          CurrentImage.Header.Height,
          CurrentImage.Header.Depth,
          CurrentImage.ImageListData
        );

        if (!written)
          MessageBox.Show("Write failed?!");
      }
      else
      {
        MessageBox.Show("Save As was canceled...");
      }
    }//cmdSaveAs


    private void button1_Click(object sender, EventArgs e)
    {
      if (CurrentImage == null)  // sanity check: make sure we have an image to manipulate
        return;

      //
      // Example of calling library, which then dumps data about the given image
      // to Visual Studio's "Output" window.  Note you must run with debugging (F5)
      // in order to see the output.
      //
      // PPMImageLibrary.DebugOutput(
      //   CurrentImage.Header.Width,
      //   CurrentImage.Header.Height, 
      //   CurrentImage.Header.Depth,
      //   CurrentImage.ImageListData
      // );

      //
      // Perform transformation:
      //
      string fileLocation = Interaction.InputBox("Please provide a file name for the outputfile.", "Enter Filename", "p3.txt", -1, -1);
      if(PPMImageLibrary.WriteP3Image (
        fileLocation,
        CurrentImage.Header.Width,
        CurrentImage.Header.Height, 
        CurrentImage.Header.Depth,
        CurrentImage.ImageListData
      )){
          MessageBox.Show("Printed 'P3' data to file p3.txt");
      }
      else
      {
          MessageBox.Show("Data print failed");
      }

      //
      // create a new PixelMap here on the client-side, which creates a new bitmap
      // we then display to the user:
      //
      //CurrentImage = new PixelMap(newImageList);
      //picImage.Image = CurrentImage.BitMap;
    }


    private void button2_Click(object sender, EventArgs e)
    {
      if (CurrentImage == null)  // sanity check: make sure we have an image to manipulate
        return;

      //
      // Example of calling library, which then dumps data about the given image
      // to Visual Studio's "Output" window.  Note you must run with debugging (F5)
      // in order to see the output.
      //
      //PPMImageLibrary.DebugOutput(
      //  CurrentImage.Header.Width,
      //  CurrentImage.Header.Height, 
      //  CurrentImage.Header.Depth,
      //  CurrentImage.ImageListData
      //);

      //
      // Perform transformation:
      //
      FSharpList<FSharpList<int>> newImageList;
      
      newImageList = PPMImageLibrary.Grayscale (
        CurrentImage.Header.Width,
        CurrentImage.Header.Height, 
        CurrentImage.Header.Depth,
        CurrentImage.ImageListData
      );

      //
      // create a new PixelMap here on the client-side, which creates a new bitmap
      // we then display to the user:
      //
      CurrentImage = new PixelMap(newImageList);
      picImage.Image = CurrentImage.BitMap;
    }


    private void button3_Click(object sender, EventArgs e)
    {
      if (CurrentImage == null)  // sanity check: make sure we have an image to manipulate
        return;

      //
      // Example of calling library, which then dumps data about the given image
      // to Visual Studio's "Output" window.  Note you must run with debugging (F5)
      // in order to see the output.
      //
      //PPMImageLibrary.DebugOutput(
      //  CurrentImage.Header.Width,
      //  CurrentImage.Header.Height, 
      //  CurrentImage.Header.Depth,
      //  CurrentImage.ImageListData
      //);

      //
      // Perform transformation:
      //
      FSharpList<FSharpList<int>> newImageList;

      int thresholdValue = int.Parse(Interaction.InputBox("Please provide the threashold value you want to use.", "Threshold value", "127", -1, -1));
      
      newImageList = PPMImageLibrary.Threshold(
        CurrentImage.Header.Width,
        CurrentImage.Header.Height, 
        CurrentImage.Header.Depth,
        CurrentImage.ImageListData,
        thresholdValue
      );

      //
      // create a new PixelMap here on the client-side, which creates a new bitmap
      // we then display to the user:
      //
      CurrentImage = new PixelMap(newImageList);
      picImage.Image = CurrentImage.BitMap;
    }


    private void button4_Click(object sender, EventArgs e)
    {
      if (CurrentImage == null)  // sanity check: make sure we have an image to manipulate
        return;

      //
      // Example of calling library, which then dumps data about the given image
      // to Visual Studio's "Output" window.  Note you must run with debugging (F5)
      // in order to see the output.
      //
      //PPMImageLibrary.DebugOutput(
      //  CurrentImage.Header.Width,
      //  CurrentImage.Header.Height, 
      //  CurrentImage.Header.Depth,
      //  CurrentImage.ImageListData
      //);

      //
      // Perform transformation:
      //
      FSharpList<FSharpList<int>> newImageList;
      
      newImageList = PPMImageLibrary.FlipHorizontal(
        CurrentImage.Header.Width,
        CurrentImage.Header.Height, 
        CurrentImage.Header.Depth,
        CurrentImage.ImageListData
      );

      //
      // create a new PixelMap here on the client-side, which creates a new bitmap
      // we then display to the user:
      //
      CurrentImage = new PixelMap(newImageList);
      picImage.Image = CurrentImage.BitMap;
    }


    private void button5_Click(object sender, EventArgs e)
    {
      if (CurrentImage == null)  // sanity check: make sure we have an image to manipulate
        return;

      //
      // Example of calling library, which then dumps data about the given image
      // to Visual Studio's "Output" window.  Note you must run with debugging (F5)
      // in order to see the output.
      //
      //PPMImageLibrary.DebugOutput(
      //  CurrentImage.Header.Width,
      //  CurrentImage.Header.Height, 
      //  CurrentImage.Header.Depth,
      //  CurrentImage.ImageListData
      //);

      //
      // Perform transformation:
      //
      FSharpList<FSharpList<int>> newImageList;
      int zoomFactor = int.Parse(Interaction.InputBox("Please provide the zoom factor you want to use.", "Zoom factor", "2", -1, -1));
      if (zoomFactor > 4)
      {
          MessageBox.Show("Too large a value try again.");
      }
      else if (zoomFactor < 1)
      {
          MessageBox.Show("Too small a value try again.");
      }
      else
      {
          newImageList = PPMImageLibrary.Zoom(
            CurrentImage.Header.Width,
            CurrentImage.Header.Height,
            CurrentImage.Header.Depth,
            CurrentImage.ImageListData,
            zoomFactor
          );
          //
          // create a new PixelMap here on the client-side, which creates a new bitmap
          // we then display to the user:
          //
          CurrentImage = new PixelMap(newImageList);
          picImage.Image = CurrentImage.BitMap;
      }
    }
    private void button6_Click(object sender, EventArgs e)
    {
        if (CurrentImage == null)  // sanity check: make sure we have an image to manipulate
            return;

        //
        // Example of calling library, which then dumps data about the given image
        // to Visual Studio's "Output" window.  Note you must run with debugging (F5)
        // in order to see the output.
        //
        //PPMImageLibrary.DebugOutput(
        //  CurrentImage.Header.Width,
        //  CurrentImage.Header.Height, 
        //  CurrentImage.Header.Depth,
        //  CurrentImage.ImageListData
        //);

        //
        // Perform transformation:
        //
        FSharpList<FSharpList<int>> newImageList;
        
        newImageList = PPMImageLibrary.RotateRight90 (
          CurrentImage.Header.Width,
          CurrentImage.Header.Height, 
          CurrentImage.Header.Depth,
          CurrentImage.ImageListData
        );

        //
        // create a new PixelMap here on the client-side, which creates a new bitmap
        // we then display to the user:
        //
        CurrentImage = new PixelMap(newImageList);
        picImage.Image = CurrentImage.BitMap;
    }

    private void radioFitImage_CheckedChanged(object sender, EventArgs e)
    {
      if (this.radioFitImage.Checked)
      {
        this.picImage.SizeMode = PictureBoxSizeMode.Zoom;
      }
    }

    private void radioActualSizeImage_CheckedChanged(object sender, EventArgs e)
    {
      if (this.radioActualSizeImage.Checked)
      {
        this.picImage.SizeMode = PictureBoxSizeMode.CenterImage;
      }
    }

  }//class
}//namespace
