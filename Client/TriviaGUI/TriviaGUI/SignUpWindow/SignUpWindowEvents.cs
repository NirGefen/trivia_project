using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace TriviaGUI
{
    public partial class SignUpWindow : Window
    {
        private void OnClickSignUpUser(object sender, RoutedEventArgs e)
        {
            if (validRegistration())
            {
                string username = UsernameInput.Text, password = PasswordInput.Text, mail = MailInput.Text;
                SignupResponse response = new SignupResponse();
                try
                {
                    response = Globals.protocolManager.signup(username, password, mail);
                }
                catch (Exception)
                {
                    return;
                }
                if (response.status == Constants.SUCCESS_CODE)
                {
                    Globals.ShowMainWindow();
                }
                else
                {
                    MessageBox.Show("Invalid registration or user exists\n\nTry a different username");
                }
            }

        }
        private void OnFocusMail(object sender, RoutedEventArgs e)
        {
            if (MailInput.Text == "Enter mail here")
            {
                MailInput.Text = "";
            }
        }

        private void OnLostFocusMail(object sender, RoutedEventArgs e)
        {
            if (MailInput.Text == "")
            {
                MailInput.Text = "Enter mail here";
            }
        }

        private void OnFocusUsername(object sender, RoutedEventArgs e)
        {
            if (UsernameInput.Text == "Enter username here")
            {
                UsernameInput.Text = "";
            }
        }

        private void OnLostFocusUsername(object sender, RoutedEventArgs e)
        {
            if (UsernameInput.Text == "")
            {
                UsernameInput.Text = "Enter username here";
            }
        }

        private void OnFocusPassword(object sender, RoutedEventArgs e)
        {
            if (PasswordInput.Text == "Enter password here")
            {
                PasswordInput.Text = "";
            }
        }

        private void OnLostFocusPassword(object sender, RoutedEventArgs e)
        {
            if (PasswordInput.Text == "")
            {
                PasswordInput.Text = "Enter password here";
            }
        }
    }
}
