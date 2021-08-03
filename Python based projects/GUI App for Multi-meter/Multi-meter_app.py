"""
Created on Th Mar 25 12:01:24 2021

@author: Mohab Mohamed
"""


from tkinter import *
from tkinter.ttk import *
from mttkinter import *
from tkinter import messagebox
import threading
import time
import os
import serial
import serial.tools.list_ports

serial_data = ''
vData = 0       # carry the processed voltage measurement
cData = 0       # carry the processed current measurement
rData = 0       # carry the processed resistance measurement
update_period = 1
ser = None
volt = []
current = []
resistance = []
voltageMode = 0 #Voltage data ready flag used in get_data function to indicate that a result is ready to be displayed
currentMode = 0 #Current data ready flag used in get_data function to indicate that a result is ready to be displayed
resistanceMode = 0 #resistance data ready flag used in get_data function to indicate that a result is ready to be displayed
vModeOn = 0
cModeOn = 0
currentSensor = 10.5



gui = mtTkinter.Tk()
gui.title("MultiMeter App")


def AtoN(frame):
    val = ''                            #Empty string
    for s in frame:             #for loop to create string containing only the numbers in the incoming frame.
        if s >= 48 and s <= 57:   #Ignore any value that is not a number
            val += str(s - 48)       
    return int(val) 


def connect():    
        """
        The function initiates the Connection to the UART device with the Port and Buad fed through the Entry
        boxes in the application.

        The radio button selects the platform, as the serial object has different key phrases 
        for Linux and Windows. Some Exceptions have been made to prevent the app from crashing,
        such as blank entry fields and value errors, this is due to the state-less-ness of the 
        UART device, the device sends data at regular intervals irrespective of the master's state. The other Parts are self explanatory.
        """
        global ser
        port = port_entry.get()
        baud = baud_entry.get()  
        try:
                ser = serial.Serial(str(port), baud)
        except ValueError:
                messagebox.showerror("Enter baud rate and com port", "Error")
                return
        except serial.serialutil.SerialException:
                print(f"could not open port {str(port)}")
                messagebox.showerror("could not open port", "Error")
                return
        t1 = threading.Thread(target = get_data)
        t1.daemon = True
        t1.start()

def get_data():
        """
        This function serves the purpose of collecting data from the serial object and storing 
        the filtered data into a global variable.
        The function has been put into a thread since the serial event is a blocking function.
        """
        global ser
        global vData
        global cData
        global rData
        global voltageMode
        global currentMode
        global resistanceMode
        global volt
        global current
        global resistance
        global vModeOn
        global cModeOn
        while(1):
                try:
                        if ser.in_waiting > 0:                          # Check if the buffer contains data.
                                c = ord(ser.read(1).decode('ascii'))        # store the ascii value in c
                                if c == 64: # c = '@' voltage frame 
                                    while c != 59: # c = ';'
                                        volt.append(c)
                                        c = ord(ser.read(1).decode('ascii'))
                                        
                                    adcVal = AtoN(volt)
                                    vData = (adcVal * 5) / 1020
                                    print(f"Volage = {vData}")
                                    volt = []
                                    voltageMode = 1
                                    vModeOn = 1
                                    
                                elif c == 35: # c = '#' current frame
                                    while c != 59:
                                        current.append(c)
                                        c = ord(ser.read(1).decode('ascii'))
                                        
                                    adcVal = AtoN(current)
                                    v = (adcVal * 5) / 1020
                                    cData = (v / currentSensor)
                                    print(f"Current = {cData} mA")
                                    current = []
                                    currentMode = 1
                                    cModeOn = 1
                                    
                                elif c == 36: # c = '$' resistance frame
                                    while c != 59:
                                        resistance.append(c)
                                        c = ord(ser.read(1).decode('ascii'))
                                        
                                    knownRes = 1000
                                    unknownRes = 0
                                    adcVal = AtoN(resistance)
                                    v = (adcVal * 5) / 1020
                                    if v == 0:
                                        buffer = 0
                                    else:
                                        buffer = (5 / v) - 1
                                    unknownRes = buffer * knownRes
                                    rData = unknownRes
                                    print(f"Resistance = {rData} ohm")
                                    resistance = []
                                    resistanceMode = 1
                                    
                except TypeError:
                        pass 


