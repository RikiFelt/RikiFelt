using System;
using ChangeFolderIcon.FolderInterface;

namespace ChangeFolderIcon.Exe
{
    internal class ExeFolder
    {
        /// <summary>
        /// 主函数
        /// </summary>
        /// <param name="args">文件夹列表</param>
        static void Main(string[] args)
        {
            if(args.Length == 0) return;

            FolderManager folderManager = new FolderManager();
            folderManager.LoadFolders(args);

            ExeFolderIconSetter setter = new ExeFolderIconSetter();
            folderManager.ForeachFolder(setter);

            Console.WriteLine("按任意键结束");
            Console.ReadKey();
        }
    }
}
