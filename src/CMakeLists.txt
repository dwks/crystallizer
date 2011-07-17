# Enable warnings
add_definitions(-W -Wall -ansi -pedantic -g -O3)
add_definitions(-Wno-unused-parameter -Wno-long-long)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# List of all source directories
aux_source_directory(client CLIENT_SOURCES)
aux_source_directory(network NETWORK_SOURCES)
aux_source_directory(server SERVER_SOURCES)

# Source groups, for e.g. Visual Studio
source_group("client" FILES ${CLIENT_SOURCES})
source_group("network" FILES ${NETWORK_SOURCES})
source_group("server" FILES ${SERVER_SOURCES})

# More general source variables
set(CORE_SOURCES
    ${NETWORK_SOURCES})
set(CLIENT_TARGET_SOURCES
    ${CLIENT_SOURCES})
set(SERVER_TARGET_SOURCES
    ${SERVER_SOURCES})

# Boost
find_package(Boost COMPONENTS signals system thread)
include_directories(${Boost_INCLUDE_DIRS})

# Libraries and executables
set(CORE_LIBRARY core)
add_library(${CORE_LIBRARY} ${CORE_SOURCES})

set(CLIENT_TARGET client)
set(SERVER_TARGET server)
add_executable(${CLIENT_TARGET} ${CLIENT_TARGET_SOURCES})
add_executable(${SERVER_TARGET} ${SERVER_TARGET_SOURCES})

set(COMMON_LIBRARIES ${CORE_LIBRARY} ${Boost_LIBRARIES})
target_link_libraries(${CLIENT_TARGET} ${COMMON_LIBRARIES})
target_link_libraries(${SERVER_TARGET} ${COMMON_LIBRARIES})

