# 
#                     Copyright (C) 2020 Clovis Durand
# 
# -----------------------------------------------------------------------------

# CMake version required ----------------------------------
cmake_minimum_required(VERSION 3.0)
project(osco-od-gen)

# Project definition --------------------------------------
if(NOT DEFINED PRJ_VERSION)
    set(PRJ_VERSION "1.0.0")
endif(NOT DEFINED PRJ_VERSION)

#------------------------------------------------------------------------------
# Build definition (to do before calling 'project()')
#------------------------------------------------------------------------------

# Build type
if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
    FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG=1)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

message(STATUS "Build type is : ${CMAKE_BUILD_TYPE}")

# CASE OF C PROJECT
set(CMAKE_C_STANDARD 99)
if(NOT CMAKE_C_FLAGS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wformat-security -pedantic" CACHE STRING "C99 compilation flags" FORCE)
endif(NOT CMAKE_C_FLAGS)

# CASE OF CPP PROJECT
set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_CXX_FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat-security -pedantic" CACHE STRING "C++17 compilation flags" FORCE)
endif(NOT CMAKE_CXX_FLAGS)

#------------------------------------------------------------------------------
# Project definition, variable and dependencies 
#------------------------------------------------------------------------------

set(CMAKE_PROJECT_NAME ${PROJECT_NAME})
set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_PROJECT_BRIEF "OSCO Object Disctionary generator")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/dest CACHE PATH "" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Allow CTest
enable_testing()

# Allow subdirectory test and docs
option(ENABLE_TESTS "Enable Tests" 1)
option(ENABLE_EXAMPLES "Enable Examples" 1)

# Doxygen dependency
find_package(Doxygen)
option(ENABLE_DOCS "Build API documentation" ${DOXYGEN_FOUND})

# OpenSSL dependency
# if(APPLE)
#     SET(ENV{OPENSSL_ROOT_DIR} /usr/local/Cellar/openssl@1.1/)
# endif(APPLE)
# find_package(OpenSSL REQUIRED)
# if(OPENSSL_FOUND)
#     if(APPLE)
#         include_directories(/usr/local/Cellar/openssl@1.1/include)
#         list(APPEND LIB_LIST /usr/local/Cellar/openssl@1.1/lib/libssl.dylib)
#         list(APPEND LIB_LIST /usr/local/Cellar/openssl@1.1/lib/libcrypto.dylib)
#         message(STATUS "OpenSSL Version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
#     else(APPLE)
#         include_directories(${OPENSSL_INCLUDE_DIR})
#         list(APPEND LIB_LIST ${OPENSSL_LIBRARIES})
#         message(STATUS "OpenSSL Version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
#     endif(APPLE)
# endif(OPENSSL_FOUND)

