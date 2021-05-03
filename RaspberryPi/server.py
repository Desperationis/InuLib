from socket import *

s = socket(type=SOCK_DGRAM)
s.bind(('192.168.1.4', 5000))

while True:
    data,addr = s.recvfrom(64)
    data = data.decode('utf-8').split(",")
    print(data, addr)
    #s.sendto(data,addr)

