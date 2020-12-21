cmake_minimum_required(VERSION 3.0.2)
project(spooky_msgs)


find_package(catkin REQUIRED COMPONENTS
  std_msgs
  message_generation
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)



add_service_files(
  FILES
  MotorCommand.srv
) 

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  CATKIN_DEPENDS message_runtime
)