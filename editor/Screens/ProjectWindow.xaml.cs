using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Editor.Screens
{
    /// <summary>
    /// Interaction logic for ProjectWindow.xaml
    /// </summary>
    public partial class ProjectWindow : Window
    {
        public ProjectWindow()
        {
            InitializeComponent();
        }

        private void CreateNewProjectButton_Click(object sender, RoutedEventArgs e)
        {
            loadingAnimation.Visibility = Visibility.Visible;
            CreateNewProjectWindow newProjectWindow = new CreateNewProjectWindow();
            newProjectWindow.ShowDialog();
            loadingAnimation.Visibility = Visibility.Hidden;
        }
    }
}
