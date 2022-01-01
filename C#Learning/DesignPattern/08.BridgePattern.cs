using System;

namespace BridgeSample
{
    class Matrix
    {
        // nothing
    }

    interface ImageImp
    {
        void DoPaint( Matrix m );
    }

    class WindowsImp : ImageImp
    {
        public void DoPaint( Matrix m )
        {
            Console.Write("在Windows操作系统中显示图像：");
        }
    }

    class LinuxImp : ImageImp
    {
        public void DoPaint( Matrix m )
        {
            Console.Write("在Linux操作系统中显示图像：");
        }
    }

    class UinxImp : ImageImp
    {
        public void DoPaint( Matrix m )
        {
            Console.Write("在Uinx操作系统中显示图像：");
        }
    }

    abstract class Image
    {
        protected ImageImp imp;

        public void SetImageImp( ImageImp imp )
        {
            this.imp = imp;
        }

        public abstract void ParseFile( string fileName );
    }

    class JPGImage : Image
    {
        public override void ParseFile( string fileName )
        {
            Matrix m = new Matrix();
            imp.DoPaint(m);
            Console.WriteLine("{0},格式为JPG。", fileName);
        }
    }

    class PNGImage : Image
    {
        public override void ParseFile( string fileName )
        {
            Matrix m = new Matrix();
            imp.DoPaint(m);
            Console.WriteLine("{0},格式为PNG。", fileName);
        }
    }

    class BMPImage : Image
    {
        public override void ParseFile( string fileName )
        {
            Matrix m = new Matrix();
            imp.DoPaint(m);
            Console.WriteLine("{0},格式为BMP。", fileName);
        }
    }
}
