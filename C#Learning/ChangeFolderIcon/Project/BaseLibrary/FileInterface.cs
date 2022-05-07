using ChangeFolderIcon.Visitor;
using System.Collections.Generic;

namespace ChangeFolderIcon.FileInterface
{
    /// <summary>
    /// 文件接口
    /// </summary>
    static public class FileUtil
    {
        public static string GetFirstIconFile(string folder)
        {
            return GetFirstFile(folder, ".ico");
        }

        public static string GetFirstExeFile(string folder)
        {
            return GetFirstFile(folder, ".exe");
        }

        public static string GetFirstVedioFile(string folder)
        {
            string[] extensions = new string[] { ".mp4", ".mkv", ".rmvb", ".avi" };
            return GetFirstFile(folder, extensions);
        }

        public static List<string> GetAllIconfile(string folder)
        {
            return GetAllFile(folder, ".ico");
        }

        public static List<string> GetAllExefile(string folder)
        {
            return GetAllFile(folder, ".exe");
        }

        private static string GetFirstFile(string folder, string extension)
        {
            FilePicker picker = new FilePicker();
            FileExtensionFilter filter = new FileExtensionFilter(extension, picker);
            FolderFileVisitor visitor = new FolderFileVisitor(filter);
            visitor.Visit(folder);
            return picker.Get();
        }

        private static string GetFirstFile(string folder, string[] extensions)
        {
            FilePicker picker = new FilePicker();
            FileExtensionsFilter filter = new FileExtensionsFilter(extensions, picker);
            FolderFileVisitor visitor = new FolderFileVisitor(filter);
            visitor.Visit(folder);
            return picker.Get();
        }

        private static List<string> GetAllFile(string folder, string extension)
        {
            List<string> files = new List<string>();
            FileCollector collector = new FileCollector(files);
            FileExtensionFilter filter = new FileExtensionFilter(extension, collector);
            FolderFileVisitor visitor = new FolderFileVisitor(filter);
            visitor.Visit(folder);
            return files;
        }

        private static List<string> GetAllFile(string folder, string[] extensions)
        {
            List<string> files = new List<string>();
            FileCollector collector = new FileCollector(files);
            FileExtensionsFilter filter = new FileExtensionsFilter(extensions, collector);
            FolderFileVisitor visitor = new FolderFileVisitor(filter);
            visitor.Visit(folder);
            return files;
        }
    }
}
