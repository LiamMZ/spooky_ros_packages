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

    void MotorActuatorNodelet::Setup(ros::NodeHandle& nh)
    {
        nh_ = nh; 
        motor_server_ = nh.advertiseService("motor_actuator", &MotorActuatorNodelet::motor_callback, this);
        
    }

    bool MotorActuatorNodelet::motor_callback(spooky_msgs::MotorCommand::Request& req,
                                 spooky_msgs::MotorCommand::Response& res)
    {
        bool success;
        success = driver_.setMotor(req.motor, req.speed, static_cast<Command>(req.command));
        res.success = success;
        return success;
    }
    
}