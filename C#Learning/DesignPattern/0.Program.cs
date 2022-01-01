using System;
using System.Configuration;
using System.Reflection;
using System.Collections.Generic;

using SimpleFctorySample;
using FactoryMethodSample;
using AbstractFactorySample;
using BuilderSample;
using PrototypeSample;
using SingletonSample;
using AdapterSample;
using BridgeSample;
using CompositeSample;
using DecoratorSample;
using FacadeSample;
using FlyweightSample;
using ProxySample;
using CoRSample;
using CommandSample;
using InterpreterSample;
using IteratorSample;
using MediatorSample;
using MementoSample;
using ObserverSample;
using StateSample;
using StrategySample;
using TemplateMethodSample;
using VisitorSample;

/*
 * 创造型模式：简单工厂模式，工厂方法模式，抽象工厂模式，建造者模式，原型模式，单例模式
 * 结构型模式：适配器模式，桥接模式，组合模式，装饰模式，外观模式，享元模式，代理模式
 * 行为型模式：职责链模式，命令模式，解释器模式，迭代器模式，中介者模式，备忘录模式，
 *             观察者模式，状态模式，策略模式，模板方法模式，访问者模式
*/

namespace DesignPattern
{
    class Program
    {
        static void Main( string[] args )
        {
            // 创造性模式
            SimpleFctory();
            FactoryMethod();
            AbstractFactory();
            BuilderPattern();
            PrototypePattern();
            SingletonPattern();

            // 结构型模式
            AdapterPattern();
            BridgePattern();
            CompositePattern();
            DecoratorPattern();
            FacadePattern();
            FlyweightPattern();
            ProxyPattern();

            // 行为型模式
            CoRPattern();
            CommandPattern();
            InterpreterPattern();
            IteratorPattern();
            MediatorPattern();
            MementoPattern();
            ObserverPattern();
            StatePattern();
            StrategyPattern();
            TemplateMethodPattern();
            VisitorPattern();

            Console.Read();
        }

        static void ReturnLine()
        {
            Console.WriteLine("============================================");
        }

        public static void SimpleFctory()
        {
            // 读取配置文件
            string chartType = ConfigurationManager.AppSettings["chartType"];
            Chart chart = ChartFactory.GetChart(chartType);
            if( chart != null )
            {
                chart.Display();
            }
            else
            {
                Console.WriteLine("chartType设置错误");
            }
            ReturnLine();
        }

        public static void FactoryMethod()
        {
            string factoryString = ConfigurationManager.AppSettings["factory"];
            // 反射生成对象
            // object obj = Assembly.Load("程序集名称").CreateInstance("命名空间.类");
            LoggerFactory factory = (LoggerFactory)Assembly.Load("DesignPattern").CreateInstance(factoryString);
            if( factory != null )
            {
                factory.WriteLog();
            }
            else
            {
                Console.WriteLine("factory设置错误");
            }
            ReturnLine();
        }

        public static void AbstractFactory()
        {
            string factoryString = ConfigurationManager.AppSettings["abstractFactory"];
            SkinFactory factory = (SkinFactory)Assembly.Load("DesignPattern").CreateInstance(factoryString);
            if( factory != null )
            {
                AbstractFactorySample.Button bt = factory.CreateButton();
                TextField tf = factory.CreateTextField();
                AbstractFactorySample.ComboBox cb = factory.CreateComboBox();
                bt.Display();
                tf.Display();
                cb.Display();
            }
            else
            {
                Console.WriteLine("factory设置错误");
            }
            ReturnLine();
        }

        public static void BuilderPattern()
        {
            string builderType = ConfigurationManager.AppSettings["builder"];
            ActorBuilder ab = (ActorBuilder)Assembly.Load("DesignPattern").CreateInstance(builderType);
            if( ab != null )
            {
                Actor actor = ab.Construct();
                actor.Display();
            }
            else
            {
                Console.WriteLine("builder设置错误");
            }
            ReturnLine();
        }

