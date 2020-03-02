# 
#                     Copyright (C) 2020 Clovis Durand
# 
# -----------------------------------------------------------------------------

# -----------------------------------------------
# inih ------------------------------------------
# -----------------------------------------------
file(GLOB INIH_CXX_HEADERS
    ${CMAKE_SOURCE_DIR}/deps/inih/cpp/*.h
    ${CMAKE_SOURCE_DIR}/deps/inih/cpp/*.hpp
    ${CMAKE_SOURCE_DIR}/deps/inih/*.h
    ${CMAKE_SOURCE_DIR}/deps/inih/*.hpp
)

file(GLOB INIH_CXX_SOURCES
    ${CMAKE_SOURCE_DIR}/deps/inih/*.c
    ${CMAKE_SOURCE_DIR}/deps/inih/*.cpp
    ${CMAKE_SOURCE_DIR}/deps/inih/cpp/*.c
    ${CMAKE_SOURCE_DIR}/deps/inih/cpp/*.cpp
)

message("INIH HEADERS : ${INIH_CXX_HEADERS}")
message("INIH SOURCES : ${INIH_CXX_SOURCES}")

add_library(inih SHARED
    ${INIH_CXX_SOURCES}
)
set_target_properties(inih PROPERTIES 
    PUBLIC_HEADER "${INIH_CXX_HEADERS}"
)
install(TARGETS inih
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)



