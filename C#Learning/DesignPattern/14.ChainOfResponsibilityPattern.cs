using System;

namespace CoRSample
{
    class PurchaseRequest
    {
        public double Amount { get; set; }
        public int Number { get; set; }
        public string purpose { get; set; }

        public PurchaseRequest( double amount, int number, string purpose )
        {
            this.Amount = amount;
            this.Number = number;
            this.purpose = purpose;
        }
    }

    abstract class Approver
    {
        protected Approver successor; // 定义后继对象
        protected string name;        // 审批人姓名

        public Approver( string name )
        {
            this.name = name;
        }

        public void SetSuccessor( Approver successor )
        {
            this.successor = successor;
        }
        public abstract void ProcessRequest( PurchaseRequest request );
    }

    class Approver_ : Approver
    {
        protected int amount;
        protected string appellation;
        public Approver_( string name, string appellation, int amount ) : base(name)
        {
            this.amount = amount;
            this.appellation = appellation;
        }

        public override void ProcessRequest( PurchaseRequest request )
        {
            if( request.Amount < amount )
            {
                Console.WriteLine("{0}{1}审批采购单：{2}，金额：{3}元，采购目的：{4}。",
                                  appellation, name, request.Number, request.Amount, request.purpose);
            }
            else
            {
                if( successor != null )
                {
                    successor.ProcessRequest(request);
                }
                else
                {
                    Console.WriteLine("数额过大，无法采购，采购单：{0}，金额：{1}元，采购目的：{2}。",
                                       request.Number, request.Amount, request.purpose);
                }
            }
        }
    }

    class Director : Approver_
    {
        public Director( string name ) : base(name, "主任", 50000) { }
    }

    class VicePresident : Approver_
    {
        public VicePresident( string name ) : base(name, "副董事长", 100000) { }
    }

    class President : Approver_
    {
        public President( string name ) : base(name, "董事长", 500000) { }
    }

    class Congress : Approver_
    {
        public Congress( string name ) : base(name, "召开", 1000000) { }
    }
}
