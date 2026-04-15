using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;
using System.Windows.Media.Media3D;

namespace Editor.Resources.Controls
{
    public partial class SpinnerControl : UserControl
    {
        public static readonly DependencyProperty SizeProperty =
            DependencyProperty.Register(nameof(Size), typeof(double), typeof(SpinnerControl), new PropertyMetadata(32.0));

        public double Size
        {
            get => (double)GetValue(SizeProperty);
            set => SetValue(SizeProperty, value);
        }

        public SpinnerControl()
        {
            InitializeComponent();
            Loaded += OnLoaded;
        }

        private void OnLoaded(object sender, RoutedEventArgs e)
        {
            var anim = new DoubleAnimation(0, 360, new Duration(TimeSpan.FromSeconds(2)))
            {
                RepeatBehavior = RepeatBehavior.Forever,
                EasingFunction = null
            };
            CubeYRot.BeginAnimation(AxisAngleRotation3D.AngleProperty, anim);
        }
    }
}
