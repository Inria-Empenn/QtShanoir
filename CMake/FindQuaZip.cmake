#
#  FindQuaZip.h
#  StackManagerQt/cmake/modules
#
#  Created by Mohammed Nafees.
#  Copyright (c) 2014 High Fidelity. All rights reserved.
# 

# QUAZIP_FOUND               - QuaZip library was found
# QUAZIP_INCLUDE_DIR         - Path to QuaZip include dir
# QUAZIP_INCLUDE_DIRS        - Path to QuaZip and zlib include dir (combined from QUAZIP_INCLUDE_DIR + ZLIB_INCLUDE_DIR)
# QUAZIP_LIBRARIES           - List of QuaZip libraries
# QUAZIP_ZLIB_INCLUDE_DIR    - The include dir of zlib headers


if(QUAZIP_INCLUDE_DIRS AND QUAZIP_LIBRARIES)
    set(QUAZIP_FOUND TRUE)
else(QUAZIP_INCLUDE_DIRS AND QUAZIP_LIBRARIES)
    set(QUAZIP_SEARCH_DIRS "$ENV{HIFI_LIB_DIR}/QuaZip")
    if (WIN32)
        find_path(QUAZIP_INCLUDE_DIRS quazip.h PATH_SUFFIXES include/quazip HINTS ${QUAZIP_SEARCH_DIRS})
        find_library(QUAZIP_LIBRARIES NAMES quazip PATH_SUFFIXES lib HINTS ${QUAZIP_SEARCH_DIRS})
    elseif(APPLE)
        find_path(QUAZIP_INCLUDE_DIRS quazip.h PATH_SUFFIXES include/quazip HINTS ${QUAZIP_SEARCH_DIRS})
        find_library(QUAZIP_LIBRARIES NAMES quazip PATH_SUFFIXES lib HINTS ${QUAZIP_SEARCH_DIRS})
    else ()
        find_path(QUAZIP_INCLUDE_DIRS quazip.h PATH_SUFFIXES quazip HINTS ${QUAZIP_SEARCH_DIRS})
        find_library(QUAZIP_LIBRARIES NAMES quazip-qt5 PATH_SUFFIXES lib HINTS ${QUAZIP_SEARCH_DIRS})
    endif ()
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(QUAZIP DEFAULT_MSG QUAZIP_INCLUDE_DIRS QUAZIP_LIBRARIES)
endif (QUAZIP_INCLUDE_DIRS AND QUAZIP_LIBRARIES)
