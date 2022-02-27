cmake_minimum_required(VERSION 3.0.2)
set (CMAKE_CXX_STANDARD 11)
project(motor_actuator)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  nodelet
  pluginlib
  spooky_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES motor_actuator
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# Declare a C++ library
add_library( ${PROJECT_NAME}
    src/adafruitdcmotor.cpp
    src/adafruitmotorhat.cpp
    src/i2cdevice.cpp 
    src/motor_driver.cpp
    src/pwm.cpp
    )

catkin_python_setup()

install(
     PROGRAMS
     nodes/encoder_node.py
     DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

add_library(MotorActuatorNodelet src/motor_actuator_nodelet.cpp)
target_link_libraries(MotorActuatorNodelet ${catkin_LIBRARIES} ${PROJECT_NAME} -lwiringPi)
## Mark the nodelet library for installations
install(TARGETS MotorActuatorNodelet
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

## Mark other files for installation (e.g. launch and bag files, etc.)
install(FILES nodelet_plugin.xml motor_actuator_nodelet.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

