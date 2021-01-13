#!/usr/bin/python

import pigpio

class RotaryEncoder(object):
   def __init__(self, gpioA, gpioB, pulse_count=0, pi = pigpio.pi(), encoder_min=-32750, encoder_max=32750):
      self.pi = pi
      self.gpioA = gpioA
      self.gpioB = gpioB

      self.pulse_count = pulse_count
      self.levA = 0
      self.levB = 0
      self.encoder_min = encoder_min
      self.encoder_max = encoder_max

      self.low_wrap = (self.encoder_max - self.encoder_min) * 0.3 + self.encoder_min 
      self.high_wrap = (self.encoder_max - self.encoder_min) * 0.7 + self.encoder_min

      self.lastGpio = None

      self.pi.set_mode(gpioA, pigpio.INPUT)
      self.pi.set_mode(gpioB, pigpio.INPUT)

      self.pi.set_pull_up_down(gpioA, pigpio.PUD_UP)
      self.pi.set_pull_up_down(gpioB, pigpio.PUD_UP)

      self.cbA = self.pi.callback(gpioA, pigpio.EITHER_EDGE, self._pulse)
      self.cbB = self.pi.callback(gpioB, pigpio.EITHER_EDGE, self._pulse)

   def _pulse(self, gpio, level, tick):
      """
      Decode the rotary encoder pulse.

                     +---------+         +---------+      0
                     |         |         |         |
         A         |         |         |         |
                     |         |         |         |
         +---------+         +---------+         +----- 1

               +---------+         +---------+            0
               |         |         |         |
         B   |         |         |         |
               |         |         |         |
         ----+         +---------+         +---------+  1
      """

      if gpio == self.gpioA:
         self.levA = level
      else:
         self.levB = level

      if gpio != self.lastGpio: # debounce
         self.lastGpio = gpio

         if   gpio == self.gpioA and level == 1:
            if self.levB == 1:
               self.callback(1)
         elif gpio == self.gpioB and level == 1:
            if self.levA == 1:
               self.callback(-1)
    
   def callback(self, direction):
      if direction == 1 and self.pulse_count >= self.encoder_max:
         self.pulse_count = self.encoder_min
      elif direction == -1 and self.pulse_count<=self.encoder_min:
         self.pulse_count = self.encoder_max
      else:
         self.pulse_count+=direction
      print("pos:", self.pulse_count)

   def __del__(self):
      """
      Cancel the rotary encoder decoder.
      """

      self.cbA.cancel()
      self.cbB.cancel()
      self.pi.stop()



if __name__ == "__main__":

   decoder = RotaryEncoder(6, 16)

   time.sleep(300)
