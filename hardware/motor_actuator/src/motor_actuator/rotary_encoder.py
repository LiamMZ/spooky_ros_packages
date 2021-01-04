#!/usr/bin/python

import RPi.GPIO as GPIO
import time

class RotaryEncoder(object):
    def __init__(self, Enc_A, Enc_B, pulse_count=0):
        '''
        Initializes a number of settings and prepares the environment
        before we start the main program.
        '''
        self.Enc_A = Enc_A
        self.Enc_B = Enc_B
        self.lastitem = [None,None,None]
        self.pulse_count = 0
        GPIO.setwarnings(True)
        GPIO.setmode(GPIO.BCM)			# Use BCM mode
        GPIO.setup(self.Enc_A, GPIO.IN) 			# setup callback thread for the A and B encoder 	
        GPIO.setup(self.Enc_B, GPIO.IN)			
        GPIO.add_event_detect(self.Enc_A, GPIO.RISING, callback=self.rotary_interrupt) 	# NO bouncetime 
        GPIO.add_event_detect(self.Enc_B, GPIO.RISING, callback=self.rotary_interrupt) 	# NO bouncetime 
    
    def rotary_interrupt(self, w):
        if w == self.Enc_A:
            item = (w, 1, GPIO.input(self.Enc_B))
        else:
            item = (w, GPIO.input(self.Enc_A),1)
            
        if item == (self.Enc_A,1,1) and self.lastitem[1] == 0:	# Is it in END position?
            self.pulse_count-=1
            print ("DOWN", self.pulse_count)
        elif item == (self.Enc_B,1,1) and self.lastitem[2] == 0:	# Same but for ENC_B
            self.pulse_count+=1
            print ("UP", self.pulse_count)
        self.lastitem = item	

    def __del__(self):
        GPIO.cleanup()

if __name__=='__main__':
    # init and loop forever (stop with CTRL C)
    enc = RotaryEncoder(16,6)
    while 1:
        print()
        print(enc.pulse_count)
        time.sleep(1)