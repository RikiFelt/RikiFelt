using System;
using System.Collections.Generic;

// 组合模式
namespace CompositeSample
{
    abstract class AbstractFile
    {
        public abstract void Add( AbstractFile file );
        public abstract void Remove( AbstractFile file );
        public abstract AbstractFile GetChild( int i );
        public abstract void KillVirus();
    }

    class AbstractFile_ : AbstractFile
    {
        private string name;
        private string type;

        public AbstractFile_( string name, string type )
        {
            this.name = name;
            this.type = type;
        }

        public override void Add( AbstractFile file )
        {
            Console.WriteLine("对不起，不支持该方法");
        }

        public override void Remove( AbstractFile file )
        {
            Console.WriteLine("对不起，不支持该方法");
        }

        public override AbstractFile GetChild( int i )
        {
            Console.WriteLine("对不起，不支持该方法");
            return null;
        }

        public override void KillVirus()
        {
            Console.WriteLine("----对{0}'{1}'进行杀毒", type, name);
        }
    }

    class ImageFile : AbstractFile_
    {
        public ImageFile( string name ) : base(name, "图像文件") { }
    }

    class TextFile : AbstractFile_
    {
        public TextFile( string name ) : base(name, "文本文件") { }
    }

    class VideoFile : AbstractFile_
    {
        public VideoFile( string name ) : base(name, "视频文件") { }
    }

    class Folder : AbstractFile
    {
        private string name;
        private List<AbstractFile> fileList = new List<AbstractFile>();

        public Folder( string name )
        {
            this.name = name;
        }

        public override void Add( AbstractFile file )
        {
            fileList.Add(file);
        }

        public override void Remove( AbstractFile file )
        {
            fileList.Remove(file);
        }

        public override AbstractFile GetChild( int i )
        {
            return (AbstractFile)fileList[i];
        }

        public override void KillVirus()
        {
            Console.WriteLine("****对文件夹'{0}'进行杀毒", name);

            foreach( AbstractFile file in fileList )
            {
                file.KillVirus();
            }
        }
    }
}
