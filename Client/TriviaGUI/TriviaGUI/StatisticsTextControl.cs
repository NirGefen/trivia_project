using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace TriviaGUI
{
    public partial class Statistics : Window
    {
        public void displayStatistics(StatisticsObject info)
        {
            GamesPlayed.Content = "Games Played\t\t" + info.total_games_played;
            CorrectAnswers.Content = "Correct Answers\t\t" + info.total_correct_answers;
            TotalAnswers.Content = "Total Answers\t\t" + info.total_answers;
            AverageAnswerTime.Content = "Average Answer Time\t" + String.Format("{0:0.00}", info.average_answer_time); // show only 2 digits after the dot
            Score.Content = "Score\t\t\t\t" + info.score;
        }      
    }
}
