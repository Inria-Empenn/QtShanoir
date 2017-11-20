cmake_minimum_required(VERSION 2.6)

project(QTSHANOIRDEMO)

add_definitions(-g -Wno-deprecated)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${QTSHANOIRDEMO_SOURCE_DIR}")
set (QTSHANOIR_DIR "${QTSHANOIR_BINARY_DIR}")

find_package(QTSHANOIR REQUIRED)
if (QTSHANOIR_FOUND)
  include(${QTSHANOIR_USE_FILE})
endif (QTSHANOIR_FOUND)

set(DEMO_SRCS
  ${QTSHANOIRDEMO_SOURCE_DIR}/main.cpp
  ${QTSHANOIRDEMO_SOURCE_DIR}/Demo.cpp
)

set(DEMO_UIS
  ${QTSHANOIRDEMO_SOURCE_DIR}/demo.ui
)

include_directories(${CMAKE_BINARY_DIR} ${QTSHANOIR_INCLUDE_DIR} ${QTSHANOIR_DIR} ${QTSHANOIRDEMO_SOURCE_DIR} ${QTSHANOIRDEMO_BINARY_DIR})

add_executable(qtshanoirdemo
  ${DEMO_SRCS}
  ${DEMO_UIS}
  )
target_link_libraries(qtshanoirdemo
  ${QTSHANOIR_LIBS}
  )
