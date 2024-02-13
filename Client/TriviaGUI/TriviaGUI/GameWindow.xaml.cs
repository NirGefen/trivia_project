using System;
using System.Collections;
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
using System.Timers;

namespace TriviaGUI
{
    /// <summary>
    /// Interaction logic for SignUpWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        public Answer[] answers;
        public Button[] buttons;
        public System.Timers.Timer answerTimer;

        private Thread updateThread;
        public bool shouldThreadRun;
        private static Mutex updateMutex = new Mutex();
        public bool canPressButtons = true;
        public GameWindow()
        {
            InitializeComponent();
            this.answers = new Answer[4];
            this.buttons = new Button[4];
            this.buttons[0] = this.AnswerOne;
            this.buttons[1] = this.AnswerTwo;
            this.buttons[2] = this.AnswerThree;
            this.buttons[3] = this.AnswerFour;
        }
        private void OnClickArrowBack(object sender, RoutedEventArgs e)
        {
            updateMutex.WaitOne();
            LeaveGameResponse response = new LeaveGameResponse();
            try
            {
                response = Globals.protocolManager.leaveGame();
            }
            catch (Exception)
            {
                updateMutex.ReleaseMutex();
                this.answerTimer.Stop();
                this.answerTimer.Dispose();
                return;
            }
            if (response.status == Constants.SUCCESS_CODE)
            {
                this.shouldThreadRun = false;
                updateMutex.ReleaseMutex();
                this.answerTimer.Stop();
                this.answerTimer.Dispose();
                Globals.ShowMainWindow();
            }
            else
            {
                this.answerTimer.Stop();
                this.answerTimer.Dispose();
                updateMutex.ReleaseMutex();
                return;
            }
        }

        private void OnClickAnswerOne(object sender, RoutedEventArgs e)
        {
            if(this.canPressButtons)
            {
                this.answerTimer.Stop();
                this.answerTimer.Dispose();
                this.submitAnswer(this.answers[0].answer_id);
            }
        }

        private void OnClickAnswerTwo(object sender, RoutedEventArgs e)
        {
            if (this.canPressButtons)
            {
                this.answerTimer.Stop();
                this.answerTimer.Dispose();
                this.submitAnswer(this.answers[1].answer_id);
            }
        }

        private void OnClickAnswerThree(object sender, RoutedEventArgs e)
        {
            if (this.canPressButtons)
            {
                this.answerTimer.Stop();
                this.answerTimer.Dispose();
                this.submitAnswer(this.answers[2].answer_id);
            }
        }

        private void OnClickAnswerFour(object sender, RoutedEventArgs e)
        {
            if (this.canPressButtons)
            {
                this.answerTimer.Stop();
                this.answerTimer.Dispose();
                this.submitAnswer(this.answers[3].answer_id);
            }
        }

