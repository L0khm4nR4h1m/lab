import socket
import sys
import time
import errno
import math
from multiprocessing import Process

def process_start(s_sock):
    query = (
        'Welcome to the Calculator Server\n\n'
        'Pick an operation between:\n'
        '1: Factorial\n'
        '2: Logarithm(base 10)\n'
        '3: Exponent\n'
        '4: Square Root\n'
        '5: To exit\n'
    )
    
    num_msg = 'Please enter an integer number'
    s_sock.send(str.encode(query))
    
    while True:
        data = s_sock.recv(2048)
        if not data:
            break
        
        data = int(data.decode('utf-8'))

        if data == 1:
            total = Factorial(s_sock, num_msg)
            total = str(total)
            s_sock.sendall(str.encode(total))
            
        elif data == 2:
            total = Logarithm(s_sock, num_msg)
            total = str(total)
            s_sock.sendall(str.encode(total))
			
        elif data == 3:
            total = Exponent(s_sock, num_msg)
            total = str(total)
            s_sock.sendall(str.encode(total))

        elif data == 4:
            total = Square(s_sock, num_msg)
            total = str(total)
            s_sock.sendall(str.encode(total))

        elif data == 5:
            s_sock.sendall(str.encode('Goodbye'))
            break
		
        else:
            s_sock.sendall(str.encode('Invalid option'))
		    
    s_sock.close()
    
def Factorial(s_sock, num_msg):
    num_msg = num_msg.encode('utf-8')
    s_sock.sendall(num_msg)
    data = s_sock.recv(2048)
    num = int(data.decode('utf-8'))
    val = math.factorial(num)
    str = 'The value of '
    str2 = "% s" % num
    str3 = '! is '
    str4 = "% s" % val
    result = str + str2 + str3 + str4
    return result
    
def Logarithm(s_sock, num_msg):
    num_msg = num_msg.encode('utf-8')
    s_sock.sendall(num_msg)
    data = s_sock.recv(2048)
    num = int(data.decode('utf-8'))
    val = math.log(num, 10)
    str = 'The value of log('
    str2 = "% s" % num
    str3 = ') is '
    str4 = "% s" % val
    result = str + str2 + str3 + str4
    return result

def Exponent(s_sock, num_msg):
    num_msg = num_msg.encode('utf-8')
    s_sock.sendall(num_msg)
    data = s_sock.recv(2048)
    num = int(data.decode('utf-8'))
    val = math.exp(num)
    str = 'The value of e*'
    str2 = "% s" % num
    str3 = ' is '
    str4 = "% s" % val
    result = str + str2 + str3 + str4
    return result
	
def Square(s_sock, num_msg):
    num_msg = num_msg.encode('utf-8')
    s_sock.sendall(num_msg)
    data = s_sock.recv(2048)
    num = int(data.decode('utf-8'))
    val = math.sqrt(num)
    str = 'The value of square root('
    str2 = "% s" % num
    str3 = ') is '
    str4 = "% s" % val
    result = str + str2 + str3 + str4
    return result
	

if __name__ == '__main__':
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("",8888))
    print("listening...")
    s.listen(3)
    try:
        while True:
            try:
                s_sock, s_addr = s.accept()
                p = Process(target=process_start, args=(s_sock,))
                p.start()

            except socket.error:

                print('got a socket error')

    except Exception as e:
        print('an exception occurred!')
        print(e)
        sys.exit(1)
    finally:
        s.close()