using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaGUI
{
    public class LoginRequest
    {
        public string username { get; set; }
        public string password { get; set; }
        public LoginRequest(string username, string password)
        {
            this.username = username;
            this.password = password;
        }
    }
    public class SignupRequest
    {
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }
        public SignupRequest(string username, string password, string mail)
        {
            this.username = username;
            this.password = password;
            this.email = mail;
        }
    }
    public class StatisticsRequest
    {

    }
    public class GetRoomsRequest
    {

    }
    public class LeaveRoomRequest
    {

    }
    public class CloseRoomRequest
    {

    }
    public class CreateRoomRequest
    {
        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, double answerTimeout)
        {
            this.room_name = roomName;
            this.max_users = maxUsers;
            this.question_count = questionCount;
            this.answer_timeout = answerTimeout;
        }
        public string room_name { get; set; }
        public uint max_users { get; set; }
        public uint question_count { get; set; }
        public double answer_timeout { get; set; }
    }
    public class JoinRoomRequest
    {
        public uint room_id { get; set; }
        public JoinRoomRequest(uint roomId)
        {
            this.room_id = roomId;
        }
    }
    public class GetPlayersInRoomRequest
    {
        public uint room_id { get; set; }
        public GetPlayersInRoomRequest(uint roomId)
        {
            this.room_id = roomId;
        }
    }
    public class GetRoomStateRequest
    {

    }
    public class StartGameRequest
    {

    }
    public class LeaveGameRequest
    {

    }
    public class GetQuestionRequest
    {

    }
    public class GetGameResultsRequest
    {

    }
    public class SubmitAnswerRequest
    {
        public SubmitAnswerRequest(uint answerId)
        {
            this.answer_id = answerId;
        }
        public uint answer_id { get; set; }
    }
}
