using System;

// 装饰模式
namespace DecoratorSample
{
    abstract class VisualComponent
    {
        public abstract void Display();
    }

    class Window : VisualComponent
    {
        public override void Display()
        {
            Console.WriteLine("显示窗体！");
        }

        class TextBox : VisualComponent
        {
            public override void Display()
            {
                Console.WriteLine("显示文本框！");
            }
        }
    }

    class ListBox : VisualComponent
    {
        public override void Display()
        {
            Console.WriteLine("显示列表框！");
        }
    }

    class ComponentDecorator : VisualComponent
    {
        private VisualComponent component;

        public ComponentDecorator( VisualComponent component )
        {
            this.component = component;
        }

        public override void Display()
        {
            component.Display();
        }
    }

    class ScrollBarDecorator : ComponentDecorator
    {
        public ScrollBarDecorator( VisualComponent component ) : base(component) { }

        public override void Display()
        {
            this.SetScrollBar();
            base.Display();
        }

        private void SetScrollBar()
        {
            Console.WriteLine("为构建增加滚动条！");
        }
    }

    class BlackBorderDecorator : ComponentDecorator
    {
        public BlackBorderDecorator( VisualComponent component ) : base(component) { }

        public override void Display()
        {
            this.SetBlackBorder();
            base.Display();
        }

        public void SetBlackBorder()
        {
            Console.WriteLine("为构建增加黑色边框！");
        }
    }
}
