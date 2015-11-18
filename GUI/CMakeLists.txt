cmake_minimum_required(VERSION 2.8.10)

project(GUI)

## #############################################################################
## List Sources.
## #############################################################################

list_source_files(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR} Resources )

## #############################################################################
## include directories.
## #############################################################################

list_header_directories_to_include(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} )

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS} ${DAO_INCLUDE_DIRS} ${QuaZip_INCLUDE_DIRS})

set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)


## #############################################################################
## Lib definition.
## #############################################################################

message("${PROJECT_NAME}_QRC ${${PROJECT_NAME}_QRC}")

qt4_add_resources(${PROJECT_NAME}_QRC ${${PROJECT_NAME}_QRC} )

message ("Gui: ${${PROJECT_NAME}_UI}")
message ("${PROJECT_NAME}_UI")
qt4_wrap_ui(${PROJECT_NAME}_UI ${${PROJECT_NAME}_UI})

message ("Gui: ${GUI_CFILES}")
message("UI : ${GUI_UI}")

add_library(${PROJECT_NAME} SHARED  ${${PROJECT_NAME}_CFILES} ${${PROJECT_NAME}_QRC} ${${PROJECT_NAME}_UI} ${${PROJECT_NAME}_MOC})

target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} DAO )
set_lib_install_rules(${PROJECT_NAME})
