# CMake build script for the c-arel project
#
# Building (out of source build):
# > mkdir build && cd build
# > cmake .. [-DSETTINGS=VALUE]
# > cmake --build .
#
# Testing:
# > ctest -V
#
# Install:
# > cmake --build . --target install

PROJECT(c-arel)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FILE(STRINGS "include/c-arel/version.h" C_AREL_HEADER REGEX "^#define C_AREL_VERSION \"[^\"]*\"$")

STRING(REGEX REPLACE "^.*C_AREL_VERSION \"([0-9]+).*$" "\\1" C_AREL_VERSION_MAJOR "${C_AREL_HEADER}")
STRING(REGEX REPLACE "^.*C_AREL_VERSION \"[0-9]+\\.([0-9]+).*$" "\\1" C_AREL_VERSION_MINOR  "${C_AREL_HEADER}")
STRING(REGEX REPLACE "^.*C_AREL_VERSION \"[0-9]+\\.[0-9]+\\.([0-9]+).*$" "\\1" C_AREL_VERSION_REV "${C_AREL_HEADER}")
SET(C_AREL_VERSION_STRING "${C_AREL_VERSION_MAJOR}.${C_AREL_VERSION_MINOR}.${C_AREL_VERSION_REV}")

# Find required dependencies
INCLUDE_DIRECTORIES(src include deps/variant)

# Installation paths
SET(INSTALL_BIN bin CACHE PATH "Where to install binaries to.")
SET(INSTALL_LIB lib CACHE PATH "Where to install libraries to.")
SET(INSTALL_INC include CACHE PATH "Where to install headers to.")

# Build options
OPTION (BUILD_SHARED_LIBS "Build Shared Library (OFF for Static)" ON)
OPTION (THREADSAFE "Build c-arel as threadsafe" OFF)
OPTION (BUILD_TESTS "Build Tests" ON)
OPTION (BUILD_CLAY "Build Tests using the Clay suite" OFF)

# Platform specific compilation flags
IF (MSVC)
  # Not using __stdcall with the CRT causes problems
  OPTION (STDCALL "Buildl c-arel with the __stdcall convention" ON)

  SET(CMAKE_C_FLAGS "/W4 /nologo /Zi ${CMAKE_C_FLAGS}")
  IF (STDCALL)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Gz")
  ENDIF ()
  # TODO: bring back /RTC1 /RTCc
  SET(CMAKE_C_FLAGS_DEBUG "/Od /DEBUG /MTd")
  SET(CMAKE_C_FLAGS_RELEASE "/MT /O2")
  SET(WIN_RC "src/win32/c-arel.rc")
ELSE ()
  SET(CMAKE_C_FLAGS "-O2 -g -Wall -Wextra -Wno-missing-field-initializers -Wstrict-aliasing=2 -Wstrict-prototypes -Wmissing-prototypes ${CMAKE_C_FLAGS}")
  SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")
  IF (NOT MINGW) # MinGW always does PIC and complains if we tell it to
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  ENDIF ()
ENDIF()

# Build Debug by default
IF (NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF ()

IF (THREADSAFE)
  IF (NOT WIN32)
    find_package(Threads REQUIRED)
  ENDIF()

  ADD_DEFINITIONS(-DGIT_THREADS)
ENDIF()

ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64)

# Collect sourcefiles
FILE(GLOB SRC_H include/c-arel/*.h include/c-arel/managers/*.h include/c-arel/nodes/*.h include/c-arel/visitors/*.h)
FILE(GLOB SRC src/*.cpp src/managers/*.cpp src/nodes/*.cpp src/visitors/*.cpp)

# Compile and link c-arel
ADD_LIBRARY(c-arel ${SRC} ${WIN_RC})

TARGET_LINK_LIBRARIES(c-arel ${CMAKE_THREAD_LIBS_INIT})
SET_TARGET_PROPERTIES(c-arel PROPERTIES VERSION ${C_AREL_VERSION_STRING})
SET_TARGET_PROPERTIES(c-arel PROPERTIES SOVERSION ${C_AREL_VERSION_MAJOR})
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/c-arel.pc.in ${CMAKE_CURRENT_BINARY_DIR}/c-arel.pc @ONLY)
SET_TARGET_PROPERTIES(c-arel PROPERTIES LINKER_LANGUAGE C)

