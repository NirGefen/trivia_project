using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaGUI
{
    public class ErrorResponse
    {
        public string message { get; set; }
    }
    public class LoginResponse
    {
        public uint status { get; set; }
    }
    public class SignupResponse
    {
        public uint status { get; set; }
    }
    public class LogoutResponse
    {
        public uint status { get; set; }
    }
    public class StatisticsResponse
    {
        public StatisticsObject user_stats { get; set; }
        public StatisticsObject[] highscores { get; set; }     
    }
    public class StatisticsObject
    {
        public double average_answer_time   { get; set; } 
        public int total_answers            { get; set; } 
        public int total_correct_answers    { get; set; } 
        public int total_games_played       { get; set; } 
        public int score                    { get; set; } 
        public string username              { get; set; }
    }
    public class CreateRoomResponse
    {
        public uint status { get; set; }
    }
    public class GetRoomsResponse
    {
        public RoomInfo[] room_list;
    }
    public class RoomInfo
    {
        public uint room_id { get; set; }
        public string room_name { get; set; }
        public string owner_username { get; set; }
        public uint max_players { get; set; }
        public double seconds_per_question { get; set; }
        public bool is_active { get; set; }
        public uint num_of_questions { get; set; }
    }
    public class JoinRoomResponse
    {
        public uint status { get; set; }
    }
    public class LeaveRoomResponse
    {
        public uint status { get; set; }
    }
    public class CloseRoomResponse
    {
        public uint status { get; set; }
    }
    public class GetPlayersInRoomResponse
    {
        public string[] room_player_list { get; set; }
    }
    public class GetRoomStateResponse
    {
        public RoomInfo room_data {get; set;}
        public string[] players { get; set; }
    }
    public class StartGameResponse
    {
        public uint status { get; set; }
    }
    public class LeaveGameResponse
    {
        public uint status { get; set; }
    }
    public class GetQuestionResponse
    {
        public uint status { get; set; }
        public string question { get; set; }
        public Answer[] answers { get; set; }
        public string category { get; set; }
    }
    public class Answer
    {
        public uint answer_id;
        public string answer;
    }
    public class SubmitAnswerResponse
    {
        public uint status { get; set; }
        public uint correct_answer_id { get; set; }
    }
    public class GetGameResultsResponse
    {
        public uint status { get; set; }
        public PlayerResults[] results { get; set; }
    }
    public class PlayerResults
    {
        public string username { get; set; }
        public uint correct_answer_count { get; set; }
        public uint wrong_answer_count { get; set; }
        public double average_answer_time { get; set; }
    }
}