# cpprest dependency
if(UNIX)
    if(NOT APPLE)
        set(CMAKE_PREFIX_PATH /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
        # set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
    else(NOT APPLE)
        set(CMAKE_PREFIX_PATH /usr/local/opt/cpprestsdk/lib/cmake/)
        set(cpprestsdk_DIR /usr/local/opt/cpprestsdk/lib/cmake/)
    endif(NOT APPLE)
endif(UNIX)
# if(APPLE)
#     find_package(cpprestsdk REQUIRED PATH /usr/local/Cellar/cpprestsdk/2.10.15/lib/cmake/cpprestsdk)
# else(APPLE)
#     find_package(cpprestsdk REQUIRED)
# endif(APPLE)

message(STATUS "CMAKE_PREFIX_PATH : ${CMAKE_PREFIX_PATH}")
find_package(cpprestsdk REQUIRED)
if(cpprestsdk_FOUND)
    message(STATUS "=====================================")
    message(STATUS "cpprestsdk_DIR : ${cpprestsdk_DIR}")
    message(STATUS "cpprestsdk Version: ${cpprestsdk_VERSION} ${cpprestsdk_INCLUDE_DIRS} ${cpprestsdk_LIBRARIES}")
    message(STATUS "CPPRESTSDK Version: ${CPPRESTSDK_VERSION} ${CPPRESTSDK_INCLUDE_DIRS} ${CPPRESTSDK_LIBRARIES}")
    message(STATUS "CPP_REST Version: ${CPP_REST_VERSION} ${CPP_REST_INCLUDE_DIRS} ${CPP_REST_LIBRARIES}")
    message(STATUS "cpp_rest Version: ${cpp_rest_VERSION} ${cpp_rest_INCLUDE_DIRS} ${cpp_rest_LIBRARIES}")
    message(STATUS "cpprest Version: ${cpprest_VERSION} ${cpprest_INCLUDE_DIRS} ${cpprest_LIBRARIES}")
    message(STATUS "CPPREST Version: ${CPPREST_VERSION} ${CPPREST_INCLUDE_DIRS} ${CPPREST_LIBRARIES}")
    message(STATUS "casablanca Version: ${casablanca_VERSION} ${casablanca_INCLUDE_DIRS} ${casablanca_LIBRARIES}")
    message(STATUS "Casablanca Version: ${Casablanca_VERSION} ${Casablanca_INCLUDE_DIRS} ${Casablanca_LIBRARIES}")
    message(STATUS "=====================================")
    message(STATUS "cpprestsdk_DIR : ${cpprestsdk_DIR}")
    message(STATUS "cpprestsdk Version: ${cpprestsdk_VERSION} ${cpprestsdk_INCLUDES} ${cpprestsdk_LIBRARIES}")
    message(STATUS "CPPRESTSDK Version: ${CPPRESTSDK_VERSION} ${CPPRESTSDK_INCLUDES} ${CPPRESTSDK_LIBRARIES}")
    message(STATUS "CPP_REST Version: ${CPP_REST_VERSION} ${CPP_REST_INCLUDES} ${CPP_REST_LIBRARIES}")
    message(STATUS "cpp_rest Version: ${cpp_rest_VERSION} ${cpp_rest_INCLUDES} ${cpp_rest_LIBRARIES}")
    message(STATUS "cpprest Version: ${cpprest_VERSION} ${cpprest_INCLUDES} ${cpprest_LIBRARIES}")
    message(STATUS "CPPREST Version: ${CPPREST_VERSION} ${CPPREST_INCLUDES} ${CPPREST_LIBRARIES}")
    message(STATUS "casablanca Version: ${casablanca_VERSION} ${casablanca_INCLUDES} ${casablanca_LIBRARIES}")
    message(STATUS "Casablanca Version: ${Casablanca_VERSION} ${Casablanca_INCLUDES} ${Casablanca_LIBRARIES}")
    message(STATUS "=====================================")
    message(STATUS "INTERACE_INCLUDE_DIRECTORIES : ${INTERACE_INCLUDE_DIRECTORIES}")
    message(STATUS "INTERACE_LINK_DIRECTORIES : ${INTERACE_LINK_DIRECTORIES}")
    message(STATUS "=====================================")
endif(cpprestsdk_FOUND)

#------------------------------------------------------------------------------
# pkg-config dependencies
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Project version
#------------------------------------------------------------------------------

# Get the latest abbreviated commit hash of the working branch
execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX REPLACE
    "^([\\.0-9]+).*"
    "\\1"
    tmp_VERSION
    "${PRJ_VERSION}"
)
  
string(REGEX REPLACE
    "^([0-9]+)\\..*"
    "\\1"
    tmp_SOVERSION
    "${tmp_VERSION}"
)

# Major version is for product/marketing purpose
set(MAJ_MIN_VERSION ${tmp_VERSION} CACHE STRING "Major and minor version" FORCE)

set(RELEASE_VERSION ${tmp_SOVERSION} CACHE STRING "Release version" FORCE)

# Build version is generated using the hash of the current commit build with
set(BUILD_VERSION ${GIT_COMMIT_HASH} CACHE STRING "Build version" FORCE)

#------------------------------------------------------------------------------
# pkgconfig
#------------------------------------------------------------------------------

find_package(PkgConfig REQUIRED)
if(PKG_CONFIG_FOUND)
    # Produce a pkg-config file
    configure_file (
        ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pc.in
        ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pc
        @ONLY
    )
    install (
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pc    
        DESTINATION lib/pkgconfig
    )
endif(PKG_CONFIG_FOUND)

#------------------------------------------------------------------------------
# Project configuration 
#------------------------------------------------------------------------------

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/initools/inc
)

#------------------------------------------------------------------------------
# Sub-directories 
#------------------------------------------------------------------------------

# Dependencies
add_subdirectory(deps)

# Main build
add_subdirectory(src)

# Builds dependent on main build
if(ENABLE_TESTS)
    message(STATUS "TESTS enabled")
    add_subdirectory(tests)
else()
    message(STATUS "TESTS disabled")
endif(ENABLE_TESTS)

if(ENABLE_DOCS)
    message(STATUS "DOCS enabled")
    add_subdirectory(docs)
else()
    message(STATUS "DOCS disabled")
endif (ENABLE_DOCS)

#------------------------------------------------------------------------------
# Gencov custom command
#------------------------------------------------------------------------------

set(COVERITY_FILES
  " ${CMAKE_CURRENT_SOURCE_DIR}/build-coverity/output/summary.txt"
)

add_custom_command(OUTPUT ${COVERITY_FILES}
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR} mkdir -p build-coverity
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR} cov-configure --gcc
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR} cov-build --dir build-coverity make -j $(nproc)
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR} cov-analyze --dir build-coverity --all --aggressiveness-level low --misra-config MISRA_c2012_MM.config
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR} cov-commit-defects --dir build-coverity --host coverity3.freescale.net --user committer --password CoverityGuest --stream lib${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E touch ${COVERITY_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "run coverity"
)
add_custom_target(${CMAKE_PROJECT_NAME}-coverity DEPENDS ${COVERITY_FILES})
