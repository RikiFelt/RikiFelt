namespace ChangeFolderIcon.Exe
{
    partial class SelectIconForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if(disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.IconList = new System.Windows.Forms.ImageList(this.components);
            this.IconView = new System.Windows.Forms.ListView();
            this.SuspendLayout();
            // 
            // IconList
            // 
            this.IconList.ColorDepth = System.Windows.Forms.ColorDepth.Depth32Bit;
            this.IconList.ImageSize = new System.Drawing.Size(128, 128);
            this.IconList.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // IconView
            // 
            this.IconView.HideSelection = false;
            this.IconView.Location = new System.Drawing.Point(12, 12);
            this.IconView.Name = "IconView";
            this.IconView.Size = new System.Drawing.Size(132, 159);
            this.IconView.SmallImageList = this.IconList;
            this.IconView.TabIndex = 0;
            this.IconView.UseCompatibleStateImageBehavior = false;
            this.IconView.View = System.Windows.Forms.View.SmallIcon;
            this.IconView.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.IconView_MouseDoubleClick);
            // 
            // SelectIconForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(157, 183);
            this.Controls.Add(this.IconView);
            this.Name = "SelectIconForm";
            this.Text = "SelectIconForm";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ImageList IconList;
        private System.Windows.Forms.ListView IconView;
    }
}