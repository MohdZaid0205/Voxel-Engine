using System;
using System.Configuration;
using System.Data;
using System.Windows;

namespace editor
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        [STAThread]
        public static void Main()
        {
            App app = new();
            app.InitializeComponent();
            app.Run();
        }
    }

}
