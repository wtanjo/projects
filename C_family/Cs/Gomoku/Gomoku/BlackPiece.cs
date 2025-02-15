using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace Gomoku;

public class BlackPiece : Image
{
    static BlackPiece()
    {
        DefaultStyleKeyProperty.OverrideMetadata(typeof(BlackPiece), new FrameworkPropertyMetadata(typeof(BlackPiece)));
    }
    
    public BlackPiece(int X, int Y)
    {
        this.Source = new BitmapImage(new Uri("pack://application:,,,/Pieces/BlackPiece.png"));
        this.Width = 50;
        this.Height = 50;
        Canvas.SetLeft(this, X - 25);
        Canvas.SetTop(this, Y - 25);
    }
}