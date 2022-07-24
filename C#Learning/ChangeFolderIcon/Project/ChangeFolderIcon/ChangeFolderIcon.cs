using System;
using System.Configuration;
using ChangeFolderIcon.FolderInterface;
using ChangeFolderIcon.Factroy;

namespace ChangeFolderIcon
{
    internal class ChangeFolderIcon
    {
        /// <summary>
        /// 主函数入口
        /// </summary>
        /// <param name="args">参数</param>
        static void Main(string[] args)
        {
            if(args.Length == 0) return;

            FolderManager folderManager = new FolderManager();
            folderManager.LoadFolders(args);

            string setIconType = ConfigurationManager.AppSettings["setIconType"];
            FolderIconSetter setter = FolderIconSetterFactory.GetSetter(setIconType);
            if(setter != null)
            {
                folderManager.ForeachFolder(setter);
            }
            else
            {
                Console.WriteLine("setIconType设置错误");
            }

            Console.WriteLine("按任意键结束");
            Console.ReadKey();
        }
    }
}
