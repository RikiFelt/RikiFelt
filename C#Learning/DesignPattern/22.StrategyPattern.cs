using System;

// 策略模式
namespace StrategySample
{
    interface Discount
    {
        double Calculate( double price );
    }


    class MovieTicket
    {
        private double price;
        private Discount discount;

        public void SetDiscount( Discount discount )
        {
            this.discount = discount;
        }

        public double Price
        {
            get { return discount.Calculate(this.price); }
            set { price = value; }
        }
    }

    class StudentDiscount : Discount
    {
        private const double DISCOUNT = 0.8;
        public double Calculate( double price )
        {
            Console.WriteLine("学生票：");
            return price * DISCOUNT;
        }
    }

    class ChildrenDiscount : Discount
    {
        private const double DISCOUNT = 10;
        public double Calculate( double price )
        {
            Console.WriteLine("儿童票：");
            return price - DISCOUNT;
        }
    }

    class VIPDiscount : Discount
    {
        private const double DISCOUNT = 0.5;
        public double Calculate( double price )
        {
            Console.WriteLine("VIP票：");
            Console.WriteLine("增加积分！");
            return price * DISCOUNT;
        }
    }
}
