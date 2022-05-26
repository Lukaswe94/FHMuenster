using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace swaPra3
{
    /// <summary>
    /// Interaktionslogik für Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        public Window1()
        {
            InitializeComponent();
        }

        private void btn_del_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btn_change_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btn_reg_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btn_ChangeWindow_Click(object sender, RoutedEventArgs e)
        {
            MainWindow Mw = new MainWindow();
            Mw.Show();
            this.Close();
        }

        private void btn_ChangeWindow2_Click(object sender, RoutedEventArgs e)
        {
            btn_ChangeWindow_Click(sender,e);
        }
    }
}
