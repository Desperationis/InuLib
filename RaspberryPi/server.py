from socket import *
import serial


serialInterface = serial.Serial('/dev/ttyS0', 9600, timeout=1,stopbits=1,bytesize=8)


s = socket(type=SOCK_DGRAM)
s.bind(('192.168.1.4', 5000))

while True:
    if serialInterface.isOpen:
        data,addr = s.recvfrom(1024)
        data = data.decode('utf-8').split(",")
        print(data, addr)
        serialInterface.write([255])
        serialInterface.write([
                int(data[0]),
                int(data[1]),
                int(data[2]),
                int(data[3]),
                int(data[4]),
                int(data[5])
            ])
        #s.sendto(data,addr)

