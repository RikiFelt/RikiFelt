using System;

namespace ChangeFolderIcon.Base
{
    static public class Util
    {
        static public bool IsEmptyStr(string str)
        {
            if(String.IsNullOrEmpty(str) )
            {
                return true;
            }
            return false;
        }
    }
}
