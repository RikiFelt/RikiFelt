using System;

// 状态模式
namespace StateSample
{
    class Account
    {
        private AccountState state;
        private string owner;
        private double balance = 0;

        public Account( string owner, double init )
        {
            this.owner = owner;
            this.balance = init;
            this.state = new NormalState(this);
            Console.WriteLine("{0}开户，初始金额为{1}", this.owner, init);
            Console.WriteLine("------------------------------");
        }

        public double Balance
        {
            get { return balance; }
            set { balance = value; }
        }

        public void SetState( AccountState state )
        {
            this.state = state;
        }

        public void Deposit( double amount )
        {
            Console.WriteLine("{0}存款{1}", this.owner, amount);
            state.Deposit(amount);
            Console.WriteLine("现在余额为{0}", this.balance);
            Console.WriteLine("现在账户状态为{0}", this.state.GetType().ToString());
            Console.WriteLine("------------------------------");
        }

        public void Withdraw( double amount )
        {
            Console.WriteLine("{0}取款{1}", this.owner, amount);
            state.Withdraw(amount);
            Console.WriteLine("现在余额为{0}", this.balance);
            Console.WriteLine("现在账户状态为{0}", this.state.GetType().ToString());
            Console.WriteLine("------------------------------");
        }

        public void ComputeInterest()
        {
            state.ComputeInterest();
        }
    }

    abstract class AccountState
    {
        private Account acc;
        public Account Acc
        {
            get { return acc; }
            set { acc = value; }
        }
        public abstract void Deposit( double amount );
        public abstract void Withdraw( double amount );
        public abstract void ComputeInterest();
        public abstract void StateCheck();
    }

    class NormalState : AccountState
    {
        public NormalState( Account account )
        {
            this.Acc = account;
        }

        public NormalState( AccountState state )
        {
            this.Acc = state.Acc;
        }

        public override void Deposit( double amount )
        {
            Acc.Balance += amount;
            StateCheck();
        }

        public override void Withdraw( double amount )
        {
            Acc.Balance -= amount;
            StateCheck();
        }

        public override void ComputeInterest()
        {
            Console.WriteLine("正常状态，无需支付利息！");
        }

        public override void StateCheck()
        {
            if( Acc.Balance > -2000 && Acc.Balance <= 0 )
            {
                Acc.SetState(new OverdraftState(this));
            }
            else if( Acc.Balance == -2000 )
            {
                Acc.SetState(new RestrictedState(this));
            }
            else if( Acc.Balance <= -2000 )
            {
                Console.WriteLine("操作受限！");
            }
        }
    }

    class OverdraftState : AccountState
    {
        public OverdraftState( Account account )
        {
            this.Acc = account;
        }

        public OverdraftState( AccountState state )
        {
            this.Acc = state.Acc;
        }

        public override void Deposit( double amount )
        {
            Acc.Balance += amount;
            StateCheck();
        }

        public override void Withdraw( double amount )
        {
            Acc.Balance -= amount;
            StateCheck();
        }

        public override void ComputeInterest()
        {
            Console.WriteLine("计算利息！");
        }

        public override void StateCheck()
        {
            if( Acc.Balance > 0 )
            {
                Acc.SetState(new NormalState(this));
            }
            else if( Acc.Balance == -2000 )
            {
                Acc.SetState(new RestrictedState(this));
            }
            else if( Acc.Balance < -2000 )
            {
                Console.WriteLine("操作受限！");
            }
        }
    }

    class RestrictedState : AccountState
    {
        public RestrictedState( Account account )
        {
            this.Acc = account;
        }

        public RestrictedState( AccountState state )
        {
            this.Acc = state.Acc;
        }

        public override void Deposit( double amount )
        {
            Acc.Balance += amount;
            StateCheck();
        }

        public override void Withdraw( double amount )
        {
            Console.WriteLine("账号受限，取款失败");
        }

        public override void ComputeInterest()
        {
            Console.WriteLine("计算利息！");
        }

        public override void StateCheck()
        {
            if( Acc.Balance > 0 )
            {
                Acc.SetState(new NormalState(this));
            }
            else if( Acc.Balance > -2000 )
            {
                Acc.SetState(new OverdraftState(this));
            }
        }
    }
}
