using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace TriviaGUI
{
    public partial class MainWindow : Window
    {
        private void DisableButtons()
        {
            CreateRoomButton.IsEnabled = false;
            StatisticsButton.IsEnabled = false;
            HighscoresButton.IsEnabled = false;
            JoinRoomButton.IsEnabled = false;
            SignOutButton.IsEnabled = false;
        }
        public void EnableButtons()
        {
            CreateRoomButton.IsEnabled = true;
            StatisticsButton.IsEnabled = true;
            HighscoresButton.IsEnabled = true;
            JoinRoomButton.IsEnabled = true;
            SignOutButton.IsEnabled = true;
        }
        private void ShowSignInDisplay()
        {
            UsernameText.Content = "Username";
            PasswordText.Content = "Password";
            UsernameInput.Visibility = Visibility.Visible;
            PasswordInput.Visibility = Visibility.Visible;
            SignInButton.Visibility = Visibility.Visible;
        }

        private void HideSignInDisplay()
        {
            UsernameText.Content = "";
            PasswordText.Content = "";
            UsernameInput.Visibility = Visibility.Hidden;
            PasswordInput.Visibility = Visibility.Hidden;
            SignInButton.Visibility = Visibility.Hidden;
        }

        private void HideSignOutButton()
        {
            SignOutButton.Visibility = Visibility.Hidden;
        }
        private void ShowSignOutButton()
        {
            SignOutButton.Visibility = Visibility.Visible;
        }
    }
}
