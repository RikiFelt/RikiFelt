using System;
using System.Collections;

// 享元模式
namespace FlyweightSample
{
    class Coordinates
    {
        public int x { get; set; }
        public int y { get; set; }

        public Coordinates( int x, int y )
        {
            this.x = x;
            this.y = y;
        }
    }

    abstract class IgoChessman
    {
        public abstract string GetColor();

        public void Display( Coordinates coord )
        {
            Console.WriteLine("棋子颜色：{0}, 棋子位置：{1},{2}", this.GetColor(), coord.x, coord.y);
        }
    }

    class BlockIgoChessman : IgoChessman
    {
        public override string GetColor()
        {
            return "黑色";
        }
    }

    class WhiteIgoChessman : IgoChessman
    {
        public override string GetColor()
        {
            return "白色";
        }
    }

    class IgoChessmanFactroy
    {
        private static IgoChessmanFactroy instance = new IgoChessmanFactroy();
        private Hashtable ht;

        private IgoChessmanFactroy()
        {
            ht = new Hashtable();
            IgoChessman block, white;
            block = new BlockIgoChessman();
            white = new WhiteIgoChessman();
            ht.Add("b", block);
            ht.Add("w", white);
        }

        public static IgoChessmanFactroy GetInstance()
        {
            return instance;
        }

        public IgoChessman GetIgoChessman( string color )
        {
            return (IgoChessman)ht[color];
        }
    }
}
