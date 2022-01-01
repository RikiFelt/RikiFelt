using System;

// 中介者模式
namespace MediatorSample
{
    abstract class Mediator
    {
        public abstract void ComponentChanged( Component component );
    }

    class ConcreteMediator : Mediator
    {
        public Button addButton;
        public List list;
        public TextBox textBox;
        public ComboBox comboBox;

        public override void ComponentChanged( Component component )
        {
            if( component == addButton )
            {
                Console.WriteLine("--点击增加按钮--");
                list.Update();
                comboBox.Update();
                textBox.Update();
            }
            else if( component == list )
            {
                Console.WriteLine("--从列表框中选择客户--");
                comboBox.Select();
                textBox.SetText();
            }
            else if( component == comboBox )
            {
                Console.WriteLine("--从组合框中选择客户--");
                comboBox.Select();
                textBox.SetText();
            }
        }
    }

    abstract class Component
    {
        protected Mediator mediator;

        public void SetMeditor( Mediator mediator )
        {
            this.mediator = mediator;
        }

        public void Changed()
        {
            mediator.ComponentChanged(this);
        }

        public abstract void Update();
    }

    class Button : Component
    {
        public override void Update()
        {
            // 按钮不产生响应
        }
    }

    class List : Component
    {
        public override void Update()
        {
            Console.WriteLine("列表框增加一项：张无忌。");
        }

        public void Select()
        {
            Console.WriteLine("列表中增加一下项：小龙女。");
        }
    }

    class ComboBox : Component
    {
        public override void Update()
        {
            Console.WriteLine("组合框增加一项：张无忌。");
        }

        public void Select()
        {
            Console.WriteLine("组合框增加一项：小龙女。");
        }
    }

    class TextBox : Component
    {
        public override void Update()
        {
            Console.WriteLine("客户信息增加成功后文本框清空");
        }

        public void SetText()
        {
            Console.WriteLine("文本框增加一项：小龙女。");
        }
    }
}
