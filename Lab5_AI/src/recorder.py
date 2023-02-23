import paho.mqtt.client as mqtt
import serial, time, json, csv

ser = serial.Serial(port = '/dev/ttyACM0', baudrate=115200, timeout=1) 
print("Connected to MCU")
file = open('datos.csv', 'w')
writer = csv.writer(file)
data_rows = []
header = ['x', 'y', 'z']
print(header)
writer.writerow(header)

while(1):
    data = ser.readline().decode('utf-8').replace('\r', "").replace('\n', "")
    data = data.split('\t')
    if len(data) >= 3:
        writer.writerow(data)
        print(data)


    

