using System;

// 简单工厂模式
namespace SimpleFctorySample
{
    interface Chart
    {
        void Display();
    }

    class HistogramChart : Chart
    {
        public HistogramChart()
        {
            Console.WriteLine("创建柱状图形");
        }

        public void Display()
        {
            Console.WriteLine("显示柱状图形");
        }
    }

    class PieChart : Chart
    {
        public PieChart()
        {
            Console.WriteLine("创建饼状图形");
        }

        public void Display()
        {
            Console.WriteLine("显示饼状图形");
        }
    }

    class LineChart : Chart
    {
        public LineChart()
        {
            Console.WriteLine("创建折状图形");
        }

        public void Display()
        {
            Console.WriteLine("显示折线图形");
        }
    }

    abstract class ChartFactory
    {
        public static Chart GetChart( string type )
        {
            Chart chart = null;
            switch( type )
            {
                case "histogram":
                {
                    chart = new HistogramChart();
                    Console.WriteLine("初始化设置柱状图");
                    break;
                }
                case "pie":
                {
                    chart = new PieChart();
                    Console.WriteLine("初始化设置饼状图");
                    break;
                }
                case "line":
                {
                    chart = new LineChart();
                    Console.WriteLine("初始化设置折线图");
                    break;
                }
                default:
                {
                    break;
                }
            }
            return chart;

        }
    }
}
