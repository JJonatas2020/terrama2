# QUAZIP_FOUND               - QuaZip library was found
# QUAZIP_INCLUDE_DIR         - Path to QuaZip include dir
# QUAZIP_INCLUDE_DIRS        - Path to QuaZip and zlib include dir (combined from QUAZIP_INCLUDE_DIR + ZLIB_INCLUDE_DIR)
# QUAZIP_LIBRARIES           - List of QuaZip libraries
# QUAZIP_ZLIB_INCLUDE_DIR    - The include dir of zlib headers

IF (QUAZIP_INCLUDE_DIRS AND QUAZIP_LIBRARIES)
	# in cache already
	SET(QUAZIP_FOUND TRUE)
ELSE (QUAZIP_INCLUDE_DIRS AND QUAZIP_LIBRARIES)
    IF (Qt5Core_FOUND)
        set(QUAZIP_LIB_VERSION_SUFFIX 5)
    ENDIF()
	IF (WIN32)
		FIND_PATH(QUAZIP_LIBRARY_DIR
			WIN32_DEBUG_POSTFIX d
            NAMES libquazip${QUAZIP_LIB_VERSION_SUFFIX}.dll
			HINTS "C:/Programme/" "C:/Program Files"
			PATH_SUFFIXES QuaZip/lib
		)
        FIND_LIBRARY(QUAZIP_LIBRARIES NAMES libquazip${QUAZIP_LIB_VERSION_SUFFIX}.dll HINTS ${QUAZIP_LIBRARY_DIR})
		FIND_PATH(QUAZIP_INCLUDE_DIR NAMES quazip.h HINTS ${QUAZIP_LIBRARY_DIR}/../ PATH_SUFFIXES include/quazip)
		FIND_PATH(QUAZIP_ZLIB_INCLUDE_DIR NAMES zlib.h)
	ELSE(WIN32)
		FIND_PACKAGE(PkgConfig)
#     pkg_check_modules(PC_QCA2 QUIET qca2)
		pkg_check_modules(PC_QUAZIP QUIET quazip)
		FIND_LIBRARY(QUAZIP_LIBRARIES
			WIN32_DEBUG_POSTFIX d
            NAMES quazip${QUAZIP_LIB_VERSION_SUFFIX}
			HINTS /usr/lib /usr/lib64
		)
		FIND_PATH(QUAZIP_INCLUDE_DIR quazip.h
			HINTS /usr/include /usr/local/include
			PATH_SUFFIXES quazip${QUAZIP_LIB_VERSION_SUFFIX}
		)
		FIND_PATH(QUAZIP_ZLIB_INCLUDE_DIR zlib.h HINTS /usr/include /usr/local/include)
	ENDIF (WIN32)
	INCLUDE(FindPackageHandleStandardArgs)
	SET(QUAZIP_INCLUDE_DIRS ${QUAZIP_INCLUDE_DIR} ${QUAZIP_ZLIB_INCLUDE_DIR})
	find_package_handle_standard_args(QUAZIP DEFAULT_MSG  QUAZIP_LIBRARIES QUAZIP_INCLUDE_DIR QUAZIP_ZLIB_INCLUDE_DIR QUAZIP_INCLUDE_DIRS)
ENDIF (QUAZIP_INCLUDE_DIRS AND QUAZIP_LIBRARIES)
