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
using System.Threading;

namespace TriviaGUI
{
    /// <summary>
    /// Interaction logic for SignUpWindow.xaml
    /// </summary>
    public partial class Room : Window
    {
        private Thread updateThread;
        public bool shouldThreadRun;
        private static Mutex updateMutex = new Mutex();
        public Room()
        {
            InitializeComponent();
            Globals.currentRoomWindow = this;
            shouldThreadRun = true;
            updateThread = new Thread(new ThreadStart(updateThreadFunction));
            updateThread.Start();
        }
        public void updateThreadFunction()
        {
            while (shouldThreadRun)
            {
                GetRoomStateResponse response = new GetRoomStateResponse();
                try
                {
                    updateMutex.WaitOne();
                    response = Globals.protocolManager.updateRoom();

                    if (response != null)
                    {
                        this.Dispatcher.Invoke(() =>
                        {
                            PlayersList.DataContext = null; // clear players list
                            PlayersList.Items.Clear();
                            PlayersList.Items.Add(response.room_data.owner_username); // add the owner first
                            for (int i = 0; i < response.players.Length; i++)
                            {
                                if(response.players[i] != response.room_data.owner_username) // if not owner, add
                                {
                                    PlayersList.Items.Add(response.players[i]);
                                }
                            }
                        });
                    }
                }
                catch (Exception)
                {
                    updateMutex.ReleaseMutex();
                    return;
                }
                updateMutex.ReleaseMutex();
                Thread.Sleep(3000);
            }
        }
        private void OnClickArrowBack(object sender, RoutedEventArgs e)
        {
            updateMutex.WaitOne();
            if (Globals.ownsCurrentRoom)
            {
                CloseRoomResponse response = new CloseRoomResponse();
                try
                {
                    response = Globals.protocolManager.closeRoom();
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
                    MessageBox.Show("Close room error");
                }
            }
            else
            {
                LeaveRoomResponse response = new LeaveRoomResponse();
                try
                {
                    response = Globals.protocolManager.leaveRoom();
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
                    MessageBox.Show("Leave room error");
                }
            }
            shouldThreadRun = false;
            updateMutex.ReleaseMutex();
        }
        private void OnClickStartGame(object sender, RoutedEventArgs e)
        {
            StartGameResponse response = new StartGameResponse();
            try
            {
                response = Globals.protocolManager.startGame();
            }
            catch (Exception)
            {
                return;
            }
            if (response.status == Constants.SUCCESS_CODE)
            {
                Room roomWindow = (Room)Application.Current.Windows[0];
                roomWindow.Dispatcher.Invoke(() =>
                {
                    roomWindow.shouldThreadRun = false;
                });
                Globals.currentGameWindow = new GameWindow();
                Globals.questionsAnswered = 0;
                Globals.correctAnswers = 0;
                Globals.currentGameWindow.RoomName.Content = Globals.connectedRoom.room_name;
                Globals.currentGameWindow.HideWaitingLabel();

                Globals.protocolManager.getQuestionAndUpdate();

                Globals.currentGameWindow.Show();
                roomWindow.Dispatcher.Invoke(() =>
                {
                    roomWindow.Close();
                });
            }
            else
            {
                MessageBox.Show("Start game error");
            }
        }
        public void SetupRoomDisplay(RoomInfo roomInfo)
        {
            Title.Content = "Room: " + roomInfo.room_name;
            MaxPlayersText.Content = "Max players:\t\t" + roomInfo.max_players;
            QuestionsText.Content = "Questions\t\t" + roomInfo.num_of_questions;
            TimePerQuestionText.Content = "Time Per Question\t" + roomInfo.seconds_per_question;

            StartGameButton.Visibility = Visibility.Hidden;
            if(Globals.loggedUser.username == roomInfo.owner_username)
            {
                StartGameButton.Visibility = Visibility.Visible;
            }
        }
    }
}
