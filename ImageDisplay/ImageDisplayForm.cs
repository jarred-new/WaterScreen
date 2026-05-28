using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace ImageDisplay
{
    public class ImageDisplayForm : Form
    {
        protected override CreateParams CreateParams
        {
            get
            {
                const int WS_EX_TRANSPARENT = 0x20;
                const int WS_EX_LAYERED = 0x80000;

                CreateParams cp =
                    base.CreateParams;

                cp.ExStyle |=
                    WS_EX_TRANSPARENT |
                    WS_EX_LAYERED;

                return cp;
            }
        }
        private PictureBox bug;

        public ImageDisplayForm(
            string imagePath,
            Color tk,
            Screen screen,
            OverlayPosition position,
            int sizePercent)
        {
            this.FormBorderStyle =
                FormBorderStyle.None;

            this.ShowInTaskbar = false;

            this.TopMost = true;

            this.StartPosition =
                FormStartPosition.Manual;

            this.BackColor = tk;
            this.TransparencyKey = tk;

            this.Bounds = screen.Bounds;

            bug = new PictureBox();

            bug.BackColor =
                Color.Transparent;

            bug.Image =
                Image.FromFile(imagePath);

            bug.SizeMode =
                PictureBoxSizeMode.Zoom;

            this.Controls.Add(bug);

            ResizeBug(sizePercent);

            PositionBug(position);

            this.Resize += delegate
            {
                ResizeBug(sizePercent);
                PositionBug(position);
            };
        }

        private void ResizeBug(int sizePercent)
        {
            if (bug.Image == null)
                return;

            int targetHeight =
                Height * sizePercent / 100;

            float aspect =
                (float)bug.Image.Width /
                bug.Image.Height;

            int targetWidth =
                (int)(targetHeight * aspect);

            bug.Size =
                new Size(
                    targetWidth,
                    targetHeight);
        }

        private void PositionBug(OverlayPosition pos)
        {
            const int margin = 20;

            int x = margin;
            int y = margin;

            switch (pos)
            {
                case OverlayPosition.TopLeft:
                    break;

                case OverlayPosition.TopCenter:
                    x = (Width -
                        bug.Width) / 2;
                    break;

                case OverlayPosition.TopRight:
                    x = Width -
                        bug.Width -
                        margin;
                    break;

                case OverlayPosition.CenterLeft:
                    y = (Height -
                        bug.Height) / 2;
                    break;

                case OverlayPosition.Center:
                    x = (Width -
                        bug.Width) / 2;
                    y = (Height -
                        bug.Height) / 2;
                    break;

                case OverlayPosition.CenterRight:
                    x = Width -
                        bug.Width -
                        margin;

                    y = (Height -
                        bug.Height) / 2;
                    break;

                case OverlayPosition.BottomLeft:
                    y = Height -
                        bug.Height -
                        margin;
                    break;

                case OverlayPosition.BottomCenter:
                    x = (Width -
                        bug.Width) / 2;

                    y = Height -
                        bug.Height -
                        margin;
                    break;

                case OverlayPosition.BottomRight:
                    x = Width -
                        bug.Width -
                        margin;

                    y = Height -
                        bug.Height -
                        margin;
                    break;

                default:
                    MessageBox.Show(
                        "Invalid Position\n\n" +
                        "TL TC TR\n" +
                        "CL C CR\n" +
                        "BL BC BR");

                    Application.Exit();
                    
                    return;
            }

            bug.Location =
                new Point(x, y);
        }
    }
}