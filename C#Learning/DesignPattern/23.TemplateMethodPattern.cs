using System;

// 模板方法模式
namespace TemplateMethodSample
{
    abstract class Account
    {
        public bool Validate( string account, string password )
        {
            Console.WriteLine("账号：{0}", account);
            Console.WriteLine("密码：{0}", password);
            if( account.Equals("张无忌") && password.Equals("123456") )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public abstract void CalculateInterest();

        public void Display()
        {
            Console.WriteLine("显示利息！");
        }

        public void Handle( string account, string password )
        {
            if( !Validate(account, password) )
            {
                Console.WriteLine("账号或密码错误！");
                return;
            }
            CalculateInterest();
            Display();
        }
    }

    class CurrentAccount : Account
    {
        public override void CalculateInterest()
        {
            Console.WriteLine("按活期利率计算利息！");
        }
    }

    class SavingAccount : Account
    {
        public override void CalculateInterest()
        {
            Console.WriteLine("按定期利率计算利息！");
        }
    }
}
