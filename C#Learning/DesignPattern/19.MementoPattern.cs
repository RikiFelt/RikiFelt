using System;
using System.Collections.Generic;

// 备忘录模式
namespace MementoSample
{
    class Chessman
    {
        public string Label { get; set; }
        public int X { get; set; }
        public int Y { get; set; }

        public Chessman( string label, int x, int y )
        {
            this.Label = label;
            this.X = x;
            this.Y = y;
        }

        internal ChessmanMemento Save()
        {
            return new ChessmanMemento(this.Label, this.X, this.Y);
        }

        internal void Restore( ChessmanMemento memento )
        {
            this.Label = memento.Label;
            this.X = memento.X;
            this.Y = memento.Y;
        }
    }

    internal class ChessmanMemento
    {
        public string Label { get; set; }
        public int X { get; set; }
        public int Y { get; set; }

        public ChessmanMemento( string label, int x, int y )
        {
            this.Label = label;
            this.X = x;
            this.Y = y;
        }
    }

    public class MementoCaretaker
    {
        private Stack<ChessmanMemento> mementoStackIn = new Stack<ChessmanMemento>();
        private Stack<ChessmanMemento> mementoStackOut = new Stack<ChessmanMemento>();

        internal void Play( Chessman chess )
        {
            mementoStackIn.Push(chess.Save());
            mementoStackOut.Clear();
            Display(chess, 0);
        }

        internal void Undo( Chessman chess )
        {
            if( mementoStackIn.Count > 1 )
            {
                mementoStackOut.Push(mementoStackIn.Pop());
                chess.Restore(mementoStackIn.Peek());
                Display(chess, 1);
            }
            else
            {
                Display(chess, 3);
            }
        }

        internal void Redo( Chessman chess )
        {
            if( mementoStackOut.Count != 0 )
            {
                ChessmanMemento memento = mementoStackOut.Pop();
                mementoStackIn.Push(memento);
                chess.Restore(memento);
                Display(chess, 2);
            }
            else
            {
                Display(chess, 4);
            }
        }

        private void Display( Chessman chess, int state )
        {
            string msg = null;
            switch( state )
            {
                case 0:
                {
                    msg = "下棋,";
                    break;
                }
                case 1:
                {
                    msg = "悔棋,";
                    break;

                }
                case 2:
                {
                    msg = "撤销悔棋,";
                    break;
                }
                case 3:
                {
                    msg = "无法悔棋,";
                    break;
                }
                case 4:
                {
                    msg = "无法撤销悔棋,";
                    break;
                }
                default:
                {
                    break;
                }
            }
            Console.WriteLine("{0}棋子{1}的当前位置为：第{2}行第{3}列。", msg, chess.Label, chess.X, chess.Y);
        }
    }
}
