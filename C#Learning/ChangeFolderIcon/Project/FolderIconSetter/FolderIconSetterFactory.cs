using ChangeFolderIcon.Anime;
using ChangeFolderIcon.Exe;
using ChangeFolderIcon.FolderInterface;
using System;

namespace ChangeFolderIcon.Factroy
{
    /// <summary>
    /// 简单工厂
    /// </summary>
    public static class FolderIconSetterFactory
    {
        public static FolderIconSetter GetSetter(string type)
        {
            FolderIconSetter setter = null;
            switch(type)
            {
                case "exe":
                {
                    setter = new ExeFolderIconSetter();
                    Console.WriteLine("初始化应用文件夹图标设定程序");
                    break;
                }
                case "anime":
                {
                    setter = new AnimeFolderIconSetter();
                    Console.WriteLine("初始化动漫文件夹图标设定程序");
                    break;
                }
                default:
                {
                    break;
                }
            }
            return setter;
        }
    }
}
