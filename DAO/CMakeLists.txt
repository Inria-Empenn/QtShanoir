cmake_minimum_required(VERSION 2.8.10)

project(DAO)

## #############################################################################
## List Sources
## #############################################################################

message ("Projet : ${PROJECT_NAME}")
message ("Dir : ${CMAKE_CURRENT_SOURCE_DIR}")
list_source_files(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR} )

## #############################################################################
## include directories.
## #############################################################################

message ("PROJECT_NAME : ${PROJECT_NAME}")
message ("${PROJECT_NAME}_HEADERS : ${${PROJECT_NAME}_HEADERS}")
list_header_directories_to_include(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS}) 

message ("${PROJECT_NAME}_INCLUDE_DIRS : ${${PROJECT_NAME}_INCLUDE_DIRS}")
include_directories(${${PROJECT_NAME}_INCLUDE_DIRS} ${QuaZip_INCLUDE_DIRS} )

set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)

## #############################################################################
## Lib definition.
## #############################################################################

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_CFILES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} QuaZip)
set_lib_install_rules(${PROJECT_NAME})
