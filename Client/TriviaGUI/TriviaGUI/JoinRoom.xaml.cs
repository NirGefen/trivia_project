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
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        public JoinRoom()
        {
            InitializeComponent();
        }
        private void OnClickArrowBack(object sender, RoutedEventArgs e)
        {
            Globals.ShowMainWindow();
        }

        private void OnClickJoinRoom(object sender, RoutedEventArgs e)
        {
            if(this.RoomsList.SelectedIndex == -1)
            {
                MessageBox.Show("You haven't selected a room to join.");
            }
            else
            {
                JoinRoomResponse response = new JoinRoomResponse();
                RoomInfo requestedRoom = Globals.roomsList[this.RoomsList.SelectedIndex];
                try
                {
                    response = Globals.protocolManager.joinRoom(requestedRoom.room_id);
                }
                catch (Exception)
                {
                    return;
                }
                if (response.status == Constants.SUCCESS_CODE)
                {
                    Globals.currentRoomWindow = new Room();
                    Globals.connectedRoom = requestedRoom;
                    Globals.currentRoomWindow.SetupRoomDisplay(requestedRoom);
                    Globals.currentRoomWindow.Show();
                    Globals.ownsCurrentRoom = false;
                    this.Close();
                }
            }
        }

        private void OnSelectChanged(object sender, SelectionChangedEventArgs e)
        {
            if (this.RoomsList.SelectedIndex != -1)
            {
                GetPlayersInRoomResponse getPlayersResponse = new GetPlayersInRoomResponse();
                try
                {
                    getPlayersResponse = Globals.protocolManager.getPlayersInRoom(Globals.roomsList[this.RoomsList.SelectedIndex].room_id);
                }
                catch (Exception)
                {
                    return;
                }
                PlayersList.DataContext = null;
                PlayersList.Items.Clear();
                for (int i = 0; i < getPlayersResponse.room_player_list.Length; i++)
                {
                    PlayersList.Items.Add(getPlayersResponse.room_player_list[i]);
                }
            }
        }
    }
}
