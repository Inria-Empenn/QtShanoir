cmake_minimum_required(VERSION 2.8.10)
project(qtshanoir)


## #############################################################################
## Version number.
## #############################################################################

set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_VERSION
    ${PROJECT_NAME}_VERSION_MAJOR.${PROJECT_NAME}_VERSION_MINOR.${PROJECT_NAME}_VERSION_PATCH
    )
add_definitions(-D${PROJECT_NAME}_VERSION="${${PROJECT_NAME}_VERSION}")


## #############################################################################
## Additionals modules
## #############################################################################

set(${PROJECT_NAME}_CMAKE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules
  )

set(CMAKE_MODULE_PATH
  ${${PROJECT_NAME}_CMAKE_DIR}
  ${CMAKE_MODULE_PATH}
  )

include(list_source_files)
include(list_header_directories_to_include)
include(set_lib_install_rules)
include(set_exe_install_rules)




## #############################################################################
## Find packages.
## #############################################################################

# Find the Qt library
find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtNetwork REQUIRED)
include(${QT_USE_FILE})
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTXML TRUE)

## #############################################################################
## Qt Automoc
## #############################################################################

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
#   Find includes in corresponding build (and source) directories
#   (nedded for generated files)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
message("automoc")
#SET (BUILD_SHARED_LIBS  TRUE)


## #############################################################################
## Configure libs
## #############################################################################

message("I'm in quazip")
add_subdirectory(QuaZip)
message("I'm in dao")
add_subdirectory(DAO)
message("I'm in gui")
add_subdirectory(GUI)

## #############################################################################
## Configure the demo
## #############################################################################

message("${PROJECT_NAME}_INCLUDE_DIRS from Main ${${PROJECT_NAME}_INCLUDE_DIRS}")

option(BUILD_DEMO "Build example application" ON)

if(BUILD_DEMO)
  add_subdirectory(Demo)
endif(BUILD_DEMO)
