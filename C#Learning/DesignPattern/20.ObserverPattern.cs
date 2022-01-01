using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// 观察者模式
namespace ObserverSample
{
    interface IObserver
    {
        string Name { get; set; }
        void Help();
        void BeAttacked( AllyControlCenter acc );
    }

    abstract class AllyControlCenter
    {
        protected string allyName;
        protected List<IObserver> players = new List<IObserver>();

        public void SetAllyName(string name)
        {
            this.allyName = name;
        }

        public string GetAllyName() { return allyName; }

        public void Join(IObserver obs)
        {
            Console.WriteLine("{0}加入{1}战队!", obs.Name, this.allyName);
            players.Add(obs);
        }

        public void Quit( IObserver obs )
        {
            Console.WriteLine("{0}退出{1}战队!", obs.Name, this.allyName);
            players.Remove(obs);
        }

        public abstract void NotifyObserver( string name );
    }

    class ConcreteAllyControlCenter : AllyControlCenter
    {
        public ConcreteAllyControlCenter(string name)
        {
            Console.WriteLine("{0}战队组建成功！", name);
            Console.WriteLine("-------------------------");
            this.allyName = name;
        }

        public override void NotifyObserver( string name )
        {
            Console.WriteLine("{0}战队紧急通知，盟友{1}遭受敌人攻击！", this.allyName, name);
            foreach(IObserver obs in players )
            {
                if( !obs.Name.Equals(name))
                {
                    obs.Help();
                }
            }
        }
    }

    class Player : IObserver
    {
        public string Name { get; set; }
        public Player(string name)
        {
            this.Name = name;
        }

        public void Help()
        {
            Console.WriteLine("坚持住，{0}来救你！", Name);
        }

        public void BeAttacked( AllyControlCenter acc)
        {
            Console.WriteLine("{0}被攻击！", this.Name);
            acc.NotifyObserver(this.Name);
        }
    }
}
