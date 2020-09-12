cmake_minimum_required(VERSION 2.8.10)

set(project_name CSC10005-Project1)

project (CSC10005-Project1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*.cpp")

add_executable(${project_name} ${source_files})

enable_testing()

add_test (
    NAME test_qint
    COMMAND ${CMAKE_COMMAND}
        -D test_cmd=${PROJECT_BINARY_DIR}/${PROJECT_NAME}
        -D input_file=QInt_input.txt
        -D output_file=QInt_output.txt
        -D answer_file=QInt_answer.txt
        -D run_mode=1
        -P ${PROJECT_SOURCE_DIR}/tests/test.cmake
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
)

add_test (
    NAME test_qfloat
    COMMAND ${CMAKE_COMMAND}
        -D test_cmd=${PROJECT_BINARY_DIR}/${PROJECT_NAME}
        -D input_file=QFloat_input.txt
        -D output_file=QFloat_output.txt
        -D answer_file=QFloat_answer.txt
        -D run_mode=2
        -P ${PROJECT_SOURCE_DIR}/tests/test.cmake
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
)
