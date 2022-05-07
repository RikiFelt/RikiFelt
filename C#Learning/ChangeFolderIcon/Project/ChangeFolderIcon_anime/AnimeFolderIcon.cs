using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Net;
using System.Text;
using System.Xml;
using ChangeFolderIcon.FileInterface;
using ChangeFolderIcon.FolderInterface;

namespace ChangeFolderIcon.Anime
{
    public class AnimeFolderIconSetter : FolderIconSetter
    {
        public AnimeFolderIconSetter() { }

        /// <summary>
        /// 从文件夹内符合条件的图标中选择一个合适的图标
        /// </summary>
        /// <param name="folder">图标所在文件夹</param>
        /// <returns>图标</returns>
        public override string GetOneIcon(string folder)
        {
            string iconPath = GetAnimeFolderIcon(folder);
            if(!String.IsNullOrEmpty(iconPath))
            {
                return iconPath;
            }

            iconPath = FileUtil.GetFirstIconFile(folder);
            return iconPath;
        }

        private string GetAnimeFolderIcon(string folder)
        {
            string animeTitle = "";
            if(!GetAnimeTitleByFolderName(folder, ref animeTitle))
            {
                if(!GetAnimeTitleByAnimeFile(folder, ref animeTitle))
                {
                    return "";
                }
            }

            // 图标已存在时不更新
            string iconFullName = folder + "\\" + animeTitle + ".ico";
            if(File.Exists(iconFullName)) return iconFullName;

            if(!AcplayApi.DownloadAnimeIcon(folder, animeTitle))
            {
                return "";
            }

            return iconFullName;
        }

        private bool GetAnimeTitleByFolderName(string folder, ref string animeTitle)
        {
            string folderName = Path.GetFileNameWithoutExtension(folder);
            animeTitle = AcplayApi.GetAnimeTitle(folderName);
            return String.IsNullOrEmpty(animeTitle) ? false : true;
        }

        private bool GetAnimeTitleByAnimeFile(string folder, ref string animeTitle)
        {
            string videoFile = FileUtil.GetFirstVedioFile(folder);
            if(String.IsNullOrEmpty(videoFile))
            {
                return false;
            }

            string fileName = Path.GetFileNameWithoutExtension(videoFile);
            animeTitle = AcplayApi.GetAnimeTitle(fileName);
            return String.IsNullOrEmpty(animeTitle) ? false : true;
        }
    }

    public static class AcplayApi
    {
        private static XmlDocument xmlDoc = new XmlDocument();

        public static string GetAnimeTitle(string keyword)
        {
            string xmlContent = SearchAnime(keyword);
            if(String.IsNullOrEmpty(xmlContent))
            {
                xmlContent = MatchAnime(keyword);
            }
            string animeTitle = GetElementInnerText(xmlContent, "animeTitle");
            return animeTitle;
        }

        public static string GetImageUrl(string animeTitle)
        {
            string xmlContent = SearchAnime(animeTitle);
            string imageUrl = GetElementInnerText(xmlContent, "imageUrl");
            return imageUrl;
        }

        public static string SearchAnime(string keyword)
        {
            string requestUrl = "https://api.acplay.net/api/v2/search/anime?keyword=" + keyword;
            Stream stream = GetStream(requestUrl, "GET", "");
            string xmlContent = ReadStream(stream);
            stream.Close();
            return xmlContent;
        }

        public static string MatchAnime(string fileName)
        {
            string requestUrl = "https://api.acplay.net/api/v2/match";
            string parameter = GetMatchContent(fileName);
            Stream stream = GetStream(requestUrl, "POST", parameter);
            string xmlContent = ReadStream(stream);
            stream.Close();
            return xmlContent;
        }

        private static string GetMatchContent(string fileName)
        {
            xmlDoc.RemoveAll();

            // 通过文件名获取动漫标题
            string fileHash = "00000000000000000000000000000000";
            XmlElement matchRequestNode = xmlDoc.CreateElement("MatchRequest");
            XmlElement fileHashNode = xmlDoc.CreateElement("fileHash");
            XmlElement fileNameNode = xmlDoc.CreateElement("fileName");
            fileHashNode.InnerText = fileHash;
            fileNameNode.InnerText = fileName;
            xmlDoc.AppendChild(matchRequestNode);
            matchRequestNode.AppendChild(fileHashNode);
            matchRequestNode.AppendChild(fileNameNode);

            MemoryStream streamXml = new MemoryStream();
            XmlTextWriter writer = new XmlTextWriter(streamXml, Encoding.UTF8);
            writer.Formatting = Formatting.Indented;
            xmlDoc.Save(writer);

            StreamReader reader = new StreamReader(streamXml, Encoding.UTF8);
            streamXml.Position = 0;
            String content = reader.ReadToEnd();
            reader.Close();
            streamXml.Close();
            xmlDoc.RemoveAll();

            return content;
        }

