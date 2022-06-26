import socket
import sys

if __name__ == "__main__":
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("", 8888))
    s.listen(1)
    print("Listenin...")
    
    try:
        try:
            s_sock, s_addr = s.accept()
            print("Connected to : " + str(s_addr[0]))
            filename = s_sock.recv(1024).decode('utf-8')
            print("Receiving the filename: " + filename)
            f = open(filename, "w")
            s_sock.send("Filename received.".encode('utf-8'))
            data = s_sock.recv(1024).decode('utf-8')
            print("Receiving the file data.")
            f.write(data)
            s_sock.send("File data received".encode('utf-8'))
            f.close()
            s.close()

        except socket.error:
            print('got a socket error')

    except Exception as e:
        print('an exception occurred!')
        print(e)
        sys.exit(1)
    