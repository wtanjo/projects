using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace Gomoku;

public class WhitePiece : Image
{
    static WhitePiece()
    {
        DefaultStyleKeyProperty.OverrideMetadata(typeof(WhitePiece), new FrameworkPropertyMetadata(typeof(WhitePiece)));
    }

    public WhitePiece(int X, int Y)
    {
        this.Source = new BitmapImage(new Uri("pack://application:,,,/Pieces/WhitePiece.png"));
        this.Width = 50;
        this.Height = 50;
        Canvas.SetLeft(this, X - 25);
        Canvas.SetTop(this, Y - 25);
    }
}