        public static void PrototypePattern()
        {
            WeeklyLog log_previous, log_new;
            log_previous = new WeeklyLog();
            Attachment attachment = new Attachment();
            log_previous.Attachment = attachment;
            log_new = log_previous.Clone();
            Console.WriteLine("周报是否相同? {0}", (log_previous == log_new) ? "是" : "否");
            Console.WriteLine("附件是否相同? {0}", (log_previous.Attachment == log_new.Attachment) ? "是" : "否");
            ReturnLine();
        }

        public static void SingletonPattern()
        {
            LoadBalancer balancer1, balancer2, balancer3, balancer4;
            balancer1 = LoadBalancer.GetLoadBalancer();
            balancer2 = LoadBalancer.GetLoadBalancer();
            balancer3 = LoadBalancer.GetLoadBalancer();
            balancer4 = LoadBalancer.GetLoadBalancer();

            if( balancer1 == balancer2 && balancer2 == balancer3 && balancer3 == balancer4 )
            {
                Console.WriteLine("服务器负载均衡器具有唯一性！");
            }

            // 增加服务器
            balancer1.AddServer("Server 1");
            balancer1.AddServer("Server 2");
            balancer1.AddServer("Server 3");
            balancer1.AddServer("Server 4");

            for( int i = 0; i < 10; i++ )
            {
                // 这里需要调试卡时间才能出现不同的Server
                string server = balancer1.GetServer();
                Console.WriteLine("分发请求至服务器: " + server);
            }
            ReturnLine();
        }

        public static void AdapterPattern()
        {
            ScoreOperation operation;
            string adapterType = ConfigurationManager.AppSettings["adapter"];
            operation = (ScoreOperation)Assembly.Load("DesignPattern").CreateInstance(adapterType);

            int[] scores = { 84, 76, 50, 69, 90, 91, 88, 96 };
            int[] result;
            Console.WriteLine("成绩的排序结果是：");
            result = operation.Sort(scores);
            foreach( int i in result )
            {
                Console.Write(i + ", ");
            }
            Console.WriteLine("");
            ReturnLine();
        }

        public static void BridgePattern()
        {
            string osType = ConfigurationManager.AppSettings["os"];
            string imgType = ConfigurationManager.AppSettings["image"];
            Image image = (Image)Assembly.Load("DesignPattern").CreateInstance(imgType);
            ImageImp imp = (ImageImp)Assembly.Load("DesignPattern").CreateInstance(osType);
            image.SetImageImp(imp);
            image.ParseFile("中国地图");
            ReturnLine();
        }

        public static void CompositePattern()
        {
            AbstractFile file1 = new ImageFile("小龙女.jpg");
            AbstractFile file2 = new ImageFile("张无忌.gif");
            AbstractFile file3 = new TextFile("九阴真经.txt");
            AbstractFile file4 = new TextFile("葵花宝典.doc");
            AbstractFile file5 = new VideoFile("神雕侠侣.avi");

            AbstractFile myFolder = new Folder("我的资料");
            AbstractFile imageFolder = new Folder("图像文件");
            AbstractFile textFolder = new Folder("文本文件");
            AbstractFile videoFolder = new Folder("视频文件");

            myFolder.Add(imageFolder);
            myFolder.Add(textFolder);
            myFolder.Add(videoFolder);
            imageFolder.Add(file1);
            imageFolder.Add(file2);
            textFolder.Add(file3);
            textFolder.Add(file4);
            videoFolder.Add(file5);

            // 从"我的资料"节点开始进行杀毒操作
            myFolder.KillVirus();
            ReturnLine();
        }

        public static void DecoratorPattern()
        {
            VisualComponent component = new Window();
            VisualComponent componentSB = new ScrollBarDecorator(component);
            componentSB.Display();
            ReturnLine();
        }

