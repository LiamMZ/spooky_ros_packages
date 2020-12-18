cmake_minimum_required(VERSION 3.0.2)
project(motor_actuator)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  nodelet
  pluginlib
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

add_library(MotorActuatorNodelet
src/safety_controller.cpp
)
add_dependencies(MotorActuatorNodelet
${catkin_EXPORTED_TARGETS}
)
target_link_libraries(MotorActuatorNodelet
${catkin_LIBRARIES}
)

install(TARGETS MotorActuatorNodelet
DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY plugins
DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

# Declare a C++ library
add_library( ${PROJECT_NAME}
    src/adafruitdcmotor.cpp
    src/adafruitmotorhat.cpp
    src/i2cdevice.cpp 
    src/motor_driver.cpp
    src/pwm.cpp
    )


add_executable(motor_test src/main.cpp)
target_link_libraries(motor_test ${PROJECT_NAME})

