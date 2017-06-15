using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Diagnostics;

namespace Microsoft.Samples.Kinect.SkeletonBasics
{
    /// <summary>
    /// Logique d'interaction pour Configurations.xaml
    /// </summary>
    public partial class Configurations : Window
    {
        public Configurations()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {

        }

        public void activateCheckBoxes()
        {
            activateSound.Checked += CheckBoxChanged;
            activateSound.Unchecked += CheckBoxChanged;
            activateColour.Checked += CheckBoxChanged;
            activateColour.Unchecked += CheckBoxChanged;
            activateGIF.Checked += CheckBoxChanged;
            activateGIF.Unchecked += CheckBoxChanged;
        }

        public void setAllTrue()
        {
            ((MainWindow)this.Owner).activateSound = true;
            ((MainWindow)this.Owner).activateColour = true;
            ((MainWindow)this.Owner).activateGIF = true;
        }

        private void CheckBoxChanged(object sender, RoutedEventArgs e)
        {
            CheckBox check = (CheckBox)sender;
            switch(check.Name)
            {
                case "activateSound":
                    ((MainWindow)this.Owner).activateSound = check.IsChecked.Value;
                    break;
                case "activateColour":
                    ((MainWindow)this.Owner).activateColour = check.IsChecked.Value;
                    break;
                case "activateGIF":
                    ((MainWindow)this.Owner).activateGIF = check.IsChecked.Value;
                    break;
            }
        }

        private void mediaElementSound_Ended(object sender, RoutedEventArgs e)
        {
            mediaElementSound.Position = TimeSpan.Zero;
            mediaElementSound.Play();
        }

        private void mediaElementGIF_Ended(object sender, EventArgs e)
        {
            double ratio = mediaElementGIF.SpeedRatio;
            mediaElementGIF.Position = TimeSpan.Zero;
            //mediaElementGIF.Play();
            mediaElementGIF.SpeedRatio = ratio;
        }

        public void playAll()
        {
              mediaElementSound.Play();
              mediaElementGIF.Play();
        }

        public void changeRatioSound(double value)
        {   
            if(mediaElementSound.Position == TimeSpan.Zero)
            {
                mediaElementSound.Play();
            }
            mediaElementSound.SpeedRatio = value;
        }

        public void changeRatioGIF(double value)
        {
            if (mediaElementGIF.Position == TimeSpan.Zero)
            {
                mediaElementGIF.Play();
            }
            mediaElementGIF.SpeedRatio = value;
        }
    }
}
