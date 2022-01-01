using System;

// 工厂方法模式
namespace FactoryMethodSample
{
    interface Logger
    {
        void WriteLog();
    }

    class DatabaseLogger : Logger
    {
        public void WriteLog()
        {
            Console.WriteLine("数据库日记记录");
        }
    }

    class FileLogger : Logger
    {
        public void WriteLog()
        {
            Console.WriteLine("文件日记记录");
        }
    }

    abstract class LoggerFactory
    {
        public void WriteLog()
        {
            Logger logger = this.CreateLogger();
            logger.WriteLog();
        }

        public abstract Logger CreateLogger();
    }

    class DatabaseLoggerFactory : LoggerFactory
    {
        public override Logger CreateLogger()
        {
            Logger logger = new DatabaseLogger();
            return logger;
        }
    }

    class FileLoggerFactory : LoggerFactory
    {
        public override Logger CreateLogger()
        {
            Logger logger = new FileLogger();
            return logger;
        }
    }
}
