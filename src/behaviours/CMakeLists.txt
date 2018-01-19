cmake_minimum_required(VERSION 2.8.3)
project(behaviours)

SET(CMAKE_CXX_FLAGS "-std=c++11")

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs
  random_numbers
  tf
  apriltags_ros
  swarmie_msgs
  )

catkin_package(
  CATKIN_DEPENDS geometry_msgs swarmie_msgs roscpp sensor_msgs std_msgs random_numbers tf apriltags_ros
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(
  behaviours
  src/Tag.cpp
  src/ROSAdapter.cpp
  src/PID.cpp
  src/Gripper.cpp
  src/state_machine/Error.cpp
  src/waypoints/WaypointUtilities.cpp
  src/waypoints/SimpleWaypoint.cpp
  src/waypoints/SimpleWaypointStates.cpp
  src/logic/LogicMachine.cpp
  src/logic/LogicState.cpp
  src/logic/SearchState.cpp
  src/logic/search/SearchMachine.cpp
  src/logic/search/SearchStateBase.cpp
)

add_dependencies(behaviours ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  behaviours
  ${catkin_LIBRARIES}
)

