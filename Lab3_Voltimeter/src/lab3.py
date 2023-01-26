import serial
import csv

ser = serial.Serial("/dev/ttyUSB0",9600)
file = open('datos.csv', 'w')
writer = csv.writer(file)

while True:
    volt0d = ser.readline()
    volt1d = ser.readline()
    volt2d = ser.readline()
    volt3d = ser.readline()
    volt0 = volt0d.decode().strip()
    volt1 = volt1d.decode().strip()
    volt2 = volt2d.decode().strip()
    volt3 = volt4d.decode().strip()
    data= ["V1:", volt0, "V2:", volt1, "V3:", volt2, "V4:", volt3 ]
    writer.writerow(data)
