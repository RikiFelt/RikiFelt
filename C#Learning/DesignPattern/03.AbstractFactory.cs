using System;

// 抽象工厂模式
namespace AbstractFactorySample
{
    interface Button
    {
        void Display();
    }

    class SpringButton : Button
    {
        public void Display()
        {
            Console.WriteLine("显示浅绿色的按钮");
        }
    }

    class SummerButton : Button
    {
        public void Display()
        {
            Console.WriteLine("显示浅蓝色的按钮");
        }
    }

    interface TextField
    {
        void Display();
    }

    class SpringTextField : TextField
    {
        public void Display()
        {
            Console.WriteLine("显示浅绿色边框的文本框");
        }
    }

    class SummerTextField : TextField
    {
        public void Display()
        {
            Console.WriteLine("显示浅蓝色边框的文本框");
        }
    }

    interface ComboBox
    {
        void Display();
    }

    class SpringComboBox : ComboBox
    {
        public void Display()
        {
            Console.WriteLine("显示浅绿色边框的组合框");
        }
    }

    class SummerComboBox : ComboBox
    {
        public void Display()
        {
            Console.WriteLine("显示浅蓝色边框的组合框");
        }
    }

    interface SkinFactory
    {
        Button CreateButton();
        TextField CreateTextField();
        ComboBox CreateComboBox();
    }

    class SpringSkinFactory : SkinFactory
    {
        public Button CreateButton()
        {
            return new SpringButton();
        }
        public TextField CreateTextField()
        {
            return new SpringTextField();
        }
        public ComboBox CreateComboBox()
        {
            return new SpringComboBox();
        }
    }

    class SummerSkinFactory : SkinFactory
    {
        public Button CreateButton()
        {
            return new SummerButton();
        }
        public TextField CreateTextField()
        {
            return new SummerTextField();
        }
        public ComboBox CreateComboBox()
        {
            return new SummerComboBox();
        }
    }
}
