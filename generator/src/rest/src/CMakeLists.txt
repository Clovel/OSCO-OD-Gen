# 
#                     Copyright (C) 2020 Clovis Durand
# 
# -----------------------------------------------------------------------------

# Header files --------------------------------------------
file(GLOB PUBLIC_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc/*.hpp
)

file(GLOB RESOURCE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/*.hpp
)

file(GLOB_RECURSE MODULE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

set(HEADERS
    ${PUBLIC_HEADERS}
    ${MODULE_HEADERS}
    ${RESOURCE_HEADERS}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../resources/)

# Source files --------------------------------------------
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB RESOURCE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/*.cpp
)

list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

message("cpprest-api SOURCES : ${SOURCES};${RESOURCE_SOURCES}")

# Link directories ----------------------------------------

# Target definition ---------------------------------------
add_library(cpprest-api SHARED
    ${SOURCES}
    ${RESOURCE_SOURCES}
)
target_link_libraries(cpprest-api PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
)
set_target_properties(cpprest-api PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

add_executable(cpprest-api-test
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
add_dependencies(cpprest-api-test
    cpprest-api
)
target_link_libraries(cpprest-api-test PUBLIC
    cpprest-api
)

#----------------------------------------------------------------------------
# The installation is prepended by the CMAKE_INSTALL_PREFIX variable
install(TARGETS cpprest-api
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS cpprest-api-test
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
