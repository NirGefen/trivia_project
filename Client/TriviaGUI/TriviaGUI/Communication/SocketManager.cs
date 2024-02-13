using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaGUI
{
    public class ResponseInfo
    {
        public uint header;
        public string json;
    }
    public class SocketManager
    {
        public Communicator socket;
        public SocketManager()
        {
            this.socket = new Communicator();
        }
        public ResponseInfo getResponseForRequest(byte header, string json)
        {
            socket.clientStream.Write(new byte[1] { header }, 0, 1);
            socket.clientStream.Write(System.BitConverter.GetBytes(json.Length), 0, sizeof(int));
            byte[] jsonArr = new ASCIIEncoding().GetBytes(json);
            if(jsonArr.Length > 0) 
                socket.clientStream.Write(jsonArr, 0, jsonArr.Length);

            ResponseInfo info = new ResponseInfo();
            byte[] buffer = new byte[65536];
            int bytesRead = socket.clientStream.Read(buffer, 0, buffer.Length);

            info.header = buffer[Constants.RESPONSE_CODE_INDEX];
            int length = System.BitConverter.ToInt32(new byte[4] { buffer[4], buffer[3], buffer[2], buffer[1] }, 0);
            jsonArr = new byte[length]; // jsonArr contains json message only
            Array.Copy(buffer, Constants.JSON_DATA_INDEX, jsonArr, 0, length);
            info.json = System.Text.Encoding.Default.GetString(jsonArr);
            return info;
        }
    }
}