def update_gui():
        """"
        This function is an update function which is also threaded. The function assimilates the data
        and applies it to it corresponding progress bar. The text box is also updated every couple of seconds.</p><p>    A simple auto refresh function .after() could have been used, this has been avoid purposely due to 
        various performance issues.
        """
        
        global voltageMode
        global currentMode
        global resistanceMode
        global vModeOn
        global cModeOn
        global currentSensor
        while(1):
            
            if voltageMode:
                vDataL.configure(text = f"{round(vData, 3)} V")
                voltageMode = 0

            if currentMode:
                cDataMilli = cData*1000
                cDataL.configure(text = f"{round(cDataMilli, 6)} mA")
                currentMode = 0

            if resistanceMode:
                rDataL.configure(text = f"{round(rData, 5)} ohm")
                resistanceMode = 0

            if vModeOn and cModeOn:
                vModeOn = 0
                cModeOn = 0
                power = vData*cData
                if cData > 0:
                   Rt = vData / cData
                   rDataLc.configure(text = f"{round(Rt,3)} ohm")
                else:
                    rDataLc.configure(text = "OO ohm")
                pDataL.configure(text = f"{power} W")


def send():
        """
        This function is for sending data from the computer to the host controller.

        The value entered in the the entry box is pushed to the UART. The data can be of any format, since
        the data is always converted into ASCII, the receiving device has to convert the data into the required f
        format.
        """
        send_data = data_entry.get()
    
        if not send_data:
                print("Sent Nothing")
        else:
            ser.write(send_data.encode())

def voltM():
    try:
        ser.write("#1#".encode())
    except:
        print("Unable to send data")

def currentM():
    try:
        ser.write("#2#".encode())
    except:
        print("Unable to send data")

def resistanceM():
    try:
        ser.write("#3#".encode())
    except:
        print("Unable to send data")

def dualM():
    try:
        ser.write("#4#".encode())
    except:
        print("Unable to send data")

def nullM():
    try:
        ser.write("#0#".encode())
    except:
        print("Unable to send data")
    


def disconnect():    
        """ 
        This function is for disconnecting and quitting the application.</p><p>    Sometimes the application throws a couple of errors while it is being shut down, the fix isn't out yet
        but will be pushed to the repo once done.  
        simple GUI.quit() calls.    
        """
        try:
                ser.close()     
        except AttributeError:
                print("Closed without Using it")
        gui.quit()


if __name__ == "__main__":

        #frames
        frame_1 = Frame(height = 285, width = 480, relief = 'groove').place(x = 7, y = 5)
        frame_2 = Frame(height = 150, width = 480, relief = 'groove').place(x = 7, y = 300)
        welcomeL = Label(text = "     Welcome\nMultimeter GUI", font=("Arial Bold", 25)).place(x = 125, y = 10)

        #threads
        t2 = threading.Thread(target = update_gui)
        t2.daemon = True
        t2.start()

        #Labels
        voltL = Label(text = "Voltage:").place(x = 15, y= 100)
        currentL = Label(text = "Current:").place(x = 15, y= 130)
        powerL = Label(text = "Power:").place(x = 15, y= 160)
        cResL = Label(text = "Circuit Resistance:")
        cResL.place(x = 15, y= 190)
        ResL = Label(text = "Resistance:")
        ResL.place(x = 15, y= 210)
        vDataL = Label(text = "V")
        vDataL.place(x = 200, y = 100)
        cDataL = Label(text = "mAmp")
        cDataL.place(x = 200, y= 130)
        pDataL = Label(text = "mW")
        pDataL.place(x = 200, y= 160)
        rDataLc = Label(text = "ohm") #Rt in a circuit
        rDataLc.place(x = 200, y= 190)
        rDataL = Label(text = "ohm")
        rDataL.place(x = 200, y= 210)
        
        baud   = Label(text = "Baud").place(x = 100, y = 348)
        port   = Label(text = "Port").place(x = 200, y = 348)

        #Entry
        #data_entry = Entry()
        #data_entry.place(x = 100, y = 255)
            
        baud_entry = Entry(width = 7)
        baud_entry.place(x = 100, y = 365)
            
        port_entry = Entry(width = 7)
        port_entry.place(x = 200, y = 365)

        #button
        voltageCommandB = Button(text = "V", command = voltM, width = 6).place(x = 15, y = 250)
        currentCommandB = Button(text = "C", command = currentM, width = 6).place(x = 85, y = 250)
        resistanceCommandB = Button(text = "R", command = resistanceM, width = 6).place(x = 155, y = 250)
        dualCommandB = Button(text = "D", command = dualM, width = 6).place(x = 225, y = 250)
        nullCommandB = Button(text = "Stop", command = nullM, width = 6).place(x = 295, y = 250)
        connect = Button(text = "Connect", command = connect).place(x = 15, y = 360)
        #disconnect = Button(text = "Disconnect", command = disconnect).place(x =300, y = 360)


        
        gui.geometry('500x500')
        gui.resizable(False, False)
        gui.mainloop()


















