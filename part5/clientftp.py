import socket
import sys

if __name__ == "__main__":

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("192.168.0.106", 8888))
    input = input("Enter the filename: ")
    try:
    
        f = open(input, "r")
        data = f.read()
        s.send(input.encode('utf-8'))
        msg = s.recv(1024).decode('utf-8')
        print("Server: " + msg)
        s.send(data.encode('utf-8'))
        msg = s.recv(1024).decode('utf-8')
        print("Server: " + msg)
        f.close()
        s.close()
    
    except Exception as e:
        print('File does not exist!')
        print(e)
        sys.exit(1)
