cmake_minimum_required(VERSION 2.8)

project(unit-thread)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(Boost COMPONENTS system program_options REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

#set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: Debug Release"
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(GRAV_FLAGS_DEBUG "-Wall -Wextra -Werror -g -pg -fno-inline")
set(GRAV_FLAGS_RELEASE "-Wall -Wextra -Werror  -O2")

set(CMAKE_C_FLAGS_DEBUG ${GRAV_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_DEBUG "${GRAV_FLAGS_DEBUG} -std=c++11")

set(CMAKE_C_FLAGS_RELEASE ${GRAV_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELEASE "${GRAV_FLAGS_RELEASE} -std=c++11")

message("Release C   flags are ${CMAKE_C_FLAGS_RELEASE}")
message("Debug   C   flags are ${CMAKE_C_FLAGS_DEBUG}")
message("Release C++ flags are ${CMAKE_CXX_FLAGS_RELEASE}")
message("Debug   C++ flags are ${CMAKE_CXX_FLAGS_DEBUG}")
message("Build type is ${CMAKE_BUILD_TYPE}")

include_directories(.)

if(WIN32 AND ${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
endif()

message("Installation would be to ${CMAKE_INSTALL_PREFIX}/${GRAV_BIN_DIR}")

file(GLOB TEST_SRCS *.cpp)
add_executable(test ${TEST_SRCS})

target_link_libraries(test ${Boost_LIBRARIES})

if(WIN32)
else()
    target_link_libraries(test pthread)
endif()


set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 0)
#set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README.txt)
#set(CPACK_PACKAGE_EXECUTABLES gravastar;gravastar)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.txt")
#set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.txt")
set(CPACK_PACKAGE_NAME unit-thread)

