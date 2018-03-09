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
  src/MotorController.cpp
  src/TagUtilities.cpp
  src/state_machine/Error.cpp
  src/waypoints/Waypoint.cpp
  src/waypoints/WaypointUtilities.cpp
  src/waypoints/SimpleWaypoint.cpp
  src/waypoints/ApproachTagWaypoint.cpp
  src/waypoints/LinearWaypoint.cpp
  src/waypoints/RawOutputWaypoint.cpp
  src/logic/LogicMachine.cpp
  src/logic/SearchState.cpp
  src/logic/PickUpState.cpp
  src/logic/FindHomeState.cpp
  src/logic/MotorCalibState.cpp
  src/logic/RotationalCalibState.cpp
  src/logic/DropOffState.cpp
  src/TagExaminer.cpp
)

add_dependencies(behaviours ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  behaviours
  ${catkin_LIBRARIES}
)

