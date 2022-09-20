cmake_minimum_required(VERSION 3.20)

set(VERSIONABLE_VERSION_EXECUTABLE ON)
include(${CMAKE_CURRENT_SOURCE_DIR}/../Versionable/CMake/CMakeLists.txt)

project(${PROJECT_FULL_NAME})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB LIB_SRC "*.h" "*.cpp")
add_library(${PROJECT_NAME} ${LIB_SRC})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS *.h Implementations/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})