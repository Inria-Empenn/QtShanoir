# - Find an QtShanoir installation or build tree.

# When QtShanoir is found, the QtShanoirConfig.cmake file is sourced to setup the
# location and configuration of QtShanoir.  Please read this file, or
# VistalConfig.cmake.in from the QtShanoir source tree for the full list of
# definitions.  Of particular interest is QtShanoir_USE_FILE, a CMake source file
# that can be included to set the include directories, library directories,
# and preprocessor macros.  In addition to the variables read from
# QtShanoirConfig.cmake, this find module also defines
#  QTSHANOIR_DIR  - The directory containing VistalConfig.cmake.  
#             This is either the root of the build tree
#
#  QtShanoir_FOUND - Whether Vistal was found.  If this is true, 
#              QtShanoir_DIR is okay.
#
#  USE_QTSHANOIR_FILE - The full path to the UseVistal.cmake file.  
#                 This is provided for backward 
#                 compatability.  Use QtShanoir_USE_FILE
#                 instead.

FIND_PATH(QTSHANOIR_DIR UseQtShanoir.cmake 
  /usr/lib/qtshanoir-0.1 
  /usr/local/lib/qtshanoir-0.1
  /home/aabadie/Softs/builds/qtshanoir2
  DOC "QTSHANOIR directory")

SET(QTSHANOIR_CONFIG_FILE ${QTSHANOIR_DIR}/QtShanoirConfig.cmake)
SET(QTSHANOIR_USE_FILE ${QTSHANOIR_DIR}/UseQtShanoir.cmake)
# path is okay
IF (EXISTS ${QTSHANOIR_CONFIG_FILE})
  SET(QTSHANOIR_FOUND 1)
  INCLUDE (${QTSHANOIR_CONFIG_FILE})
  INCLUDE (${QTSHANOIR_USE_FILE})
ELSE (EXISTS ${QTSHANOIR_CONFIG_FILE})
  SET(QTSHANOIR_FOUND 0)
  IF(QTSHANOIR_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Please set QTSHANOIR_DIR to the correct value")
  ENDIF(QTSHANOIR_FIND_REQUIRED)
ENDIF (EXISTS ${QTSHANOIR_CONFIG_FILE})
