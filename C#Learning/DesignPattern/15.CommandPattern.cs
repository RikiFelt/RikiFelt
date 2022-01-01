using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// 命令模式
namespace CommandSample
{
    abstract class Command
    {
        public abstract void Execute();
    }

    class FunctionButton
    {
        public Command Command { get; set; }

        public void Click()
        {
            Console.WriteLine("单机功能键!");
            Command.Execute();
        }
    }

    class ExitCommand : Command
    {
        private SystemExitClass seObj;

        public ExitCommand()
        {
            seObj = new SystemExitClass();
        }

        public override void Execute()
        {
            seObj.Exit();
        }
    }

    class HelpCommand : Command
    {
        private DisplayHelpClass hcObj;

        public HelpCommand()
        {
            hcObj = new DisplayHelpClass();
        }

        public override void Execute()
        {
            hcObj.Display();
        }
    }

    class SystemExitClass
    {
        public void Exit()
        {
            Console.WriteLine("退出系统!");
        }
    }

    class DisplayHelpClass
    {
        public void Display()
        {
            Console.WriteLine("显示帮助文档!");
        }
    }

    // 命令队列
    class CommandQueue
    {
        private List<Command> commands = new List<Command>();

        public void AddCommand( Command command )
        {
            commands.Add(command);
        }

        public void Remove( Command command )
        {
            commands.Remove(command);
        }

        public void Execute()
        {
            foreach( Command command in commands )
            {
                command.Execute();
            }
        }
    }

    class Invoker
    {
        private CommandQueue commandQueue;

        public Invoker( CommandQueue commandQueue )
        {
            this.commandQueue = commandQueue;
        }

        public void setCommandQueue( CommandQueue commandQueue )
        {
            this.commandQueue = commandQueue;
        }

        public void Call()
        {
            commandQueue.Execute();
        }
    }
}
