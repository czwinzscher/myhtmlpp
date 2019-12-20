cmake_minimum_required(VERSION 3.8.0)


## PROJECT

project(myhtmlpp
    VERSION 2.3.0
    DESCRIPTION "A C++ HTML parser with CSS selectors based on myhtml/modest")


## INCLUDE

include(GNUInstallDirs)


## OPTIONS

option(MYHTMLPP_USE_SYSTEM_MODEST
    "Use the system install of modest instead of the submodule if ON" OFF)
option(MYHTMLPP_BUILD_TESTS "Build myhtmlpp tests if ON." ON)
option(MYHTMLPP_BUILD_DOC "Build documentation if ON" ON)


## CONFIGURATION

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MYHTMLPP_USE_SYSTEM_MODEST)
    set(MODEST_BUILD_SHARED OFF CACHE INTERNAL "")
    set(MYHTML_LIBRARIES modest::modest_static)
else()
    set(MYHTML_LIBRARIES modest)
endif()

set(MYHTMLPP_TARGET_NAME ${PROJECT_NAME})

# these variables could be useful if this project is embedded
# inside another project
set(MYHTMLPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
set(MYHTMLPP_LIBRARIES ${MYHTMLPP_TARGET_NAME} CACHE INTERNAL "")


## TARGET

if(NOT MYHTMLPP_USE_SYSTEM_MODEST)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modest)
endif()

file(GLOB MYHTMLPP_SRCFILES src/*.cpp)
add_library(${MYHTMLPP_TARGET_NAME} STATIC ${MYHTMLPP_SRCFILES})

target_compile_options(${MYHTMLPP_TARGET_NAME} PRIVATE -Wall -Wextra -pedantic)

target_include_directories(${MYHTMLPP_TARGET_NAME}
    PUBLIC ${MYHTMLPP_INCLUDE_DIR})

target_link_libraries(${MYHTMLPP_TARGET_NAME} ${MYHTML_LIBRARIES})

set_target_properties(${MYHTMLPP_TARGET_NAME}
    PROPERTIES VERSION ${PROJECT_VERSION})


## TESTS

if(MYHTMLPP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()


## DOCUMENTATION

find_package(Doxygen)
if(MYHTMLPP_BUILD_DOC)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
    else()
        message("Doxygen need to be installed to generate the documentation.")
    endif()
endif()


## INSTALL

install(TARGETS ${MYHTMLPP_TARGET_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY ${MYHTMLPP_INCLUDE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
