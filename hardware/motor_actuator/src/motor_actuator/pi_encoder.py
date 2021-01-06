from gpiozero import DigitalInputDevice

# Class for photointerupter encoder tic counting
class PhotoInterupterEncoderCounter(object):
    ## Constructor sets up Digital input device and sets when changed function
    # @param[in] pin_number - number for GPIO pin to monitor
    def __init__(self, pin_number):
        self.pulse_count = 0
        self.device = DigitalInputDevice(pin=pin_number)
        self.device.pin.when_changed = self.when_changed
    # Overload function for when_changed increases pulse count
    def when_changed(self, when, state):
        self.pulse_count += 1
    
    # Function to reset pulse count
    def reset_count(self):
        self.pulse_count = 0

