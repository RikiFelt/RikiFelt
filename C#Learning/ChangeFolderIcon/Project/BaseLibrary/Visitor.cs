using System.Collections.Generic;
using System.IO;

namespace ChangeFolderIcon.Visitor
{
    public abstract class Visitor<T>
    {
        public abstract bool Visit(T value);
    }

    public class SubFolderVisitor : Visitor<string>
    {
        Visitor<string> visitor;

        public SubFolderVisitor(Visitor<string> visitor)
        {
            this.visitor = visitor;
        }

        public override bool Visit(string folder)
        {
            bool result = true;
            string[] subFolders = Directory.GetDirectories(folder, "*", SearchOption.TopDirectoryOnly);
            foreach(string subFolder in subFolders)
            {
                result = visitor.Visit(subFolder);
                if(!result) break;
            }
            return result;
        }
    }

    public class FolderFileVisitor : Visitor<string>
    {
        Visitor<string> visitor;

        public FolderFileVisitor(Visitor<string> visitor)
        {
            this.visitor = visitor;
        }

        public override bool Visit(string folder)
        {
            bool result = true;
            string[] files = Directory.GetFiles(folder);
            foreach(string file in files)
            {
                result = visitor.Visit(file);
                if(!result) break;
            }
            return result;
        }
    }

    public class FileExtensionFilter : Visitor<string>
    {
        string extension;
        Visitor<string> visitor;

        public FileExtensionFilter(string extension, Visitor<string> visitor)
        {
            this.extension = extension;
            this.visitor = visitor;
        }

        public override bool Visit(string file)
        {
            string exname = Path.GetExtension(file);
            if(extension.Equals(exname))
            {
                return visitor.Visit(file);
            }
            return true;
        }
    }
    
    public class FileExtensionsFilter : Visitor<string>
    {
        string[] extensions;
        Visitor<string> visitor;

        public FileExtensionsFilter(string[] extensions, Visitor<string> visitor)
        {
            this.extensions = extensions;
            this.visitor = visitor;
        }

        public override bool Visit(string file)
        {
            string exname = Path.GetExtension(file);
            foreach(string extension in extensions)
            {
                if(extension.Equals(exname))
                {
                    return visitor.Visit(file);
                }
            }
            return true;
        }
    }

    public class FilePicker : Visitor<string>
    {
        string file;

        public FilePicker()
        {
            file = null;
        }

        public override bool Visit(string file)
        {
            this.file = file;
            return false;
        }

        public string Get()
        {
            return file;
        }
    }
    
    public class FileCollector : Visitor<string>
    {
        List<string> files;

        public FileCollector(List<string> files)
        {
            this.files = files;
        }

        public override bool Visit(string file)
        {
            files.Add(file);
            return true;
        }
    }
}
