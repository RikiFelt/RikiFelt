using System;
using System.Collections.Generic;
using System.IO;

namespace ChangeFolderIcon.Log
{
    public enum LogID : int
    {
        G1 = 101,
        G2 = 102,
        G3 = 103,
        W1 = 201,
        W2 = 202,
        W3 = 203,
        W4 = 204,
        E1 = 301
    }

    static internal class LogStr
    {
        // Guide
        static public string ProcessingFolder        = "当前正在处理的文件夹是 : {0}";
        static public string SetFolderIcon           = "--文件夹 '{0}' 图标设定为 : {1}";
        static public string SearchSubFolder         = "----正在查找文件夹 '{0}' 的子文件夹";
        // Warning
        static public string NotExistFolder          = "--文件夹 '{0}' 不存在";
        static public string NotExistIcon            = "--文件夹 '{0}' 内不存在图标或程序";
        static public string NotExistIconInSubFolder = "----文件夹 '{0}' 的子文件夹内不存在图标或程序";
        static public string NoIconSelected          = "--未选择文件夹 '{0}' 的图标";
        // Error
        static public string FailedToSetFolderIcon   = "--文件夹 '{0}' 图标设定失败";
    }

    static public class Logger
    {
        static Dictionary<LogID, string> logMessage = new Dictionary<LogID, string>()
        {
            { LogID.G1, LogStr.ProcessingFolder },
            { LogID.G2, LogStr.SetFolderIcon },
            { LogID.G3, LogStr.SearchSubFolder },
            { LogID.W1, LogStr.NotExistFolder },
            { LogID.W2, LogStr.NotExistIcon },
            { LogID.W3, LogStr.NotExistIconInSubFolder },
            { LogID.W4, LogStr.NoIconSelected },
            { LogID.E1, LogStr.FailedToSetFolderIcon },
        };

        static public void Output(LogID logID, string value)
        {
            string msg = logMessage[logID];
            string folderName = Path.GetFileName(value);
            string str = string.Format(msg, folderName);
            Console.WriteLine(str);
        }

        static public void Output(LogID logID, string value1, string value2)
        {
            string msg = logMessage[logID];
            string temp1 = Path.GetFileName(value1);
            string temp2 = Path.GetFileName(value2);
            string str = string.Format(msg, temp1, temp2);
            Console.WriteLine(str);
        }
    }
}
