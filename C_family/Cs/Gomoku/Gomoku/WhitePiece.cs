using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace Gomoku;

public class WhitePiece : Image
{
    public readonly int RP = 50;//Radius of Piece

    static WhitePiece()
    {
        DefaultStyleKeyProperty.OverrideMetadata(typeof(WhitePiece), new FrameworkPropertyMetadata(typeof(WhitePiece)));
    }

    public WhitePiece(int X, int Y)
    {
        this.Source = new BitmapImage(new Uri("pack://application:,,,/Pieces/WhitePiece.png"));
        this.Width = RP;
        this.Height = RP;
        Canvas.SetLeft(this, X - RP / 2);
        Canvas.SetTop(this, Y - RP / 2);
    }
}
