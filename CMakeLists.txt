cmake_minimum_required (VERSION 2.8)
project (CS5721AnthonyBrown)


# --------------------------------------------------------------------
# PNG and ZLIB
# 
# This macro will attempt to locate the PNG include directories, link
# directories and libraries. The INCLUDE_DIRECTORIES macro adds the
# resulting include directories to the search path.
# --------------------------------------------------------------------
find_package(PNG REQUIRED)
if (PNG_FOUND)
  MESSAGE(STATUS "Found png: ${PNG_INCLUDE_DIR}, ${PNG_LIBRARY}")
  INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIR})
endif (PNG_FOUND)

# ----------------------------------------------------------
# Boost
#
# This section tests for Boost support on the system. Boost is
# required as it is used heavily with this code. Boost also allows the
# code to be nicely portable across Operating Systems.
# ----------------------------------------------------------
SET (Boost_MULTITHREADED TRUE)

# If you want to get more info on what the Find Boost macro is
# doing...  
SET(Boost_DEBUG 1)

# Necessary to get Win32 version to work, plus, not a bad idea to link
# statically for our purposes.
# Cygwin can't find the static libraries on my machine, so I'm turning this
# off when running cmake on cygwin
IF(NOT CYGWIN)
	SET(Boost_USE_STATIC_LIBS TRUE)
ENDIF()
	
FIND_PACKAGE(Boost REQUIRED date_time program_options system filesystem thread unit_test_framework)
IF(${Boost_FOUND})
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ENDIF()

include_directories(${CMAKE_SOURCE_DIR}/shared/cs57s1Lib/cs5721GraphicsLib/src)
include_directories(${CMAKE_SOURCE_DIR}/shared/cs57s1Lib/cs5721GraphicsLib/src/png++)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add the src directory to build the libsive-rtutil.a library.
add_subdirectory(shared/cs57s1Lib/cs5721GraphicsLib/src)

# Add the directory to build the ablib library.
add_subdirectory(src)




add_executable(RayTracer
	RayTracer.cpp
)
target_link_libraries(RayTracer 
                      sive-rtutil
                      ablib
                      ${Boost_PROGRAM_OPTIONS_LIBRARIES}
                      ${Boost_FILESYSTEM_LIBRARIES}
                      ${Boost_THREAD_LIBRARIES}
                      ${Boost_SYSTEM_LIBRARIES}
                      ${PNG_LIBRARY}
                      ${ZLIB_LIBRARY})

add_executable(MatrixTest
	MatrixTest.cpp
)
target_link_libraries(MatrixTest 
                      sive-rtutil
                      ablib
                      ${Boost_PROGRAM_OPTIONS_LIBRARIES}
                      ${Boost_FILESYSTEM_LIBRARIES}
                      ${Boost_THREAD_LIBRARIES}
                      ${Boost_SYSTEM_LIBRARIES}
                      pthread
                      ${PNG_LIBRARY}
                      ${ZLIB_LIBRARY})