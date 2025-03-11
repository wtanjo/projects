using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Gomoku;
/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    private bool isBlack = true;
    private readonly int RR = 20;// Radius of available Ranges

    public MainWindow()
    {
        InitializeComponent();

        for (int x = 50; x <= 750; x += 70)
        {
            for (int y = 50; y <= 750; y += 70)
            {
                Ellipse AvailableRange = new() { Width = RR, Height = RR, Fill = Brushes.Transparent, Stroke = Brushes.Transparent };
                ARcanvas.Children.Add(AvailableRange);
                Canvas.SetLeft(AvailableRange, x - RR / 2);
                Canvas.SetTop(AvailableRange, y - RR / 2);
                AvailableRange.MouseDown += MDDropPiece;
                AvailableRange.MouseDown += MDJudgeAndDesert;
                AvailableRange.MouseEnter += MEAvailableRange;
                AvailableRange.MouseLeave += MLAvailableRange;
            }
        }
    }

    private void MDDropPiece(object sender, MouseButtonEventArgs e)
    {
        if (isBlack)
        {
            canvas.Children.Add(new BlackPiece((int)(Canvas.GetLeft((Ellipse)sender) + RR / 2), (int)(Canvas.GetTop((Ellipse)sender) + RR / 2)));
            isBlack = false;
        }
        else
        {
            canvas.Children.Add(new WhitePiece((int)(Canvas.GetLeft((Ellipse)sender) + RR / 2), (int)(Canvas.GetTop((Ellipse)sender) + RR / 2)));
            isBlack = true;
        }
    }

    private void MDJudgeAndDesert(object sender, MouseButtonEventArgs e)
    {
        this.Cursor = Cursors.Arrow;
        ((Ellipse)sender).MouseDown -= MDDropPiece;
        ((Ellipse)sender).MouseDown -= MDJudgeAndDesert;
        ((Ellipse)sender).MouseEnter -= MEAvailableRange;
        ((Ellipse)sender).MouseLeave -= MLAvailableRange;
        ARcanvas.Children.Remove((Ellipse)sender);

        //Judge whether there's a winner and if so, who is the winner.
        if (isBlack)
        {
            var WhitePiecesQuery = canvas.Children.OfType<WhitePiece>();
            List<WhitePiece> WhitePiecesForWin = [];
            if (WhitePiecesQuery.Count() < 5)
                return;

            foreach (var WP in WhitePiecesQuery)
            {
                for (int i = 1; i < 5; i++)//水平方向
                {
                    var WhitePiecesForWinQuery = from WhitePiece WPFW in WhitePiecesQuery
                                                 where (int)Canvas.GetLeft(WPFW) == (int)Canvas.GetLeft(WP) + i * 70 && (int)Canvas.GetTop(WPFW) == (int)Canvas.GetTop(WP)
                                                 select WPFW;
                    if (WhitePiecesForWinQuery.Any<WhitePiece>() == false)
                    {
                        WhitePiecesForWin.Clear();
                        break;
                    }
                    else
                        WhitePiecesForWin.AddRange(WhitePiecesForWinQuery);
                }
                if (WhitePiecesForWin.Count == 4)
                {
                    GameOver(isBlack);
                    return;
                }
                for (int i = 1; i < 5; i++)//竖直方向
                {
                    var WhitePiecesForWinQuery = from WhitePiece WPFW in WhitePiecesQuery
                                                 where (int)Canvas.GetLeft(WPFW) == (int)Canvas.GetLeft(WP) && (int)Canvas.GetTop(WPFW) == (int)Canvas.GetTop(WP) + i * 70
                                                 select WPFW;
                    if (WhitePiecesForWinQuery.Any<WhitePiece>() == false)
                    {
                        WhitePiecesForWin.Clear();
                        break;
                    }
                    else
                        WhitePiecesForWin.AddRange(WhitePiecesForWinQuery);
                }
                if (WhitePiecesForWin.Count == 4)
                {
                    GameOver(isBlack);
                    return;
                }
                for (int i = 1; i < 5; i++)//左下到右上
                {
                    var WhitePiecesForWinQuery = from WhitePiece WPFW in WhitePiecesQuery
                                                 where (int)Canvas.GetLeft(WPFW) == (int)Canvas.GetLeft(WP) + i * 70 && (int)Canvas.GetTop(WPFW) == (int)Canvas.GetTop(WP) - i * 70
                                                 select WPFW;
                    if (WhitePiecesForWinQuery.Any<WhitePiece>() == false)
                    {
                        WhitePiecesForWin.Clear();
                        break;
                    }
                    else
                        WhitePiecesForWin.AddRange(WhitePiecesForWinQuery);
                }
                if (WhitePiecesForWin.Count == 4)
                {
                    GameOver(isBlack);
                    return;
                }
                for (int i = 1; i < 5; i++)//左上到右下
                {
                    var WhitePiecesForWinQuery = from WhitePiece WPFW in WhitePiecesQuery
                                                 where (int)Canvas.GetLeft(WPFW) == (int)Canvas.GetLeft(WP) + i * 70 && (int)Canvas.GetTop(WPFW) == (int)Canvas.GetTop(WP) + i * 70
                                                 select WPFW;
                    if (WhitePiecesForWinQuery.Any<WhitePiece>() == false)
                    {
                        WhitePiecesForWin.Clear();
                        break;
                    }
                    else
                        WhitePiecesForWin.AddRange(WhitePiecesForWinQuery);
                }
                if (WhitePiecesForWin.Count == 4)
                {
                    GameOver(isBlack);
                    return;
                }
            }
        }
        else
        {
            var BlackPiecesQuery = canvas.Children.OfType<BlackPiece>();
            List<BlackPiece> BlackPiecesForWin = [];
            if (BlackPiecesQuery.Count() < 5)
                return;

            foreach (var BP in BlackPiecesQuery)
            {
                for (int i = 1; i < 5; i++)//水平方向
                {
                    var BlackPiecesForWinQuery = from BlackPiece BPFW in BlackPiecesQuery
                                                 where (int)Canvas.GetLeft(BPFW) == (int)Canvas.GetLeft(BP) + i * 70 && (int)Canvas.GetTop(BPFW) == (int)Canvas.GetTop(BP)
                                                 select BPFW;
                    if (BlackPiecesForWinQuery.Any<BlackPiece>() == false)
                    {
                        BlackPiecesForWin.Clear();
                        break;
                    }
                    else
                        BlackPiecesForWin.AddRange(BlackPiecesForWinQuery);
                }
                if (BlackPiecesForWin.Count == 4)
                {
                    GameOver(isBlack);
                    return;
                }
                for (int i = 1; i < 5; i++)//竖直方向
                {
                    var BlackPiecesForWinQuery = from BlackPiece BPFW in BlackPiecesQuery
                                                 where (int)Canvas.GetLeft(BPFW) == (int)Canvas.GetLeft(BP) && (int)Canvas.GetTop(BPFW) == (int)Canvas.GetTop(BP) + i * 70
                                                 select BPFW;
                    if (BlackPiecesForWinQuery.Any<BlackPiece>() == false)
                    {
                        BlackPiecesForWin.Clear();
                        break;
                    }
                    else
                        BlackPiecesForWin.AddRange(BlackPiecesForWinQuery);
                }
                if (BlackPiecesForWin.Count == 4)
                {
                    GameOver(isBlack);
                    return;
                }
                for (int i = 1; i < 5; i++)//左下到右上
                {
                    var BlackPiecesForWinQuery = from BlackPiece BPFW in BlackPiecesQuery
                                                 where (int)Canvas.GetLeft(BPFW) == (int)Canvas.GetLeft(BP) + i * 70 && (int)Canvas.GetTop(BPFW) == (int)Canvas.GetTop(BP) - i * 70
                                                 select BPFW;
                    if (BlackPiecesForWinQuery.Any<BlackPiece>() == false)
                    {
                        BlackPiecesForWin.Clear();
                        break;
                    }
                    else
                        BlackPiecesForWin.AddRange(BlackPiecesForWinQuery);
                }
                if (BlackPiecesForWin.Count == 4)
                {
                    GameOver(isBlack);
                    return;
                }
                for (int i = 1; i < 5; i++)//左上到右下
                {
                    var BlackPiecesForWinQuery = from BlackPiece BPFW in BlackPiecesQuery
                                                 where (int)Canvas.GetLeft(BPFW) == (int)Canvas.GetLeft(BP) + i * 70 && (int)Canvas.GetTop(BPFW) == (int)Canvas.GetTop(BP) + i * 70
                                                 select BPFW;
                    if (BlackPiecesForWinQuery.Any<BlackPiece>() == false)
                    {
                        BlackPiecesForWin.Clear();
                        break;
                    }
                    else
                        BlackPiecesForWin.AddRange(BlackPiecesForWinQuery);
                }
                if (BlackPiecesForWin.Count == 4)
                {
                    GameOver(isBlack);
                    return;
                }
            }
        }
    }

    private void MEAvailableRange(object sender, EventArgs e)
    {
        this.Cursor = Cursors.Hand;
    }

    private void MLAvailableRange(object sender, EventArgs e)
    {
        this.Cursor = Cursors.Arrow;
    }

    private void GameOver(bool isBlack)
    {
        foreach (Ellipse AvailableRange in ARcanvas.Children)
        {
            AvailableRange.MouseDown -= MDDropPiece;
            AvailableRange.MouseDown -= MDJudgeAndDesert;
            AvailableRange.MouseEnter -= MEAvailableRange;
            AvailableRange.MouseLeave -= MLAvailableRange;
        }
        ARcanvas.Children.Clear();
        MessageBox.Show(isBlack ? "白方获胜" : "黑方获胜");
    }
}
