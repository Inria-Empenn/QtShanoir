cmake_minimum_required(VERSION 2.8.10)

project(qtshanoir-demo)

## #############################################################################
## List Sources
## #############################################################################

list_source_files(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR} )

## #############################################################################
## include directorie.
## #############################################################################


include_directories(${${PROJECT_NAME}_INCLUDE_DIRS} ${QuaZip_INCLUDE_DIRS} ${DAO_INCLUDE_DIRS} ${GUI_INCLUDE_DIRS} )

## #############################################################################
## Translate.
## #############################################################################



## #############################################################################
## Lib definition.
## #############################################################################

qt4_wrap_ui(${PROJECT_NAME}_UI ${${PROJECT_NAME}_UI} )

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_CFILES}
  ${${PROJECT_NAME}_UI}
  ${qm_files}
  )

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  DAO GUI
  )
message("lib ${QT_LIBRARIES}") 

set_exe_install_rules(${PROJECT_NAME})
