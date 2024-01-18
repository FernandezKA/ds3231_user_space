cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(DS3231 VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(${PROJECT_NAME} Src/main.cpp)

# Include directories
include_directories(Inc)

# Add the source files
target_sources(${PROJECT_NAME} PRIVATE Src/DS3231.cpp)

# Find and link any necessary libraries, for example, I2Cdev if needed
# find_library(I2CDEV_LIBRARY NAMES I2Cdev)
# if (I2CDEV_LIBRARY)
#   target_link_libraries(${PROJECT_NAME} ${I2CDEV_LIBRARY})
# endif()

# Installation rules
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
