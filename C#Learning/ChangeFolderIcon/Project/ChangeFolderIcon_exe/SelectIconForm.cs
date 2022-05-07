using System.Drawing;
using System.Windows.Forms;

namespace ChangeFolderIcon.Exe
{
    public partial class SelectIconForm : Form
    {
        public int selectIndex { set; get; }

        public SelectIconForm()
        {
            selectIndex = -1;
            InitializeComponent();
        }

        public void AddImage(string path)
        {
            Image image = Image.FromFile(path);
            AddImage(image);
        }

        public void AddImage(Image image)
        {
            int imageIndex = IconList.Images.Count;
            IconList.Images.Add(image);
            ListViewItem listViewItem = new ListViewItem("", imageIndex);
            IconView.Items.Add(listViewItem);
        }

        public void ResizeForm()
        {
            int imageHeight = 128;
            int imageCount = IconList.Images.Count;
            int formAddWidth = 0;
            if(IconList.Images.Count > 5 )
            {
                imageCount = 5;
                formAddWidth = 20;
            }
            Size sizeForm = this.Size;
            IconView.Size = new Size(IconView.Size.Width + formAddWidth, imageHeight * imageCount + 30);
            this.Size = new Size(this.Size.Width + formAddWidth, imageHeight * imageCount + 100);
        }

        private void IconView_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            ListViewItem item = IconView.GetItemAt(e.X, e.Y);
            selectIndex = item.Index;
            Close();
        }
    }
}
