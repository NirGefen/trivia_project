using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using System.Windows;
using System.Threading;
using System.Timers;

namespace TriviaGUI
{
    public class ProtocolManager
    {
        public SocketManager socketManager;
        public ProtocolManager()
        {
            this.socketManager = new SocketManager();
        }
        public void handleError(string jsonError)
        {
            MessageBox.Show(JsonConvert.DeserializeObject<ErrorResponse>(jsonError).message);
            throw new ResponseErrorReplyException();
        }
        public void handleUnexpectedHeader(uint badHeader)
        {
            MessageBox.Show("Unexpected header: " + badHeader.ToString());
            throw new ResponseUnexpectedErrorReplyException();
        }
        public LoginResponse login(string username, string password)
        {
            LoginResponse response = new LoginResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.LOGIN_REQUEST_CODE, JsonConvert.SerializeObject(new LoginRequest(username, password), Formatting.Indented));
            if(info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if(info.header == Constants.LOGIN_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<LoginResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public SignupResponse signup(string username, string password, string mail)
        {
            SignupResponse response = new SignupResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.SIGNUP_REQUEST_CODE, JsonConvert.SerializeObject(new SignupRequest(username, password, mail), Formatting.Indented));
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.SIGNUP_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<SignupResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public LogoutResponse logout()
        {
            LogoutResponse response = new LogoutResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.LOGOUT_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.LOGOUT_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<LogoutResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public LeaveRoomResponse leaveRoom()
        {
            LeaveRoomResponse response = new LeaveRoomResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.LEAVE_ROOM_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.LEAVE_ROOM_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<LeaveRoomResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public CloseRoomResponse closeRoom()
        {
            CloseRoomResponse response = new CloseRoomResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.CLOSE_ROOM_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.CLOSE_ROOM_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<CloseRoomResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public StatisticsResponse statistics()
        {
            StatisticsResponse response = new StatisticsResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.STATISTICS_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.STATISTICS_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<StatisticsResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public CreateRoomResponse createRoom(string roomName, uint maxUsers, uint questionCount, double answerTimeout)
        {
            CreateRoomResponse response = new CreateRoomResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.CREATE_ROOM_REQUEST_CODE, JsonConvert.SerializeObject(new CreateRoomRequest(roomName, maxUsers, questionCount, answerTimeout), Formatting.Indented));
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.CREATE_ROOM_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<CreateRoomResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public GetRoomsResponse getRooms()
        {
            GetRoomsResponse response = new GetRoomsResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.GET_ROOMS_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.GET_ROOMS_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<GetRoomsResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public JoinRoomResponse joinRoom(uint roomId)
        {
            JoinRoomResponse response = new JoinRoomResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.JOIN_ROOM_REQUEST_CODE, JsonConvert.SerializeObject(new JoinRoomRequest(roomId), Formatting.Indented));
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.JOIN_ROOM_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<JoinRoomResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public GetPlayersInRoomResponse getPlayersInRoom(uint roomId)
        {
            GetPlayersInRoomResponse response = new GetPlayersInRoomResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.GET_PLAYERS_IN_ROOM_REQUEST_CODE, JsonConvert.SerializeObject(new GetPlayersInRoomRequest(roomId), Formatting.Indented));
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.GET_PLAYERS_IN_ROOM_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public GetRoomStateResponse updateRoom()
        {
            GetRoomStateResponse response = null;
            ResponseInfo info = socketManager.getResponseForRequest(Constants.GET_ROOM_STATE_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.GET_ROOM_STATE_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<GetRoomStateResponse>(info.json);
            }
            else if(info.header == Constants.LEAVE_ROOM_RESPONSE_CODE)
            {
                Application.Current.Dispatcher.Invoke((Action)delegate 
                {
                    Globals.currentRoomWindow.shouldThreadRun = false;
                    Globals.ShowMainWindow();
                    MessageBox.Show("Your room has been closed.");
                });
            }
            else if(info.header == Constants.START_GAME_RESPONSE_CODE)
            {
                Globals.currentRoomWindow.Dispatcher.Invoke(() =>
                {
                    Globals.currentRoomWindow.shouldThreadRun = false;
                });
                Application.Current.Dispatcher.Invoke((Action)delegate 
                {
                    Globals.currentGameWindow = new GameWindow();
                    Globals.questionsAnswered = 0;
                    Globals.correctAnswers = 0;
                    Globals.currentGameWindow.RoomName.Content = Globals.connectedRoom.room_name;
                    Globals.currentGameWindow.HideWaitingLabel();

                    this.getQuestionAndUpdate();

                    Globals.currentGameWindow.Show();
                    Globals.currentRoomWindow.Dispatcher.Invoke(() =>
                    {
                        Globals.currentRoomWindow.Close();
                    });
                });
                
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public StartGameResponse startGame()
        {
            StartGameResponse response = new StartGameResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.START_GAME_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.START_GAME_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<StartGameResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public SubmitAnswerResponse submitAnswer(uint answerId)
        {
            SubmitAnswerResponse response = new SubmitAnswerResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.SUBMIT_ANSWER_REQUEST_CODE, JsonConvert.SerializeObject(new SubmitAnswerRequest(answerId), Formatting.Indented));
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.SUBMIT_ANSWER_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<SubmitAnswerResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public LeaveGameResponse leaveGame()
        {
            LeaveGameResponse response = new LeaveGameResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.LEAVE_GAME_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.LEAVE_GAME_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<LeaveGameResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public GetQuestionResponse getQuestion()
        {
            GetQuestionResponse response = new GetQuestionResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.GET_QUESTION_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.GET_QUESTION_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<GetQuestionResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public GetGameResultsResponse getGameResults()
        {
            // TODO: change GET_ROOMS_REQUEST_CODE and GET_ROOMS_RESPONSE_CODE and function's purpose
            GetGameResultsResponse response = new GetGameResultsResponse();
            ResponseInfo info = socketManager.getResponseForRequest(Constants.GET_GAME_RESULTS_REQUEST_CODE, "");
            if (info.header == Constants.ERROR_RESPONSE_CODE)
            {
                handleError(info.json);
            }
            else if (info.header == Constants.GET_GAME_RESULTS_RESPONSE_CODE)
            {
                response = JsonConvert.DeserializeObject<GetGameResultsResponse>(info.json);
            }
            else
            {
                handleUnexpectedHeader(info.header);
            }
            return response;
        }
        public void getQuestionAndUpdate()
        {
            GetQuestionResponse questionResponse = new GetQuestionResponse();
            try
            {
                questionResponse = Globals.protocolManager.getQuestion();
            }
            catch (Exception)
            {
                return;
            }
            if (questionResponse.status == Constants.SUCCESS_CODE)
            {
                Globals.timeLeft = (int)Globals.connectedRoom.seconds_per_question;

                Globals.currentGameWindow.answerTimer = new System.Timers.Timer(1000);
                Globals.currentGameWindow.answerTimer.Elapsed += Globals.currentGameWindow.CallBackAnswerNoTime;
                Globals.currentGameWindow.answerTimer.AutoReset = true;
                Globals.currentGameWindow.answerTimer.Enabled = true;

                Globals.currentGameWindow.Dispatcher.Invoke(() =>
                {
                    Globals.currentGameWindow.Category.Text = questionResponse.category;
                    Globals.currentGameWindow.setTimeLeft(Globals.timeLeft);
                    Globals.currentGameWindow.setCorrectAnswers(Globals.correctAnswers);
                    Globals.currentGameWindow.setQuestion(questionResponse.question);
                    Globals.currentGameWindow.setQuestionCount(Globals.questionsAnswered + 1, Globals.connectedRoom.num_of_questions);
                    Globals.currentGameWindow.setAnswers(questionResponse.answers);
                });
            }
            else
            {
                return;
            }
        }
    }
}
