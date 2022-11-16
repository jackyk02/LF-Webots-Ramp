cmake_minimum_required(VERSION 3.13)
project(webotsClient LANGUAGES C)
# Require C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DEFAULT_BUILD_TYPE Release)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE} CACHE STRING "Choose the type of build." FORCE)
endif()
set(CoreLib core)
set(PlatformLib platform)
include(${CoreLib}/platform/Platform.cmake)
include_directories(${CoreLib})
include_directories(${CoreLib}/platform)
include_directories(${CoreLib}/federated)
set(LF_MAIN_TARGET webotsClient)
# Declare a new executable target and list all its sources
add_executable(
    ${LF_MAIN_TARGET}
    webotsClient.c
    ${CoreLib}/platform/${LF_PLATFORM_FILE}
    lib/schedule.c
    lib/util.c
    lib/tag.c
    lib/time.c
    core/mixed_radix.c
    core/threaded/scheduler_NP.c
    core/utils/semaphore.c
)
# Find threads and link to it
find_package(Threads REQUIRED)
target_link_libraries( ${LF_MAIN_TARGET} Threads::Threads)
# Set the number of workers to enable threading
target_compile_definitions( ${LF_MAIN_TARGET} PUBLIC NUMBER_OF_WORKERS=0)
# Target definitions
target_compile_definitions( ${LF_MAIN_TARGET} PUBLIC LF_REACTION_GRAPH_BREADTH=1)
target_compile_definitions( ${LF_MAIN_TARGET} PUBLIC LOG_LEVEL=2)
install(
    TARGETS ${LF_MAIN_TARGET}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
include("composition.cmake")
