using System;

// 原型模式
namespace PrototypeSample
{
    class Attachment
    {
        private string Name { get; set; }

        public void Download()
        {
            Console.WriteLine("下载附件，文件名为{0}.", Name);
        }
    }

    class WeeklyLog
    {
        public Attachment Attachment { get; set; }
        public string Name { get; set; }
        public string Date { get; set; }
        public string Content { get; set; }

        // 使用MemberwiseClone()方法实现浅克隆
        public WeeklyLog Clone()
        {
            return this.MemberwiseClone() as WeeklyLog;
        }
    }

}
