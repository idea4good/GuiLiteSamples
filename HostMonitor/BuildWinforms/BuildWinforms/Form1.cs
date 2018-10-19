using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;

namespace BuildWinforms
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            uiBlock0.m_index = 0;
            uiBlock0.m_ui_width = 1024;
            uiBlock0.m_ui_height = 768;

            uiBlock1.m_index = 1;
            uiBlock1.m_ui_width = 1024;
            uiBlock1.m_ui_height = 370;

            uiBlock2.m_index = 2;
            uiBlock2.m_ui_width = 1024;
            uiBlock2.m_ui_height = 370;

            uiBlock3.m_index = 3;
            uiBlock3.m_ui_width = 1024;
            uiBlock3.m_ui_height = 370;

            uiBlock4.m_index = 4;
            uiBlock4.m_ui_width = 1024;
            uiBlock4.m_ui_height = 370;

            uiBlock5.m_index = 5;
            uiBlock5.m_ui_width = 1024;
            uiBlock5.m_ui_height = 370;

            uiBlock6.m_index = 6;
            uiBlock6.m_ui_width = 1024;
            uiBlock6.m_ui_height = 370;

            uiBlock7.m_index = 7;
            uiBlock7.m_ui_width = 1024;
            uiBlock7.m_ui_height = 370;

            uiBlock8.m_index = 8;
            uiBlock8.m_ui_width = 1024;
            uiBlock8.m_ui_height = 370;

            System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
            timer.Interval = 30;
            timer.Tick += (ss, ee) =>
            {
                updateUI();
            };
            timer.Start();
        }

        private void updateUI()
        {
            if (m_mode == MODE.MULTI_MODE)
            {
                uiBlock1.updateUI();
                uiBlock2.updateUI();
                uiBlock3.updateUI();
                uiBlock4.updateUI();
                uiBlock5.updateUI();
                uiBlock6.updateUI();
                uiBlock7.updateUI();
                uiBlock8.updateUI();
            }
            else
            {
                uiBlock0.updateUI();
            }
        }

        public void changeMode()
        {
            m_mode = (m_mode == MODE.SINGLE_MODE) ? MODE.MULTI_MODE : MODE.SINGLE_MODE;
            tableLayoutPanel1.Visible = !tableLayoutPanel1.Visible;
            uiBlock0.Visible = !uiBlock0.Visible;
        }
        
        enum MODE { SINGLE_MODE, MULTI_MODE };
        MODE m_mode = MODE.MULTI_MODE;
    }
}