        private static Stream GetStream(string url, string requestMethod, string parameter)
        {
            if(String.IsNullOrEmpty(url)) return null;

            HttpWebRequest req = (HttpWebRequest)WebRequest.Create(url);
            req.Method = requestMethod;
            req.ContentType = "application/xml; charset=utf-8";
            req.Headers.Add("Accept-Language", "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3");
            req.UserAgent = "Mozilla/5.0 (Windows NT 5.2; rv:12.0) Gecko/20100101 Firefox/12.0";

            // 添加 POST 参数
            if(requestMethod.Equals("POST") && !String.IsNullOrEmpty(parameter))
            {
                byte[] data = Encoding.UTF8.GetBytes(parameter);
                req.ContentLength = data.Length;
                using(Stream reqStream = req.GetRequestStream())
                {
                    reqStream.Write(data, 0, data.Length);
                    reqStream.Close();
                }
            }

            HttpWebResponse resp = (HttpWebResponse)req.GetResponse();
            return resp.GetResponseStream();
        }

        private static string ReadStream(Stream stream)
        {
            //获取内容
            string result = "";
            using(StreamReader reader = new StreamReader(stream, Encoding.UTF8))
            {
                result = reader.ReadToEnd();
            }
            return result;
        }

        private static string GetElementInnerText(string xmlContent, string tagName )
        {
            if(String.IsNullOrEmpty(xmlContent)) return "";

            string info = "";
            xmlDoc.RemoveAll();
            xmlDoc.LoadXml(xmlContent);
            XmlNodeList nodeList = xmlDoc.GetElementsByTagName(tagName);
            if(nodeList.Count > 0)
            {
                info = nodeList.Item(0).InnerText;
            }
            xmlDoc.RemoveAll();
            return info;
        }
        
        public static bool DownloadAnimeIcon(string folder, string animeTitle)
        {
            string imageUrl = GetImageUrl(animeTitle);
            Stream stream = GetStream(imageUrl, "GET", "");
            Image image = Image.FromStream(stream);
            string iconFullName = folder + "\\" + animeTitle + ".ico";
            return ImageToIcon(image, iconFullName);
        }

        private static bool ImageToIcon(Image imageJpg, string iconFullName)
        {
            if(imageJpg == null) return false;

            // 图标最大长宽为256
            Size iconSize = imageJpg.Size;
            iconSize.Width = iconSize.Width > 256 ? 256 : iconSize.Width;
            iconSize.Height = iconSize.Height > 256 ? 256 : iconSize.Height;

            Image imagePng = new Bitmap(imageJpg, iconSize); //先读取已有的图片为bitmap，并缩放至设定大小
            MemoryStream bitMapStream = new MemoryStream(); //存原图的内存流
            MemoryStream iconStream = new MemoryStream(); //存图标的内存流
            imagePng.Save(bitMapStream, ImageFormat.Png); //将原图读取为png格式并存入原图内存流
            BinaryWriter iconWriter = new BinaryWriter(iconStream); //新建二进制写入器以写入目标图标内存流
            /**
             * 下面是根据原图信息，进行文件头写入
             */
            iconWriter.Write((short)0);
            iconWriter.Write((short)1);
            iconWriter.Write((short)1);
            iconWriter.Write((byte)imagePng.Width);
            iconWriter.Write((byte)imagePng.Height);
            iconWriter.Write((short)0);
            iconWriter.Write((short)0);
            iconWriter.Write((short)32);
            iconWriter.Write((int)bitMapStream.Length);
            iconWriter.Write(22);
            //写入图像体至目标图标内存流
            iconWriter.Write(bitMapStream.ToArray());
            //保存流，并将流指针定位至头部以Icon对象进行读取输出为文件
            iconWriter.Flush();
            iconWriter.Seek(0, SeekOrigin.Begin);
            Stream iconFileStream = new FileStream(iconFullName, FileMode.Create);
            Icon icon = new Icon(iconStream);
            icon.Save(iconFileStream); //储存图像
            /**
             * 下面开始释放资源
             */
            iconFileStream.Close();
            iconWriter.Close();
            iconStream.Close();
            bitMapStream.Close();
            icon.Dispose();
            imagePng.Dispose();

            return File.Exists(iconFullName) ? true : false;
        }
    }
}
