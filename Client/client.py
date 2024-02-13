import socket
import struct
import json

HOST = "127.0.0.1"
PORT = 6969
INITIAL_MESSAGE = "Hello"

SERVER_RESPONSE_LEN = 1024 # TO DO: change this to expected length
LOGIN_CODE = 1
SIGNUP_CODE = 2

def print_server_msg(msg):
	print(b"Server: " + msg)

def setup_connection_and_handshake():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((HOST, PORT))
        server_msg = sock.recv(len(INITIAL_MESSAGE)).decode()
        print_server_msg(server_msg.encode())
        if server_msg == INITIAL_MESSAGE:
            sock.sendall(INITIAL_MESSAGE.encode())

    except InterruptedError:
        print("ERROR: Connection interrupted")
        exit()
    except ConnectionError:
        print("ERROR: Connection unsuccsessful/server disconnected")
        exit()
    return sock

def test_login_message(sock):
    data = json.dumps({"username": "meleh", "password": "123123"})
    message = struct.pack("b", LOGIN_CODE) + struct.pack("I", len(data)) + data.encode()
    sock.sendall(message)
    response = sock.recv(SERVER_RESPONSE_LEN)
    print_server_msg(response)

def test_signup_message(sock, name = "meleh"):
    data = json.dumps({"username": name, "password": "123123", "email": "noob@gmail.com"})
    message = struct.pack("b", SIGNUP_CODE) + struct.pack("I", len(data)) + data.encode()
    sock.sendall(message)
    response = sock.recv(SERVER_RESPONSE_LEN)
    print_server_msg(response)


def main():
    sock = setup_connection_and_handshake()	# connection is set up
    print("Trying to log in without signing up")
    test_login_message(sock)
	
    print("Signing up")
    test_signup_message(sock)
	
    print("Trying to sign up again with registered username")
    test_signup_message(sock)
	
    print("Trying to sign up with an illegal username (empty)")
    test_signup_message(sock, "")
	
    print("Login")
    test_login_message(sock) # login
	
    print("Trying to log in after being logged in")
    test_login_message(sock) # try to login after being logged in

if __name__ == "__main__":
    main()