        public void setCorrectAnswers(uint answers)
        {
            this.CorrectAnswers.Content = "Correct Answers:\t" + answers;
        }
        public void setTimeLeft(int seconds)
        {
            this.TimeLeft.Content = "Time Left:\t" + seconds;
        }
        public void setQuestion(string question)
        {
            this.Question.Text = System.Net.WebUtility.HtmlDecode(question);
        }
        public void setQuestionCount(uint currentQuestion, uint maxQuestions)
        {
            this.QuestionCount.Content = "Question " + currentQuestion + "/" + maxQuestions;
        }
        public void setAnswers(Answer[] answers)
        {
            this.Dispatcher.Invoke(() =>
            {
                var bc = new BrushConverter();
                for (int i = 0; i < this.buttons.Length; i++)
                {
                    buttons[i].Background = (Brush)bc.ConvertFrom("#FF00AEFF");

                }
            });
            for (int i = 0; i < answers.Length; i++)
            {
                this.answers[i] = answers[i];
                this.buttons[i].Content = System.Net.WebUtility.HtmlDecode(answers[i].answer);
            }
        }
        public async void submitAnswer(uint answerId)
        {
            SubmitAnswerResponse response = new SubmitAnswerResponse();
            try
            {
                response = Globals.protocolManager.submitAnswer(answerId);
            }
            catch (Exception)
            {
                return;
            }
            Globals.questionsAnswered++;
            highlightAnswers(response.correct_answer_id);
            await Task.Delay(1500);
            if (response.status == Constants.SUCCESS_CODE && response.correct_answer_id == answerId) // add to correct answers
            {
                Globals.correctAnswers++;
            }
            else if(response.status == Constants.SUCCESS_CODE && response.correct_answer_id != answerId)
            {
                this.Dispatcher.Invoke(() =>
                {
                    this.setQuestion("Wrong answer!");
                });
            }
            else
            {
                this.Dispatcher.Invoke(() =>
                {
                    this.setQuestion("Answer not in time!");
                });
            }
            await Task.Delay(1000); // wait so user can see if answer not in time or wrong
            this.canPressButtons = true;
            if (Globals.connectedRoom.num_of_questions <= Globals.questionsAnswered) // finished game
            {
                updateThread = new Thread(new ThreadStart(updateThreadFunction));
                this.shouldThreadRun = true;
                updateThread.Start();
            }
            else
            {
                Globals.protocolManager.getQuestionAndUpdate();
            }
        }
        public async void highlightAnswers(uint correctAnswerId)
        {
            this.Dispatcher.Invoke(() =>
            {
                this.canPressButtons = false;

                var bc = new BrushConverter();

                for (int i = 0; i < this.buttons.Length; i++)
                {
                    if (answers[i].answer_id == correctAnswerId)
                    {
                        buttons[i].Background = (Brush)bc.ConvertFrom("#FF02FF13");
                    }
                    else
                    {
                        buttons[i].Background = (Brush)bc.ConvertFrom("#FFFF0000");
                    }
                }
            });
            await Task.Delay(1500);
            this.Dispatcher.Invoke(() =>
            {
                var bc = new BrushConverter();
                for (int i = 0; i < this.buttons.Length; i++)
                {
                    buttons[i].Background = (Brush)bc.ConvertFrom("#FF00AEFF");
                    
                }
            });
        }
        public void CallBackAnswerNoTime(Object source, ElapsedEventArgs e)
        {
            Globals.timeLeft--;
            if(Globals.timeLeft <= 0) // ran out of time
            {
                this.answerTimer.Stop();
                this.answerTimer.Dispose();
                this.submitAnswer(this.answers[0].answer_id); // submit an answer, doesnt matter as time ran out. we do this just to get the correct answer id
            }
            else
            {
                this.Dispatcher.Invoke(() =>
                {
                    setTimeLeft(Globals.timeLeft);
                });
            }
        }
        public void ShowWaitingLabel()
        {
            this.Dispatcher.Invoke(() =>
            {
                this.WaitingLabel.Visibility = Visibility.Visible;

                this.RoomName.Visibility = Visibility.Hidden;
                this.QuestionCount.Visibility = Visibility.Hidden;
                this.Question.Visibility = Visibility.Hidden;

                for (int i = 0; i < this.buttons.Length; i++)
                {
                    this.buttons[i].Visibility = Visibility.Hidden;
                }

                this.CorrectAnswers.Visibility = Visibility.Visible;
                this.TimeLeft.Visibility = Visibility.Hidden;
                this.Category.Visibility = Visibility.Hidden;

                this.ArrowBack.Visibility = Visibility.Visible;
            });
        }
        public void HideWaitingLabel()
        {
            this.WaitingLabel.Visibility = Visibility.Hidden;

            this.RoomName.Visibility = Visibility.Visible;
            this.QuestionCount.Visibility = Visibility.Visible;
            this.Question.Visibility = Visibility.Visible;
            
            for(int i = 0; i < this.buttons.Length; i++)
            {
                this.buttons[i].Visibility = Visibility.Visible;
            }

            this.CorrectAnswers.Visibility = Visibility.Visible;
            this.TimeLeft.Visibility = Visibility.Visible;

            this.ArrowBack.Visibility = Visibility.Visible;
        }
        public void updateThreadFunction()
        {
            while (shouldThreadRun)
            {
                GetGameResultsResponse response = new GetGameResultsResponse();
                try
                {
                    updateMutex.WaitOne();
                    response = Globals.protocolManager.getGameResults();

                    if (response.status == Constants.SUCCESS_CODE)
                    {
                        this.Dispatcher.Invoke(() =>
                        {
                            this.shouldThreadRun = false;
                            EndGameWindow endWindow = new EndGameWindow();

                            for (int i = 0; i < response.results.Length; i++)
                            {
                                Array.Sort(response.results, (x, y) => (int)(y.correct_answer_count - x.correct_answer_count));
                            }

                            foreach(PlayerResults results in response.results)
                            {
                                endWindow.ResultsList.Items.Add(results.username + "\t"
                                    + "Correct Answers: " + results.correct_answer_count + "\n"
                                    + "Wrong Answers: " + results.wrong_answer_count + "\t"
                                    + "Average Answer Time: " + String.Format("{0:0.00}", results.average_answer_time));
                            }

                            endWindow.Show();
                            this.Close();
                        });
                    }
                    else
                    {
                        ShowWaitingLabel();
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
    }
}
