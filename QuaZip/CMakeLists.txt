cmake_minimum_required(VERSION 2.6)

project(QuaZip)


# Use system zlib on unix and Qt ZLIB on Windows
if(UNIX)
  find_package(ZLIB REQUIRED)
else()
  set(ZLIB_INCLUDE_DIRS "Qt/4.8.6/src/3rdparty/zlib" CACHE STRING "Path to ZLIB headers of Qt")
  set(ZLIB_LIBRARIES "")
endif()

## #############################################################################
## List Sources
## #############################################################################

message ("Projet : ${PROJECT_NAME}")
message ("Current_Dir : ${CMAKE_CURRENT_SOURCE_DIR}")
list_source_files(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR})

## #############################################################################
## include directories.
## #############################################################################

list_header_directories_to_include(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} )
message("Header : ${${PROJECT_NAME}_HEADERS}")
include_directories(${${PROJECT_NAME}_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS})
set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} PARENT_SCOPE)

## #############################################################################
## Lib definition.
## #############################################################################

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_CFILES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${ZLIB_LIBRARIES})
set_lib_install_rules(${PROJECT_NAME})
