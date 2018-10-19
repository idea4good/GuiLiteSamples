using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace BuildWinforms
{
    public partial class UiBlock : PictureBox
    {
        [DllImport("HostMonitor.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getHbitmapOfHostMonitorUiFromDll(int display_id, int witdth, int height);

        [DllImport("HostMonitor.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sendTouch2HostMonitorFromDll(int display_id, uint msg_id, int x, int y);

        public void updateUI()
        {
            if (null != Image)
            {
                Image.Dispose();
                Image = null;
            }

            IntPtr bitmap = getHbitmapOfHostMonitorUiFromDll(m_index, m_ui_width, m_ui_height);
            if(bitmap != IntPtr.Zero)
            {
                Image = System.Drawing.Image.FromHbitmap(bitmap);
            }
        }

        public void UiBlockMouseUp(object sender, MouseEventArgs e)
        {
            if(e.Location.X < 0 || e.Location.X >= this.Width ||
                e.Location.Y < 0 || e.Location.Y >= this.Height)
            {
                return;
            }
            int ui_x = (e.Location.X * m_ui_width / this.Width);
            int ui_y = (e.Location.Y * m_ui_height / this.Height);
            sendTouch2HostMonitorFromDll(m_index, 0x4600, ui_x, ui_y);
            m_is_mouse_down = false;
        }

        public void UiBlockMouseDown(object sender, MouseEventArgs e)
        {
            if (e.Location.X < 0 || e.Location.X >= this.Width ||
                e.Location.Y < 0 || e.Location.Y >= this.Height)
            {
                return;
            }
            int ui_x = (e.Location.X * m_ui_width / this.Width);
            int ui_y = (e.Location.Y * m_ui_height / this.Height);
            sendTouch2HostMonitorFromDll(m_index, 0x4700, ui_x, ui_y);
            m_is_mouse_down = true;
        }

        public void UiBlockMouseMove(object sender, MouseEventArgs e)
        {
            if(!m_is_mouse_down)
            {
                return;
            }
            UiBlockMouseDown(sender, e);
        }

        public void UiBlockMouseDoubbleClick(object sender, MouseEventArgs e)
        {
            if(0 == m_index)
            {
                ((Form1)(Parent)).changeMode();
            }
            else
            {
                ((Form1)(Parent.Parent)).changeMode();
            }
        }

        public int m_index { get; set; }
        public int m_ui_width { get; set; }
        public int m_ui_height { get; set; }
        private bool m_is_mouse_down = false;
    }
}
