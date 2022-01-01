using System;

// 外观模式
namespace FacadeSample
{
    class FileReader
    {
        public string Read( string plainText )
        {
            Console.Write("获取明文：");
            Console.WriteLine(plainText);
            return plainText;
        }
    }

    class CipherMachine
    {
        public string Encrype( string plainText )
        {
            Console.Write("数据加密,蒋明文转换为密文：");
            string es = "";
            char[] chars = plainText.ToCharArray();
            foreach( char ch in chars )
            {
                string c = (ch % 7).ToString();
                es += c;
            }
            Console.WriteLine(es);
            return es;
        }
    }

    class FileWriter
    {
        public void Write( string encryptStr )
        {
            Console.WriteLine("保存密文。");
        }
    }

    class EncryptFacade
    {
        private FileReader reader;
        private CipherMachine cipher;
        private FileWriter writer;

        public EncryptFacade()
        {
            reader = new FileReader();
            cipher = new CipherMachine();
            writer = new FileWriter();
        }

        public void FileEncrypt( string plainText )
        {
            string plainStr = reader.Read(plainText);
            string encryptStr = cipher.Encrype(plainStr);
            writer.Write(encryptStr);
        }
    }

    class NewCipherMachine
    {
        public string Encrypt( string plainText )
        {
            Console.Write("数据加密,蒋明文转换为密文：");
            string es = "";
            int key = 10; // 设置密钥，位移数为10
            char[] chars = plainText.ToCharArray();
            foreach( char ch in chars )
            {
                int temp = Convert.ToInt32(ch);
                if( ch >= 'a' && ch <= 'z' )
                {
                    temp += key % 26;
                    if( temp > 'z' )
                        temp -= 26;
                }
                if( ch >= 'A' && ch <= 'Z' )
                {
                    temp += key % 26;
                    if( temp > 'Z' )
                        temp -= 26;
                }
                es += ((char)temp).ToString();
            }
            Console.WriteLine(es);
            return es;
        }
    }

    abstract class AbstractEncryptFacade
    {
        public abstract void FileEncrypt( string plainText );
    }

    class NewEncryptFacade : AbstractEncryptFacade
    {
        private FileReader reader;
        private NewCipherMachine cipter;
        private FileWriter writer;

        public NewEncryptFacade()
        {
            reader = new FileReader();
            cipter = new NewCipherMachine();
            writer = new FileWriter();
        }

        public override void FileEncrypt( string plainText )
        {
            string plainStr = reader.Read(plainText);
            string encryptStr = cipter.Encrypt(plainStr);
            writer.Write(encryptStr);
        }
    }
}