        public static void FacadePattern()
        {
            string facadeString = ConfigurationManager.AppSettings["facade"];
            AbstractEncryptFacade ef = (AbstractEncryptFacade)Assembly.Load("DesignPattern").CreateInstance(facadeString);
            ef.FileEncrypt("Hello World!");
            ReturnLine();
        }

        public static void FlyweightPattern()
        {
            IgoChessman black1, black2, black3, white1, white2;
            IgoChessmanFactroy factroy = IgoChessmanFactroy.GetInstance();

            black1 = factroy.GetIgoChessman("b");
            black2 = factroy.GetIgoChessman("b");
            black3 = factroy.GetIgoChessman("b");
            Console.WriteLine("判断两颗黑子是否相同：" + (black1 == black2));

            white1 = factroy.GetIgoChessman("w");
            white2 = factroy.GetIgoChessman("w");
            Console.WriteLine("判断两颗白子是否相同：" + (white1 == white2));

            black1.Display(new Coordinates(1, 2));
            black2.Display(new Coordinates(3, 4));
            black3.Display(new Coordinates(1, 3));
            white1.Display(new Coordinates(2, 5));
            white2.Display(new Coordinates(2, 4));

            ReturnLine();
        }

        public static void ProxyPattern()
        {
            string proxy = ConfigurationManager.AppSettings["proxy"];
            Searcher searcher = (Searcher)Assembly.Load("DesignPattern").CreateInstance(proxy);
            string result = searcher.DoSearch("杨过", "玉女心经");
            ReturnLine();
        }

        public static void CoRPattern()
        {
            Approver wjzhang, gyang, jguo, meeting;
            wjzhang = new CoRSample.Director("张无忌");
            gyang = new VicePresident("杨过");
            jguo = new President("郭靖");
            meeting = new Congress("董事会");

            // 创建职责链
            wjzhang.SetSuccessor(gyang);
            gyang.SetSuccessor(jguo);
            jguo.SetSuccessor(meeting);

            // 创建多个采购单对象并递交请求
            PurchaseRequest pr1 = new PurchaseRequest(45000, 10001, "购买倚天剑");
            wjzhang.ProcessRequest(pr1);

            PurchaseRequest pr2 = new PurchaseRequest(60000, 10002, "购买《葵花宝典》");
            wjzhang.ProcessRequest(pr2);

            PurchaseRequest pr3 = new PurchaseRequest(160000, 10003, "购买《金刚经》");
            wjzhang.ProcessRequest(pr3);

            PurchaseRequest pr4 = new PurchaseRequest(800000, 10004, "购买桃花岛");
            wjzhang.ProcessRequest(pr4);

            PurchaseRequest pr5 = new PurchaseRequest(1000000, 10005, "购买美国");
            wjzhang.ProcessRequest(pr5);

            ReturnLine();
        }

        public static void CommandPattern()
        {
            FunctionButton fb = new FunctionButton();
            string commandStr = ConfigurationManager.AppSettings["command"];
            Command command = (Command)Assembly.Load("DesignPattern").CreateInstance(commandStr);
            fb.Command = command;
            fb.Click();
            ReturnLine();
        }

        public static void InterpreterPattern()
        {
            // todo
        }

        public static void IteratorPattern()
        {
            List<object> products = new List<object>();
            products.Add("倚天剑");
            products.Add("屠龙刀");
            products.Add("断肠草");
            products.Add("葵花宝典");
            products.Add("玉女心经");

            AbstractObjectList list = new ProductList(products);
            AbstractIterator iterator = list.CreateIterator();
            Console.WriteLine("正向遍历：");
            while( !iterator.IsLast() )
            {
                Console.WriteLine(iterator.GetNextItem() + ",");
                iterator.Next();
            }
            Console.WriteLine("-------------------");
            Console.WriteLine("逆向遍历：");
            while( !iterator.IsFirst() )
            {
                Console.WriteLine(iterator.GetPreviousItem() + ",");
                iterator.Previous();
            }
            ReturnLine();
        }

