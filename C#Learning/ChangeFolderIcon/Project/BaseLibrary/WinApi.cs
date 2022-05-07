using System;
using System.Runtime.InteropServices;

namespace ChangeFolderIcon.WinApi
{
    [StructLayout(LayoutKind.Sequential)]
    public struct SHFileInfo
    {
        public IntPtr hIcon;
        public int iIcon;
        public uint dwAttributes;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
        public string szDisplayName;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 80)]
        public string szTypeName;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
    struct LPSHFOLDERCUSTOMSETTINGS
    {
        public UInt32 dwSize;
        public UInt32 dwMask;
        public IntPtr pvid;
        public string pszWebViewTemplate;
        public UInt32 cchWebViewTemplate;
        public string pszWebViewTemplateVersion;
        public string pszInfoTip;
        public UInt32 cchInfoTip;
        public IntPtr pclsid;
        public UInt32 dwFlags;
        public string pszIconFile;
        public UInt32 cchIconFile;
        public int iIconIndex;
        public string pszLogo;
        public UInt32 cchLogo;
    }

    /// <summary>
    /// shell32文件的方法
    /// </summary>
    class Win32
    {
        /// <summary>
        /// 引用shell32文件的SHGetSetFolderCustomSettings API方法      
        /// </summary>
        /// <param name="pfcs"></param>
        /// <param name="pszPath"></param>
        /// <param name="dwReadWrite"></param>
        /// <returns></returns>
        [DllImport("Shell32.dll", CharSet = CharSet.Auto)]
        public static extern UInt32 SHGetSetFolderCustomSettings(ref LPSHFOLDERCUSTOMSETTINGS pfcs, string pszPath, UInt32 dwReadWrite);
    }
}
