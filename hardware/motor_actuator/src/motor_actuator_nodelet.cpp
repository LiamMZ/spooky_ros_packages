// this should really be in the implementation (.cpp file)
#include <pluginlib/class_list_macros.h>

// Include your header
#include <motor_actuator/motor_actuator_nodelet.h>

#include <motor_actuator/util.h>

// watch the capitalization carefully
PLUGINLIB_EXPORT_CLASS(motor_actuator::MotorActuatorNodelet, nodelet::Nodelet)

namespace motor_actuator
{
    void MotorActuatorNodelet::onInit()
    {
        NODELET_DEBUG("Initializing motor driver nodelet...");
        Setup(getNodeHandle());
    }

    void MotorActuatorNodelet::Setup(ros::NodHandle& nh)
    {
        nh_ = nh; 
        motor_server = nh.advertiseService("motor_actuator", motor_callback);
        
    }

    bool MotorActuatorNodelet::motor_callback(spooky_msgs::MotorCommand::Request& req,
                                 spooky_msgs::MotorCommand::Response& res)
    {
        driver.setMotor(req.motor, req.speed, std::static_cast<Command>(req.command));
    }
    
}