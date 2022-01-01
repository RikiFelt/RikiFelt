using System;
using System.Collections;

// 单利模式
namespace SingletonSample
{
    // 单例模式的实现
    class Singleton
    {
        // 静态私有成员变量
        private static Singleton instance = null;

        // 私有构造函数
        private Singleton() { }

        public static Singleton GetInstance()
        {
            if( instance == null )
                instance = new Singleton();
            return instance;
        }
    }

    // 单例模式的应用实例
    class LoadBalancer
    {
        private static LoadBalancer instance = null;
        private ArrayList serverList = null;

        private LoadBalancer()
        {
            serverList = new ArrayList();
        }

        public static LoadBalancer GetLoadBalancer()
        {
            if( instance == null )
            {
                instance = new LoadBalancer();
            }
            return instance;
        }

        public void AddServer( string server )
        {
            serverList.Add(server);
        }

        public void RemoveServer( string server )
        {
            serverList.Remove(server);
        }

        public string GetServer()
        {
            Random random = new Random();
            int i = random.Next(serverList.Count);
            return serverList[i].ToString();
        }
    }

    // 饿汉式单例
    class EagerSingleton
    {
        private static EagerSingleton instance = new EagerSingleton();
        private EagerSingleton() { }
        public static EagerSingleton GetInstance()
        {
            return instance;
        }
    }

    // 懒汉式单例
    class LazySingleton
    {
        private static LazySingleton instance = null;
        // 程序运行时创建一个静态只读的辅助对象
        private static readonly object syncRoot = new object();
        private LazySingleton() { }
        public static LazySingleton GetInstance()
        {
            // 第一重判断，先判断实例是否存在，不存在再加锁处理
            if( instance == null )
            {
                // 加锁的程序在某一时刻只允许一个线程访问
                lock( syncRoot )
                {
                    // 第二重判断
                    if( instance == null )
                    {
                        instance = new LazySingleton(); // 创建单例实例
                    }
                }
            }
            return instance;
        }
    }
}
