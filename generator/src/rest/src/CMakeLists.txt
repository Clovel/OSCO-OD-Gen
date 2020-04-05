# 
#                     Copyright (C) 2020 Clovis Durand
# 
# -----------------------------------------------------------------------------

# Header files --------------------------------------------
file(GLOB PUBLIC_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc/*.hpp
)

file(GLOB_RECURSE MODULE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

set(HEADERS
    ${PUBLIC_HEADERS}
    ${MODULE_HEADERS}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc/)

# Source files --------------------------------------------
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Link directories ----------------------------------------

# Target definition ---------------------------------------
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(cpprest-api SHARED
    ${SOURCES}
)
target_link_libraries(cpprest-api
    cpprestsdk::cpprest
)
set_target_properties(cpprest-api PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

add_executable(cpprest-api-test
    main.cpp
)
add_dependencies(cpprest-api-test
    cpprest-api
)
target_link_libraries(cpprest-api-test
    cpprestsdk::cpprest
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
