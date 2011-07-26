cmake_minimum_required(VERSION 2.4.6)
project(ADK_DEMO C CXX)

include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
rosbuild_find_ros_package(rosserial_arduino)
include(${rosserial_arduino_PACKAGE_PATH}/cmake_scripts/rosserial.cmake)

include_directories(src/AndroidAccessory src/USB_Host_Shield)
#====================================================================#
#  Chatter                                                #
#====================================================================#

file(GLOB ROSSERIAL_CUSTOM_SERIAL src/adk_fx.cpp src/AndroidAccessory/AndroidAccessory.cpp src/USB_Host_Shield/*.cpp)

set(linefollower_NO_DEFAULT_COM 1)
set(linefollower_BOARD mega2560)               # Arduino Target board
set(linefollower_SRCS src/linefollower.cpp          
					${ROSSERIAL_CUSTOM_SERIAL} )  
set(linefollower_LIBS m)
set(linefollower_PORT /dev/ttyUSB0)            # Serial upload port

generate_ros_firmware(linefollower)

