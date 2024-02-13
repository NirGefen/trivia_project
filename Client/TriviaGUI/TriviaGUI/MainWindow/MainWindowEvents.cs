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

namespace TriviaGUI
{
    public partial class MainWindow : Window
    {
        private void OnClickSignIn(object sender, RoutedEventArgs e)
        {
            string username = UsernameInput.Text, password = PasswordInput.Text;
            LoginResponse response = new LoginResponse();
            try
            {
                response = Globals.protocolManager.login(username, password);
            }
            catch (Exception)
            {
                return;
            }
            if (response.status == Constants.SUCCESS_CODE)
            {
                HideSignInDisplay();
                EnableButtons();
                ShowSignOutButton();
                Globals.loggedUser.username = username;
                Globals.loggedUser.password = password;
            }
            else
            {
                MessageBox.Show("Username/password are invalid, or user is logged in.");
            }
        }

        private void OnClickSignOut(object sender, RoutedEventArgs e)
        {
            LogoutResponse response = new LogoutResponse();
            try
            {
                response = Globals.protocolManager.logout();
            }
            catch (Exception)
            {
                return;
            }
            if (response.status == Constants.SUCCESS_CODE)
            {
                DisableButtons();
                ShowSignInDisplay();
                HideSignOutButton();
                Globals.loggedUser.username = "";
            }
            else
            {
                MessageBox.Show("Logout Error");
            }
        }

        private void OnClickCreateRoom(object sender, RoutedEventArgs e)
        {
            CreateRoom newWindow = new CreateRoom();
            newWindow.Show();
            this.Close();
        }

        private void OnClickHighscores(object sender, RoutedEventArgs e)
        {
            Highscores newWindow = new Highscores();
            StatisticsResponse response = new StatisticsResponse();
            try
            {
                response = Globals.protocolManager.statistics();
            }
            catch (Exception)
            {
                return;
            }
            for(int i = 0; i < response.highscores.Length; i++)
            {
                newWindow.PlayersList.Items.Add(response.highscores[i].username + "\t\t" + response.highscores[i].score);
            }

            newWindow.Show();
            this.Close();
        }

        private void OnClickStatistics(object sender, RoutedEventArgs e)
        {
            Statistics statisticsWindow = new Statistics();
            statisticsWindow.UserName.Content = Globals.loggedUser.username;

            StatisticsResponse response = new StatisticsResponse();
            try
            {
                response = Globals.protocolManager.statistics();
            }
            catch (Exception)
            {
                return;
            }
            statisticsWindow.displayStatistics(response.user_stats);
            statisticsWindow.Show();
            this.Close();
        }

        private void OnClickJoinRoom(object sender, RoutedEventArgs e)
        {
            GetRoomsResponse response = new GetRoomsResponse();
            try
            {
                response = Globals.protocolManager.getRooms();
            }
            catch (Exception)
            {
                return;
            }
            Globals.roomsList = response.room_list;
            JoinRoom roomsWindow = new JoinRoom();
            foreach(RoomInfo room in response.room_list)
            {
                ListViewItem item = new ListViewItem();
                item.Content = room.room_name;
                if (room.is_active)
                {
                    item.Foreground = Brushes.Red;
                }
                else
                {
                    item.Background = Brushes.LightGreen;
                }
                roomsWindow.RoomsList.Items.Add(item);
            }
            roomsWindow.Show();
            this.Close();
        }

        private void OnClickSignUp(object sender, RoutedEventArgs e)
        {
            SignUpWindow newWindow = new SignUpWindow();
            newWindow.Show();
            this.Close();
        }

        private void OnClickQuit(object sender, RoutedEventArgs e)
        {
            Environment.Exit(1);
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
