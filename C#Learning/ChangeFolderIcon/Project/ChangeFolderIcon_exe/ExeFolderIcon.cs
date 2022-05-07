using System.Collections.Generic;
using System.Drawing;
using ChangeFolderIcon.FileInterface;
using ChangeFolderIcon.FolderInterface;
using ChangeFolderIcon.Log;
using ChangeFolderIcon.Visitor;

namespace ChangeFolderIcon.Exe
{
    public class ExeFolderIconSetter : FolderIconSetter
    {
        public ExeFolderIconSetter() { }

        /// <summary>
        /// 从文件夹内符合条件的图标中选择一个合适的图标
        /// </summary>
        /// <param name="folder">图标所在文件夹</param>
        /// <returns>图标</returns>
        public override string GetOneIcon(string folder)
        {
            List<string> icons = FileUtil.GetAllIconfile(folder);
            List<string> exes = FileUtil.GetAllExefile(folder);
            if(icons.Count + exes.Count == 0)
            {
                Logger.Output(LogID.W2, folder);
                Logger.Output(LogID.G3, folder);
                if(!GetIconBySubFolder(folder, ref icons, ref exes))
                {
                    Logger.Output(LogID.W3, folder);
                    return "";
                }
            }
            if(icons.Count + exes.Count == 1)
            {
                return icons.Count > exes.Count ? icons[0] : exes[0];
            }

            SelectIconForm dialog = new SelectIconForm();
            foreach(string icon in icons)
            {
                // 从图标路径中获取图标
                dialog.AddImage(icon);
            }
            foreach(string exe in exes)
            {
                // 从exe程序中获取图标
                Image image = Icon.ExtractAssociatedIcon(exe).ToBitmap();
                dialog.AddImage(image);
            }

            dialog.ResizeForm();
            dialog.ShowDialog();
            int selectIndex = dialog.selectIndex;

            string iconPath = "";
            if(selectIndex < 0)
            {
                // 未选择任何图标，所以不设定文件夹图标
                Logger.Output(LogID.W4, folder);
            }
            else if(selectIndex + 1 <= icons.Count)
            {
                iconPath = icons[selectIndex];
            }
            else
            {
                iconPath = exes[selectIndex - icons.Count];
            }

            return iconPath;
        }

        /// <summary>
        /// 从子文件夹中寻找图标和程序文件
        /// </summary>
        /// <param name="folder">文件夹</param>
        /// <param name="icons">图标文件</param>
        /// <param name="exes">程序文件</param>
        /// <returns></returns>
        private bool GetIconBySubFolder(string folder, ref List<string> icons, ref List<string> exes)
        {
            // 从子文件夹中寻找图标文件
            FileCollector iconFileCollector = new FileCollector(icons);
            FileExtensionFilter iconFilter = new FileExtensionFilter(".ico", iconFileCollector);
            FolderFileVisitor fileVisitor = new FolderFileVisitor(iconFilter);
            FolderUtil.ForeachSubFolder(folder, fileVisitor);

            // 从子文件夹中寻找程序文件
            FileCollector exeFileCollector = new FileCollector(exes);
            FileExtensionFilter exeFilter = new FileExtensionFilter(".exe", exeFileCollector);
            fileVisitor = new FolderFileVisitor(exeFilter);
            FolderUtil.ForeachSubFolder(folder, fileVisitor);

            if(icons.Count + exes.Count == 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}
