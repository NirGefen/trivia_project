using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using TriviaGUI;

namespace TriviaGUI
{
    using Account = LoginRequest;
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public static class Globals
    {
        public static ProtocolManager protocolManager;
        public static Account loggedUser = new Account("", "");
        public static RoomInfo[] roomsList;
        public static RoomInfo connectedRoom;
        public static GameWindow currentGameWindow;
        public static Room currentRoomWindow;
        public static uint questionsAnswered;
        public static uint correctAnswers;
        public static bool ownsCurrentRoom;
        public static int timeLeft;
        public static bool timerRunning = false;
        public static void ShowMainWindow()
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.Show();
            Application.Current.Windows[0].Close(); // closes current window
        }
        public static bool IsANumber(string s)
        {
            int i = 0;
            return int.TryParse(s, out i);
        }
    }
    public static class Constants
    {
        public const int SUCCESS_CODE = 1;
        public const int TIMEOUT_ANSWER_CODE = 2;

        public const int FAIL_CODE = 0;
        public const int LOGIN_REQUEST_CODE = 1;
        public const int SIGNUP_REQUEST_CODE = 2;
        public const int LOGOUT_REQUEST_CODE = 3;
        public const int GET_ROOMS_REQUEST_CODE = 4;
        public const int GET_PLAYERS_IN_ROOM_REQUEST_CODE = 5;
        public const int JOIN_ROOM_REQUEST_CODE = 6;
        public const int CREATE_ROOM_REQUEST_CODE = 7;
        public const int STATISTICS_REQUEST_CODE = 8;
        public const int GET_ROOM_STATE_REQUEST_CODE = 9;
        public const int LEAVE_ROOM_REQUEST_CODE = 10;
        public const int CLOSE_ROOM_REQUEST_CODE = 11;
        public const int START_GAME_REQUEST_CODE = 12;
        public const int LEAVE_GAME_REQUEST_CODE = 13;
        public const int GET_QUESTION_REQUEST_CODE = 14;
        public const int SUBMIT_ANSWER_REQUEST_CODE = 15;
        public const int GET_GAME_RESULTS_REQUEST_CODE = 16;

        public const int LOGIN_RESPONSE_CODE = 129;
        public const int SIGNUP_RESPONSE_CODE = 130;
        public const int LOGOUT_RESPONSE_CODE = 131;
        public const int GET_ROOMS_RESPONSE_CODE = 132;
        public const int GET_PLAYERS_IN_ROOM_RESPONSE_CODE = 133;
        public const int JOIN_ROOM_RESPONSE_CODE = 134;
        public const int CREATE_ROOM_RESPONSE_CODE = 135;
        public const int STATISTICS_RESPONSE_CODE = 136;
        public const int GET_ROOM_STATE_RESPONSE_CODE = 137;
        public const int LEAVE_ROOM_RESPONSE_CODE = 138;
        public const int CLOSE_ROOM_RESPONSE_CODE = 139;
        public const int START_GAME_RESPONSE_CODE = 140;
        public const int LEAVE_GAME_RESPONSE_CODE = 141;
        public const int GET_QUESTION_RESPONSE_CODE = 142;
        public const int SUBMIT_ANSWER_RESPONSE_CODE = 143;
        public const int GET_GAME_RESULTS_RESPONSE_CODE = 144;
        public const int ERROR_RESPONSE_CODE = 255;

        public const int RESPONSE_CODE_INDEX = 0;
        public const int JSON_DATA_INDEX = 5;
    }
    public partial class App : Application
    {
        public App()
        {
            Globals.protocolManager = new ProtocolManager();
        }
    }
}
