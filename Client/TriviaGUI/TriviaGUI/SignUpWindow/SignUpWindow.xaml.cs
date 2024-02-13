using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Runtime.InteropServices;

namespace TriviaGUI
{
    /// <summary>
    /// Interaction logic for SignUpWindow.xaml
    /// </summary>
    public partial class SignUpWindow : Window
    {
        public SignUpWindow()
        {
            InitializeComponent();
        }
        private bool validRegistration()
        {
            if (MailInput.Text.Length < 3)
            {
                MessageBox.Show("Mail too short (3+ characters)");
                return false;
            }
            else if (UsernameInput.Text.Length < 1)
            {
                MessageBox.Show("Username too short (1+ characters)");
                return false;
            }
            else if (PasswordInput.Text.Length < 1)
            {
                MessageBox.Show("Password too short (1+ characters)");
                return false;
            }
            return true;
        }
        private void OnClickArrowBack(object sender, RoutedEventArgs e)
        {
            Globals.ShowMainWindow();
        }
    }
}
