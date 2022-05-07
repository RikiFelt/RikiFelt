using System;
using ChangeFolderIcon.FolderInterface;

namespace ChangeFolderIcon.Anime
{
    internal class AnimeFolder
    {
        static void Main(string[] args)
        {
            if(args.Length == 0) return;

            FolderManager folderManager = new FolderManager();
            folderManager.LoadFolders(args);

            AnimeFolderIconSetter setter = new AnimeFolderIconSetter();
            folderManager.ForeachFolder(setter);

            Console.WriteLine("按任意键结束");
            Console.ReadKey();
        }
    }
}
