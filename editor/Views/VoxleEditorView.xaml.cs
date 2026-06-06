using System.Windows;
using System.Windows.Input;

namespace Editor.Views
{
    public partial class VoxleEditorView : Window
    {
        public VoxleEditorView()
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

    }
}
