project(webotsClient)
target_include_directories(webotsClient PUBLIC "$ENV{WEBOTS_HOME}/include/controller/c")
# target_link_libraries(webotsClient /lib/libController.so)

find_library(LIBRARIES
    NAMES ${CMAKE_SHARED_LIBRARY_PREFIX}Controller${CMAKE_SHARED_LIBRARY_SUFFIX}
    HINTS "$ENV{WEBOTS_HOME}/include/controller/c"
)
target_link_libraries(webotsClient ${LIBRARIES})


if(NOT LIBRARIES)
  message(FATAL_ERROR "controller library not found")
endif()

