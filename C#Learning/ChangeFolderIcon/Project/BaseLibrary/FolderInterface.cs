using System;
using System.Collections.Generic;
using System.IO;
using ChangeFolderIcon.Log;
using ChangeFolderIcon.Visitor;
using ChangeFolderIcon.WinApi;

namespace ChangeFolderIcon.FolderInterface
{
    /// <summary>
    /// 文件集管理类
    /// </summary>
    public class FolderManager
    {
        private List<string> folders;

        public FolderManager()
        {
            folders = new List<string>();
        }

        /// <summary>
        /// 收集文件夹
        /// </summary>
        /// <param name="args">文件夹列表</param>
        public void LoadFolders(string[] args)
        {
            foreach(string arg in args)
            {
                if(Directory.Exists(arg))
                {
                    folders.Add(arg);
                }
            }
        }

        /// <summary>
        /// 循环文件夹
        /// </summary>
        /// <param name="visitor">访问者</param>
        public void ForeachFolder(Visitor<string> visitor)
        {
            foreach(string folder in folders)
            {
                visitor.Visit(folder);
            }
        }
    }

    /// <summary>
    /// 文件夹操作类
    /// </summary>
    static public class FolderUtil
    {
        /// <summary>
        /// 设定文件夹的图标
        /// </summary>
        /// <param name="folderPath">文件夹路径</param>
        /// <param name="iconPath">图标文件路径</param>
        /// <returns></returns>
        public static bool SetFolderIcon(string folderPath, string iconPath)
        {
            // 检查文件夹和图标文件是否存在
            if(!Directory.Exists(folderPath) || !File.Exists(iconPath))
            {
                return false;
            }

            // 检查图标文件是否正确
            string exname = Path.GetExtension(iconPath);
            if(!exname.Equals(".exe") && !exname.Equals(".ico"))
            {
                return false;
            }

            // 设定文件夹图标
            LPSHFOLDERCUSTOMSETTINGS FolderSettings = new LPSHFOLDERCUSTOMSETTINGS();
            FolderSettings.dwMask = 0x10;
            FolderSettings.pszIconFile = iconPath;
            FolderSettings.iIconIndex = 0;

            UInt32 FCS_FORCEWRITE = 0x00000002;
            UInt32 FCS_WRITE = FCS_FORCEWRITE;
            UInt32 S_OK = 0x00000000;

            UInt32 HRESULT = Win32.SHGetSetFolderCustomSettings(ref FolderSettings, folderPath, FCS_WRITE);

            return HRESULT == S_OK ? true : false ;
        }
    
        /// <summary>
        /// 循环文件夹内的文件
        /// </summary>
        /// <param name="folderPath">文件夹</param>
        /// <param name="visitor">访问者</param>
        public static void ForeachFile(string folderPath, ref Visitor<string> visitor)
        {
            FolderFileVisitor folderFileVisitor = new FolderFileVisitor(visitor);
            folderFileVisitor.Visit(folderPath);
        }

        /// <summary>
        /// 循环文件夹内的子文件夹
        /// </summary>
        /// <param name="folderPath">文件夹</param>
        /// <param name="visitor">访问者</param>
        public static void ForeachSubFolder(string folderPath, Visitor<string> visitor)
        {
            SubFolderVisitor subFolderVisitor = new SubFolderVisitor(visitor);
            subFolderVisitor.Visit(folderPath);
        }
    }


    /// <summary>
    /// 文件夹图标设定类
    /// </summary>
    public abstract class FolderIconSetter : Visitor<string>
    {
        public FolderIconSetter() { }

        /// <summary>
        /// 设定文件夹图标
        /// </summary>
        /// <param name="folder">要设定图标的文件夹</param>
        /// <returns></returns>
        public override bool Visit(string folder)
        {
            // 检查文件夹是否存在
            Logger.Output(LogID.G1, folder);
            if(!Directory.Exists(folder))
            {
                Logger.Output(LogID.W1, folder);
                return true;
            }

            // 选择一个合适的图标
            string icon = GetOneIcon(folder);

            // 设定图标
            if(FolderUtil.SetFolderIcon(folder, icon))
            {
                Logger.Output(LogID.G2, folder, icon);
            }
            else
            {
                Logger.Output(LogID.E1, folder);
            }

            return true;
        }

        /// <summary>
        /// 从文件夹内符合条件的图标中选择一个合适的图标
        /// </summary>
        /// <param name="folder">图标所在文件夹</param>
        /// <returns>图标</returns>
        public abstract string GetOneIcon(string folder);
    }
}
