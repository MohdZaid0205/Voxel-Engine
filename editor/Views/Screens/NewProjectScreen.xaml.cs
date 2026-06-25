using Editor.ViewModels;
using Microsoft.Win32;
using System.Windows;
using System.Windows.Input;

namespace Editor.Views.Screens
{
    public partial class NewProjectScreen : Window
    {
        public NewProjectScreen()
        {
            InitializeComponent();
        }

        private void Body_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                this.DragMove();
            }
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void BrowseFile_Click(object sender, RoutedEventArgs e)
        {
            OpenFolderDialog dialog = new OpenFolderDialog();
            dialog.Title = "Select Project Location";
            if (dialog.ShowDialog() == true)
            {
                if (this.DataContext is CreateProjectViewModel viewModle)
                {
                    if (viewModle.Name != null)
                    {
                        viewModle.Path = System.IO.Path.Combine(dialog.FolderName, viewModle.Name);
                    }
                }
            }
        }
    }
}
