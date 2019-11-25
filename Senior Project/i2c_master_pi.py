# Rasberry Pi master for Arduino Slave
# i2c_master_pi.py
# connects to Arduino via i2c

from smbus import SMBus

addr = 0x8 #bus address
bus = SMBus(1) # indicates /dev/i2c -1

numb = 1

print("Enter 1 for ON / 0 for OFF")
while numb == 1:
	ledState = input(">>>>  ")
	
	if ledState =="1":
		bus.write_byte(addr, 0x1) #switch it on
	elif ledState == "0":
		bus.write_byte(addr,0x0) # swtich it off
	else: 
		numb = 0
