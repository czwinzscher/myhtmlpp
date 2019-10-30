add_library(doctest_main OBJECT "test_main.cpp")

set(TEST_FILES
  test_parser.cpp
  test_node.cpp
  test_tree.cpp)

foreach(file ${TEST_FILES})
  get_filename_component(file_basename ${file} NAME_WE)

  add_executable(${file_basename} $<TARGET_OBJECTS:doctest_main> ${file})
  target_link_libraries(${file_basename}
    ${MYHTMLPP_LIBRARIES}
    ${MYHTMLPP_TARGET_NAME})
  add_test(NAME "myhtmlpp_${file_basename}"
    COMMAND ${file_basename})
endforeach()

include_directories(${MYHTMLPP_INCLUDE_DIR})
