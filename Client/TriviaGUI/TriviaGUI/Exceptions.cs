using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaGUI
{
    class ResponseErrorReplyException : Exception
    {
        public ResponseErrorReplyException()
        {

        }

        public ResponseErrorReplyException(string message)
            : base(message)
        {
        }

        public ResponseErrorReplyException(string message, Exception inner)
            : base(message, inner)
        {
        }
    }
    class ResponseUnexpectedErrorReplyException : Exception
    {
        public ResponseUnexpectedErrorReplyException()
        {

        }

        public ResponseUnexpectedErrorReplyException(string message)
            : base(message)
        {
        }

        public ResponseUnexpectedErrorReplyException(string message, Exception inner)
            : base(message, inner)
        {
        }
    }
}
