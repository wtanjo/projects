using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;

namespace Gomoku;
/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();

        
    }

    private void Mouse_Down(object sender, MouseButtonEventArgs e)
    {
        canvas.Children.Add(new BlackPiece((int)e.GetPosition(canvas).X, (int)e.GetPosition(canvas).Y));
    }
}