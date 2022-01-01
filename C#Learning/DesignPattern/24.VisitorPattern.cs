using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// 访问者模式
namespace VisitorSample
{
    interface Employee
    {
        void Accept( Department handler );
    }

    class FulltimeEmployee : Employee
    {
        public string Name { get; set; }
        public double WeeklyWage { get; set; }
        public int WorkTime { get; set; }

        public FulltimeEmployee( string name, double weeklyWage, int workTime )
        {
            Name = name;
            WeeklyWage = weeklyWage;
            WorkTime = workTime;
        }

        public void Accept( Department handler )
        {
            handler.Visit(this);
        }
    }

    class ParttimeEmployee : Employee
    {
        public string Name { get; set; }
        public double HourWage { get; set; }
        public int WorkTime { get; set; }

        public ParttimeEmployee( string name, double hourWage, int workTime )
        {
            Name = name;
            HourWage = hourWage;
            WorkTime = workTime;
        }

        public void Accept( Department handler )
        {
            handler.Visit(this);
        }
    }

    abstract class Department
    {
        public abstract void Visit( FulltimeEmployee employee );
        public abstract void Visit( ParttimeEmployee employee );
    }

    class FADepartment : Department
    {
        public override void Visit( FulltimeEmployee employee )
        {
            int workTime = employee.WorkTime;
            double weekWage = employee.WeeklyWage;
            if( workTime > 40 )
            {
                weekWage = weekWage + (workTime - 40) * 100;
            }
            else
            {
                weekWage = weekWage - (40 - workTime) * 80;
                weekWage = weekWage < 40 ? 0 : weekWage;
            }
            Console.WriteLine("正式员工{0}的实际工资为：{1}元。", employee.Name, weekWage);
        }

        public override void Visit( ParttimeEmployee employee )
        {
            int workTime = employee.WorkTime;
            double hourWage = employee.HourWage;
            Console.WriteLine("临时工{0}的实际工资为：{1}元。", employee.Name, workTime * hourWage);
        }
    }

    class HRDepartment : Department
    {
        public override void Visit( FulltimeEmployee employee )
        {
            int workTime = employee.WorkTime;
            Console.WriteLine("正式员工{0}的实际工作时间为：{1}小时。", employee.Name, workTime);
        }

        public override void Visit( ParttimeEmployee employee )
        {
            int workTime = employee.WorkTime;
            Console.WriteLine("临时工{0}的实际工作时间为：{1}小时。", employee.Name, workTime);
        }
    }

    class EmployeeList
    {
        private ArrayList list = new ArrayList();

        public void AddEmployee( Employee employee )
        {
            list.Add(employee);
        }

        public void Accept( Department handler )
        {
            foreach( Employee employee in list )
            {
                employee.Accept(handler);
            }
        }
    }
}
