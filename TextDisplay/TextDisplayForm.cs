using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace TextDisplay
{
    class TextDisplayForm : Form
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
        public TextDisplayForm(string text, string fontName, float fontSize,
            Color color, Color transparencyColor, Screen screen, OverlayPosition position)
        {
            this.FormBorderStyle = FormBorderStyle.None;
            this.TopMost = true;
            this.ShowInTaskbar = false;

            this.BackColor = transparencyColor;
            this.TransparencyKey = transparencyColor;
            //this.BackColor = Color.Transparent;

            this.StartPosition = FormStartPosition.Manual;

            this.Left = screen.Bounds.Left;
            this.Top = screen.Bounds.Top;
            this.Width = screen.Bounds.Width;
            this.Height = screen.Bounds.Height;

            Label lbl = new Label();
            lbl.AutoSize = true;
            lbl.Text = text;
            lbl.ForeColor = color;
            lbl.BackColor = Color.Transparent;
            lbl.Font = new Font(fontName, fontSize);

            this.Controls.Add(lbl);

            this.Load += delegate
            {
                this.PositionLabel(lbl, position);
            };
        }

        private void PositionLabel(Label lbl, OverlayPosition pos)
        {
            const int margin = 20;

            int x = margin;
            int y = margin;

            switch (pos)
            {
                case OverlayPosition.TopLeft:
                    x = margin;
                    y = margin;
                    break;

                case OverlayPosition.TopCenter:
                    x = (ClientSize.Width - lbl.Width) / 2;
                    y = margin;
                    break;

                case OverlayPosition.TopRight:
                    x = ClientSize.Width - lbl.Width - margin;
                    y = margin;
                    break;

                case OverlayPosition.CenterLeft:
                    x = margin;
                    y = (ClientSize.Height - lbl.Height) / 2;
                    break;

                case OverlayPosition.Center:
                    x = (ClientSize.Width - lbl.Width) / 2;
                    y = (ClientSize.Height - lbl.Height) / 2;
                    break;

                case OverlayPosition.CenterRight:
                    x = ClientSize.Width - lbl.Width - margin;
                    y = (ClientSize.Height - lbl.Height) / 2;
                    break;

                case OverlayPosition.BottomLeft:
                    x = margin;
                    y = ClientSize.Height - lbl.Height - margin;
                    break;

                case OverlayPosition.BottomCenter:
                    x = (ClientSize.Width - lbl.Width) / 2;
                    y = ClientSize.Height - lbl.Height - margin;
                    break;

                case OverlayPosition.BottomRight:
                    x = ClientSize.Width - lbl.Width - margin;
                    y = ClientSize.Height - lbl.Height - margin;
                    break;
            }

            lbl.Location = new Point(x, y);
        }
    }
}
