#!/usr/bin/env python

from motor_actuator.pi_encoder import PhotoInterupterEncoderCounter
from motor_actuator.rotary_encoder_v2 import RotaryEncoder
import rospy
from std_msgs.msg import Int16

class EncoderNode(object):
    def __init__(self, lpin=4, rpin=26):
        chassis = rospy.get_param('/chassis', 'tank')
        if chassis=='tank':
            self.left_encoder = RotaryEncoder(24,23)
            self.right_encoder = RotaryEncoder(6,16)
        elif chassis == '4_wheel':
            self.left_encoder = PhotoInterupterEncoderCounter(lpin)
            self.right_encoder = PhotoInterupterEncoderCounter(rpin)
        self.left_encoder_pub_ = rospy.Publisher('lwheel', Int16, queue_size=10)
        self.right_encoder_pub_ = rospy.Publisher('rwheel', Int16, queue_size=10)
    
    def run(self):
        while not rospy.is_shutdown():
            self.right_encoder_pub_.publish(Int16(self.right_encoder.pulse_count))
            self.left_encoder_pub_.publish(Int16(self.left_encoder.pulse_count))

if __name__ == '__main__':
    rospy.init_node('encoder_node')
    node = EncoderNode()
    node.run()
    rospy.spin()

