using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace TriviaGUI
{
    public partial class CreateRoom : Window
    {
        public void OnClickArrowBack(object sender, RoutedEventArgs e)
        {
            Globals.ShowMainWindow();
        }

        public void OnClickCreateRoom(object sender, RoutedEventArgs e)
        {
            if (validCreateRoom())
            {
                CreateRoomResponse response = new CreateRoomResponse();
                try
                {
                    response = Globals.protocolManager.createRoom(this.RoomNameInput.Text, Convert.ToUInt32(this.NumOfPlayersInput.Text), Convert.ToUInt32(this.NumOfQuestionsInput.Text), Convert.ToDouble(this.TimeForQuestionInput.Text));
                }
                catch (Exception)
                {
                    return;
                }
                if (response.status == Constants.SUCCESS_CODE)
                {
                    RoomInfo roomInfo = new RoomInfo();
                    roomInfo.owner_username = Globals.loggedUser.username;
                    roomInfo.room_name = this.RoomNameInput.Text;
                    roomInfo.max_players = Convert.ToUInt32(this.NumOfPlayersInput.Text);
                    roomInfo.num_of_questions = Convert.ToUInt32(this.NumOfQuestionsInput.Text);
                    roomInfo.seconds_per_question = Convert.ToDouble(this.TimeForQuestionInput.Text);
                    Globals.connectedRoom = roomInfo;
                    Globals.currentRoomWindow = new Room();
                    Globals.currentRoomWindow.SetupRoomDisplay(roomInfo);
                    Globals.currentRoomWindow.ArrowBack.Content = "Close Room";
                    Globals.currentRoomWindow.ArrowBack.Width = 201.197;
                    Globals.currentRoomWindow.Show();
                    Globals.currentRoomWindow.PlayersList.Items.Add(Globals.loggedUser.username);
                    Globals.ownsCurrentRoom = true;
                    this.Close();
                }
                else
                {
                    MessageBox.Show("Create room failed. Check your fields and try again.");
                }
            }
        }
    }
}
