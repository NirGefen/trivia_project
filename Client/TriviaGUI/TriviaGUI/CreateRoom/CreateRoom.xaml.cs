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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        public CreateRoom()
        {
            InitializeComponent();
        }
        private bool validCreateRoom()
        {
            if (RoomNameInput.Text.Length < 1 || RoomNameInput.Text.Length > 24)
            {
                MessageBox.Show("Room name length can be between 1 and 24 characters.");
                return false;
            }
            else if(!Globals.IsANumber(NumOfPlayersInput.Text) 
                    || !Globals.IsANumber(NumOfQuestionsInput.Text) 
                    || !Globals.IsANumber(TimeForQuestionInput.Text))
            {
                MessageBox.Show("Number of players/questions and time per question must be a number.");
                return false;
            }
            else if (int.Parse(NumOfPlayersInput.Text) < 1 || int.Parse(NumOfPlayersInput.Text) > 9)
            {
                MessageBox.Show("Number of players can be between 1 and 9 players.");
                return false;
            }
            else if (int.Parse(NumOfQuestionsInput.Text) < 1 || int.Parse(NumOfQuestionsInput.Text) > 99)
            {
                MessageBox.Show("Number of questions can be between 1 and 99 questions.");
                return false;
            }
            else if (int.Parse(TimeForQuestionInput.Text) < 1 || int.Parse(TimeForQuestionInput.Text) > 99)
            {
                MessageBox.Show("Time per question can be between 1 and 99 seconds.");
                return false;
            }
            return true;
        }
    }
}
