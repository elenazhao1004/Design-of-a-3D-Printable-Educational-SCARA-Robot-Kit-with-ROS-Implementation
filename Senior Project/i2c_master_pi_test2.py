import RPi.GPIO as gpio
import smbus
from timeit import default_timer as timer
import sys

bus = smbus.SMBus(1)
address = 0x04

def main():
    start = timer()
    gpio.setmode(gpio.BCM)
    gpio.setup(17, gpio.OUT)
    status = False
    
    for i in range(100000):
        gpio.output(17, status)
        #status = true
        bus.write_byte(address, 1)
        #print ("Arduino answer to RPI:",bus.read_byte(address))
        #time.sleep(1)
    end = timer()
    print(end - start)


if __name__ == '__main__':
    try:
        main()
        gpio.cleanup()
    except KeyboardInterrupt:
        print ('Interrupted')
        gpio.cleanup()
        sys.exit(0)
        
