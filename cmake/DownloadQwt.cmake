# Download and unpack Qwt at configure time
configure_file(${CMAKE_CURRENT_LIST_DIR}/CMakeLists.Qwt.txt.in
               ${CMAKE_BINARY_DIR}/qwt-download/CMakeLists.txt)

execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/qwt-download"
)
if(result)
  message(FATAL_ERROR "CMake step for qwt failed: ${result}")
endif()

execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/qwt-download"
)
if(result)
  message(FATAL_ERROR "Build step for qwt failed: ${result}")
endif()
