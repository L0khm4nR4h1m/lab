import socket
import sys

ClientSocket = socket.socket()
host = '192.168.1.222'
port = 8888

print('Waiting for connection')
try:
    ClientSocket.connect((host, port))
except socket.error as e:
    print(str(e))
	
Response = ClientSocket.recv(1024)
print(Response.decode('utf-8'))

while True:
    Input = input('Enter your option: ')
    ClientSocket.send(str.encode(Input))
    Response = ClientSocket.recv(1024)
    print(Response.decode('utf-8'))
    number = input('Number: ')
    ClientSocket.send(str.encode(number))
    Response = ClientSocket.recv(1024)
    print(Response.decode('utf-8'))

ClientSocket.close()