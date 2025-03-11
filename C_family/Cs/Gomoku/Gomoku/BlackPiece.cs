using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace Gomoku;

public class BlackPiece : Image
{
    public readonly int RP = 50;//Radius of Piece

    static BlackPiece()
    {
        DefaultStyleKeyProperty.OverrideMetadata(typeof(BlackPiece), new FrameworkPropertyMetadata(typeof(BlackPiece)));
    }
    
    public BlackPiece(int X, int Y)
    {
        this.Source = new BitmapImage(new Uri("pack://application:,,,/Pieces/BlackPiece.png"));
        this.Width = RP;
        this.Height = RP;
        Canvas.SetLeft(this, X - RP / 2);
        Canvas.SetTop(this, Y - RP / 2);
    }
}
