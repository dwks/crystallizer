# Enable warnings
add_definitions(-W -Wall -ansi -pedantic -g -O3)
add_definitions(-Wno-unused-parameter -Wno-long-long)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# List of all source directories
aux_source_directory(hive HIVE_SOURCES)
aux_source_directory(network NETWORK_SOURCES)
aux_source_directory(worker WORKER_SOURCES)

# Source groups, for e.g. Visual Studio
source_group("hive" FILES ${HIVE_SOURCES})
source_group("network" FILES ${NETWORK_SOURCES})
source_group("worker" FILES ${WORKER_SOURCES})

# More general source variables
set(CORE_SOURCES
    ${NETWORK_SOURCES})
set(HIVE_TARGET_SOURCES
    ${HIVE_SOURCES})
set(WORKER_TARGET_SOURCES
    ${WORKER_SOURCES})

# Boost
find_package(Boost COMPONENTS signals system thread)
include_directories(${Boost_INCLUDE_DIRS})

# Libraries and executables
set(CORE_LIBRARY core)
add_library(${CORE_LIBRARY} ${CORE_SOURCES})

set(HIVE_TARGET hive)
set(WORKER_TARGET worker)
add_executable(${HIVE_TARGET} ${HIVE_TARGET_SOURCES})
add_executable(${WORKER_TARGET} ${WORKER_TARGET_SOURCES})

set(COMMON_LIBRARIES ${CORE_LIBRARY} ${Boost_LIBRARIES})
target_link_libraries(${HIVE_TARGET} ${COMMON_LIBRARIES})
target_link_libraries(${WORKER_TARGET} ${COMMON_LIBRARIES})

