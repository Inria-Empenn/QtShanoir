cmake_minimum_required(VERSION 2.6)

project(QTSHANOIR)

set(QTSHANOIR_VERSION_MAJOR "0")
set(QTSHANOIR_VERSION_MINOR "1")
set(QTSHANOIR_VERSION_PATCH "0")

add_definitions(-g -Wno-deprecated)

# option(BUILD_DOCUMENTATION "Build QtShanoir Documentation" OFF)
option(BUILD_PACKAGE "Configure QtShanoir packaging" OFF)
option(BUILD_DEMO "Build example application" OFF)
option(BUILD_SHARED_LIBS "Build QtShanoir with shared libraries." ON)

if (BUILD_PACKAGE)
  include (${QTSHANOIR_SOURCE_DIR}/CMake/CPackConfig.cmake)
endif(BUILD_PACKAGE)

set(EXECUTABLE_OUTPUT_PATH "${QTSHANOIR_BINARY_DIR}/bin")
if (WIN32 AND BUILD_SHARED_LIBS)
  set(LIBRARY_OUTPUT_PATH "${QTSHANOIR_BINARY_DIR}/bin")
else (WIN32 AND BUILD_SHARED_LIBS)
  set(LIBRARY_OUTPUT_PATH "${QTSHANOIR_BINARY_DIR}/lib")
endif (WIN32 AND BUILD_SHARED_LIBS)
mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

#Configure doxygen documentation
# if(BUILD_DOCUMENTATION)
#   subdirs(Documentation/Doxygen)
# endif(BUILD_DOCUMENTATION)

set (QTSHANOIR_CMAKE_MODULE_PATH ${QTSHANOIR_SOURCE_DIR}/CMake)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${QTSHANOIR_CMAKE_MODULE_PATH}")

include (${QTSHANOIR_SOURCE_DIR}/CMake/QtShanoirSettings.cmake)

find_package( Qt4 REQUIRED COMPONENTS QtCore QtGui QtNetwork QtXml)
if(QT4_FOUND)
  set(QT_USE_QTNETWORK true)
  set(QT_USE_QTXML true)
  include(${QT_USE_FILE})
endif(QT4_FOUND)

set(QTSHANOIR_RCCS
    ${QTSHANOIR_SOURCE_DIR}/Resources/qtshanoir.qrc
)

set(SAMPLE_SRCS
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirSettingsWidget.cpp
#  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirWsQuery.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/wsquery.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirProgressWidget.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirTreeWidget.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoir.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtSoap.cpp
)

set(SAMPLE_HDRS
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirSettingsWidget.h
#  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirWsQuery.h
  ${QTSHANOIR_SOURCE_DIR}/Code/wsquery.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirProgressWidget.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirTreeWidget.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoir.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtSoap.h
)

set(SAMPLE_UIS
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoir.ui
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoirprogress.ui
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoirsettingswidget.ui
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoirtreewidget.ui
)

set(SAMPLE_MOC_HDRS ${SAMPLE_HDRS})

set(QTSHANOIR_SRCS
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirSettings.cpp
)

qt4_add_resources(QTSHANOIR_RCC_SRCS ${QTSHANOIR_RCCS})
qt4_wrap_ui( SAMPLE_UI_HDRS ${SAMPLE_UIS})
qt4_wrap_cpp( SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS})


include_directories(${CMAKE_BINARY_DIR} ${QTSHANOIR_SOURCE_DIR}/Code/ ${QTSHANOIR_BINARY_DIR})
add_library( qtshanoir ${QTSHANOIR_SRCS} ${SAMPLE_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_UI_HDRS} ${QTSHANOIR_RCC_SRCS})
target_link_libraries( qtshanoir ${QT_LIBRARIES} ${QT_QTNETWORK_LIBRARY} ${QT_QTXML_LIBRARY})


# External inclusion stuff :
set(QTSHANOIR_USE_FILE ${QTSHANOIR_BINARY_DIR}/UseQtShanoir.cmake)
set(QTSHANOIR_LIBRARY_DEPENDS_FILE ${QTSHANOIR_BINARY_DIR}/QtShanoirLibraryDepends.cmake)
set(QTSHANOIR_BUILD_SETTINGS_FILE ${QTSHANOIR_BINARY_DIR}/QtShanoirBuildSettings.cmake)
# Copy the UseQtShanoir.cmake file to the binary tree for backward compatability.
configure_file(${QTSHANOIR_SOURCE_DIR}/CMake/UseQtShanoir.cmake.in
              ${QTSHANOIR_BINARY_DIR}/UseQtShanoir.cmake)
configure_file(${QTSHANOIR_SOURCE_DIR}/CMake/QtShanoirConfig.cmake.in
              ${QTSHANOIR_BINARY_DIR}/QtShanoirConfig.cmake)

if(BUILD_DEMO)
subdirs(Demo)
endif(BUILD_DEMO)