        public static void MediatorPattern()
        {
            ConcreteMediator mediator = new ConcreteMediator();

            MediatorSample.Button addBT = new MediatorSample.Button();
            MediatorSample.List list = new MediatorSample.List();
            MediatorSample.ComboBox comboBox = new MediatorSample.ComboBox();
            MediatorSample.TextBox textBox = new MediatorSample.TextBox();

            addBT.SetMeditor(mediator);
            list.SetMeditor(mediator);
            comboBox.SetMeditor(mediator);
            textBox.SetMeditor(mediator);

            mediator.addButton = addBT;
            mediator.list = list;
            mediator.comboBox = comboBox;
            mediator.textBox = textBox;

            addBT.Changed();
            Console.WriteLine("-------------------------");
            list.Changed();

            ReturnLine();
        }

        public static void MementoPattern()
        {
            int index = -1;
            MementoCaretaker mc = new MementoCaretaker();
            Chessman chess = new Chessman("车", 1, 1);
            mc.Play(chess);
            chess.Y = 4;
            mc.Play(chess);
            chess.X = 5;
            mc.Play(chess);
            mc.Undo(chess);
            mc.Undo(chess);
            mc.Redo(chess);
            mc.Redo(chess);
            ReturnLine();
        }

        public static void ObserverPattern()
        {
            AllyControlCenter acc = new ConcreteAllyControlCenter("金庸群侠");
            IObserver player1 = new Player("杨过");
            IObserver player2 = new Player("段誉");
            IObserver player3 = new Player("乔峰");
            IObserver player4 = new Player("虚竹");
            acc.Join(player1);
            acc.Join(player2);
            acc.Join(player3);
            acc.Join(player4);
            player1.BeAttacked(acc);
            ReturnLine();
        }

        public static void StatePattern()
        {
            StateSample.Account acc = new StateSample.Account("段誉", 0.0);
            acc.Deposit(1000);
            acc.Withdraw(2000);
            acc.Deposit(3000);
            acc.Withdraw(4000);
            acc.Withdraw(1000);
            acc.ComputeInterest();
            ReturnLine();
        }

        public static void StrategyPattern()
        {
            MovieTicket mt = new MovieTicket();
            double originalPrice = 60.0;

            mt.Price = originalPrice;
            Console.WriteLine("原始价格为：{0}", originalPrice);

            string discountType = ConfigurationManager.AppSettings["discountType"];
            Discount discount = (Discount)Assembly.Load("DesignPattern").CreateInstance(discountType);
            mt.SetDiscount(discount);

            double currentPrice = mt.Price;
            Console.WriteLine("打折后为：{0}", currentPrice);

            ReturnLine();
        }

        public static void TemplateMethodPattern()
        {
            string subClassStr = ConfigurationManager.AppSettings["subClass"];
            TemplateMethodSample.Account account =
                (TemplateMethodSample.Account)Assembly.Load("DesignPattern").CreateInstance(subClassStr);
            account.Handle("张无忌", "123456");
            ReturnLine();
        }

        public static void VisitorPattern()
        {
            EmployeeList list = new EmployeeList();
            Employee fte1, fte2, fte3, pte1, pte2;
            fte1 = new FulltimeEmployee("张无忌", 3200.00, 45);
            fte2 = new FulltimeEmployee("杨过", 2000.00, 40);
            fte3 = new FulltimeEmployee("段誉", 2400.00, 38);
            pte1 = new ParttimeEmployee("洪七公", 80.00, 20);
            pte2 = new ParttimeEmployee("郭靖", 60.00, 18);

            list.AddEmployee(fte1);
            list.AddEmployee(fte2);
            list.AddEmployee(fte3);
            list.AddEmployee(pte1);
            list.AddEmployee(pte2);

            string visitorStr = ConfigurationManager.AppSettings["visitor"];
            Department dep = (Department)Assembly.Load("DesignPattern").CreateInstance(visitorStr);
            list.Accept(dep);
            ReturnLine();
        }
    }
}
