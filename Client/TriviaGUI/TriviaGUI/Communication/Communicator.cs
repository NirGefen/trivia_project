using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using System.ComponentModel;
using System.Windows;

namespace TriviaGUI
{
    public class Communicator
    {
        public TcpClient client;
        public IPEndPoint serverEndPoint;
        public NetworkStream clientStream;
        //private BackgroundWorker worker;

        public Communicator()
        {
            /*this.worker = new BackgroundWorker();
            this.worker.DoWork += SetupConnectionAndHandshake;
            worker.RunWorkerAsync();*/
            SetupConnectionAndHandshake();
        }
        private void SetupConnectionAndHandshake(object sender = null, DoWorkEventArgs e = null)
        {
            bool connectSuccess = false;
            bool shouldContinue = true;
            bool triedAgain = false;
            const int PORT = 6969;
            const string HOST = "127.0.0.1";
            const string HANDSHAKE_MESSAGE = "Hello";

            this.client = new TcpClient();
            this.serverEndPoint = new IPEndPoint(IPAddress.Parse(HOST), PORT);
            while(shouldContinue && !connectSuccess)
            {
                connectSuccess = true;
                try
                {
                    client.Connect(serverEndPoint);
                }
                catch (System.Net.Sockets.SocketException)
                {
                    connectSuccess = false;
                    var result = MessageBox.Show("Connection Failed", "Try again?", MessageBoxButton.YesNo, MessageBoxImage.Question);
                    if (result == MessageBoxResult.Yes)
                    {
                        System.Threading.Thread.Sleep(1000);
                        shouldContinue = true;
                        triedAgain = true;
                    }
                    else
                    {
                        shouldContinue = false;
                        Environment.Exit(0);
                    }
                }
                
            }

            this.clientStream = client.GetStream();

            byte[] buffer = new byte[HANDSHAKE_MESSAGE.Length];
            int bytesRead = this.clientStream.Read(buffer, 0, HANDSHAKE_MESSAGE.Length);
            if ((new ASCIIEncoding().GetString(buffer)) == HANDSHAKE_MESSAGE)
            {
                buffer = new ASCIIEncoding().GetBytes(HANDSHAKE_MESSAGE);
                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
            if(triedAgain)
            {
                MainWindow mainWindow = new MainWindow();
                mainWindow.Show();
            }
        }
    }
}
