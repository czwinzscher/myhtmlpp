cmake_minimum_required(VERSION 3.15.0)

project(myhtmlpp VERSION 0.0.1 DESCRIPTION "c++ wrapper for myhtml")

include(GNUInstallDirs)

option(MYHTMLPP_ENABLE_TESTS "Build myhtmlpp tests if ON." ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB MYHTMLPP_SRCFILES src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${MYHTMLPP_SRCFILES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# this variable is useful if this project is embedded inside another project
set(MYHTMLPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
target_include_directories(${PROJECT_NAME} PUBLIC ${MYHTMLPP_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} myhtml)

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION})

if(MYHTMLPP_ENABLE_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY ${MYHTMLPP_INCLUDE_DIR}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
