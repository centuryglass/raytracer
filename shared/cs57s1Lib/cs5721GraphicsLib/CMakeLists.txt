cmake_minimum_required (VERSION 2.8)
project (CS5721Graphics)

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
# SET(Boost_DEBUG 1)

# Necessary to get Win32 version to work, plus, not a bad idea to link
# statically for our purposes.
SET(Boost_USE_STATIC_LIBS TRUE)

FIND_PACKAGE(Boost REQUIRED date_time program_options system thread unit_test_framework)
IF(${Boost_FOUND})
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ENDIF()

# Add the src directory to build the libsive-rtutil.a library.
add_subdirectory(src)

# If you want, we can also compile the tests directory that are
# essentially examples for how to use some of the classes and code.
add_subdirectory(tests)

#
# OpenGL Example
#
# This builds a simple OpenGL example that you can use to get started with OpenGL.
#
add_subdirectory(OpenGL)

#
# Unit Tests - by enabling testing with cmake, we can create a target
# that lets unit tests be run. After re-building yourproject with
# ENABLE_TESTING called, a make target, called test will be
# enabled. You can then type
# 
#  make test
#
# to perform the unit tests. See the CMakeLists.txt file in the utests
# directory for more details. Also, see the unit test .cpp files in
# the utests directory for examples on using Boost's unit test system.
#
ENABLE_TESTING()
add_subdirectory(utests)
