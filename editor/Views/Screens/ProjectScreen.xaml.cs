using System;
using System.Windows;
using System.Windows.Input;
using Editor.ViewModels;

namespace Editor.Views.Screens
{
    public partial class ProjectScreen : Window
    {
        public ProjectScreen()
        {
            InitializeComponent();
        }

        private void CreateNewProject_Click(object sender, RoutedEventArgs e)
        {
            project_screen_topleft_spinner.Visibility = Visibility.Visible;
            project_screen_topleft_static.Visibility = Visibility.Hidden;
            NewProjectScreen newProjectScreen = new NewProjectScreen();
            newProjectScreen.ShowDialog();
            project_screen_topleft_spinner.Visibility = Visibility.Hidden;
            project_screen_topleft_static.Visibility = Visibility.Visible;
        }

        private void TitleBar_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
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

        private void MinimizeButton_Click(Object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }

