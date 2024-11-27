cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0048 NEW) # avoid annoing warnings
project(tvl1flow C CXX)

message(STATUS "Configuring project: " ${PROJECT_NAME})

###############################################################################

# NOTE: -fPIC is added so that the static library can be included into
#       shared libraries.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -w -fPIC -O3 ")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ggdb")

###############################################################################

# Enable C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

###############################################################################

# Find OpenMP
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(TIFF REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG  REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})
###############################################################################

include_directories(${IIO_INCLUDE_DIR})

# tvl1 static library
add_library(iio STATIC iio.c)

target_link_libraries(iio png tiff jpeg)
add_library(tvl1flow STATIC tvl1flow_lib.c)
add_library(opencv_wrapper SHARED opencv_wrapper.cpp) # Add wrapper
target_link_libraries(tvl1flow iio m)
target_link_libraries(opencv_wrapper ${OpenCV_LIBS})

# tvl1 executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(tvl1flow-bin main.c)
target_link_libraries(tvl1flow-bin opencv_wrapper iio m)
set_target_properties(tvl1flow-bin PROPERTIES OUTPUT_NAME tvl1flow)

###############################################################################

# Expose public includes to other subprojects through cache variable
set(TVL1FLOW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

