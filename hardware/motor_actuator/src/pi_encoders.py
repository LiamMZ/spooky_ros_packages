from gpiozero import DigitalInputDevice

class PhotoInterupterEncoder(object):
    def __init__(self, pin_number):
        self.pulse_count = 0
        self.device = DigitalInputDevice(pin=pin_number)
        self.device.pin.when_changed = self.when_changed
        
    def when_changed(self):
        self.pulse_count += 1
    
    def reset_count(self):
        self.pulse_count = 0