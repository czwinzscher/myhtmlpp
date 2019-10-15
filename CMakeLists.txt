cmake_minimum_required(VERSION 3.8.0)


## PROJECT

project(myhtmlpp VERSION 0.0.1 DESCRIPTION "c++ wrapper for myhtml")


## INCLUDE

include(GNUInstallDirs)


## OPTIONS

option(MYHTMLPP_BUILD_TESTS "Build myhtmlpp tests if ON." ON)


## CONFIGURATION

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MYHTMLPP_TARGET_NAME ${PROJECT_NAME})

# these variables could be useful if this project is embedded inside another project
set(MYHTMLPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
set(MYHTMLPP_LIBRARIES myhtml CACHE INTERNAL "")


## TARGET

file(GLOB MYHTMLPP_SRCFILES src/*.cpp)
add_library(${MYHTMLPP_TARGET_NAME} STATIC ${MYHTMLPP_SRCFILES})

target_compile_options(${MYHTMLPP_TARGET_NAME} PRIVATE -Wall -Wextra -pedantic)

target_include_directories(${MYHTMLPP_TARGET_NAME} PUBLIC ${MYHTMLPP_INCLUDE_DIR})

target_link_libraries(${MYHTMLPP_TARGET_NAME} ${MYHTMLPP_LIBRARIES})

set_target_properties(${MYHTMLPP_TARGET_NAME} PROPERTIES VERSION ${PROJECT_VERSION})


## TESTS

if(MYHTMLPP_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()


## INSTALL

install(TARGETS ${MYHTMLPP_TARGET_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY ${MYHTMLPP_INCLUDE_DIR}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
