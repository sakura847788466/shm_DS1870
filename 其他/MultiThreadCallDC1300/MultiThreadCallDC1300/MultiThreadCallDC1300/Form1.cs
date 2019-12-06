using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace MultiThreadCallDC1300
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        
        private void button5_Click(object sender, EventArgs e)
        {
            Thread t1 = new Thread(() =>
            {
                SetPrinterName();
            });
            t1.Start();
            MessageBox.Show("Thread 1 set printer name finish!");
            
        }
        private void SetPrinterName()
        {
            D300RWHelp.DASSetPrinterName("DC-1300@USB001", "D300C");
        }
        private int RejectCard()
        {
            return (int)D300RWHelp.DASRejectCard();
        }
        private void button6_Click(object sender, EventArgs e)
        {
            Thread t2 = new Thread(() =>
            {
                SetPrinterName();
            });
            t2.Start();
            MessageBox.Show("Thread 2 set printer name finish!");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Thread t1 = new Thread(() =>
            {
                int result = RejectCard();
                if (result == 0)
                {
                    MessageBox.Show("t1 RejectCard Success!");
                    return;
                }
                else
                {
                    MessageBox.Show("t1 RejectCard Failed!");
                    return;
                }
            });
            t1.Start();
            MessageBox.Show("Thread 1 reject card finish!");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Thread t2 = new Thread(() =>
            {
                int result = RejectCard();
                if (result == 0)
                {
                    MessageBox.Show("t2 RejectCard Success!");
                    return;
                }
                else
                {
                    MessageBox.Show("t2 RejectCard Failed!");
                    return;
                }
            });
            t2.Start();
            MessageBox.Show("Thread 2 reject card finish!");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int length = 1000;
            byte[] prtlist = new byte[length];
            uint result = D300RWHelp.DASEnumPrinter(prtlist, ref length, 3);
            if (result == 0)
            {
                string printList = Encoding.ASCII.GetString(prtlist, 0, length);
                string[] split = printList.Split('\n');
                for (int i = 0; i < split.Length; i++)
                {
                    cbBPrintName.Items.Add(split[i].Trim('\0'));
                }
                if (cbBPrintName.Items.Count > 0)
                {
                    cbBPrintName.SelectedIndex = 0;
                }
            }
            else
            {
                MessageBox.Show("Enum Failed!");
                return;
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASSetPrinterName(cbBPrintName.Text.Trim(), "D300RW");
            if (result == 0)
                MessageBox.Show("SetPrinterName Success!");
            else
                MessageBox.Show("SetPrinterName Failed!");
        }
    }
}
