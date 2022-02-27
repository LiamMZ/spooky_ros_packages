cmake_minimum_required(VERSION 3.0.2)
project(raspi_cam)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++17)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  spooky_msgs
  std_msgs
  sensor_msgs
  cv_bridge
  roscpp
  std_msgs
  image_transport
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES motor_actuator
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} src/raspi_cam_nodelet.cpp)
target_link_libraries(RaspiCamNodelet ${catkin_LIBRARIES} ${PROJECT_NAME})

## Mark the nodelet library for installations
install(TARGETS RaspiCamNodelet
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

## Mark other files for installation (e.g. launch and bag files, etc.)
install(FILES nodelet_plugin.xml raspi_cam_nodelet.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

