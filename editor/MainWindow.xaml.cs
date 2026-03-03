using System;
using System.Windows;
using System.Windows.Media;

namespace editor
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            CompositionTarget.Rendering += OnRenderTick;
        }

        private void OnRenderTick(object sender, EventArgs e)
        {
            EngineHost.OnUpdate();
        }
    }
}