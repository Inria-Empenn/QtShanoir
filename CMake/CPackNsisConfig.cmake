set(CPACK_GENERATOR NSIS)
set(CPACK_NSIS_CONTACT "alexandre.abadie@irisa.fr")
set(CPACK_NSIS_URL_INFO_ABOUT "http://qtshanoir.gforge.inria.fr")
set(CPACK_NSIS_MODIFY_PATH "ON")
# set(CPACK_PACKAGE_ICON ${VISTAL_SOURCE_DIR}/vistalLogo.bmp)
if (BUILD_PACKAGE_BINARY)
  set(CPACK_PACKAGE_FILE_NAME "qtshanoir-runtime-${QTSHANOIR_VERSION_MAJOR}.${QTSHANOIR_VERSION_MINOR}.${QTSHANOIR_VERSION_PATCH}")
endif (BUILD_PACKAGE_BINARY)
if (BUILD_PACKAGE_SDK)
  set(CPACK_PACKAGE_FILE_NAME "qtshanoir-sdk-${QTSHANOIR_VERSION_MAJOR}.${QTSHANOIR_VERSION_MINOR}.${QTSHANOIR_VERSION_PATCH}")
endif (BUILD_PACKAGE_SDK)