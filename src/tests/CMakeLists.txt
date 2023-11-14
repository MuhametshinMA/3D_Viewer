cmake_minimum_required(VERSION 3.8)

project(3DViewer2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")
# -fsanitize=address

include_directories(../model)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        3DViewer2_tests
        tests.cc
)

target_link_libraries(
        3DViewer2_tests
        ModelLib
        GTest::gtest_main
)

add_library(ModelLib SHARED
        ${CMAKE_SOURCE_DIR}/../model/affine_command.h
        ${CMAKE_SOURCE_DIR}/../model/affine_invoker.h
        ${CMAKE_SOURCE_DIR}/../model/data_object.h
        ${CMAKE_SOURCE_DIR}/../model/exceptions.h
        ${CMAKE_SOURCE_DIR}/../model/i_model.h
        ${CMAKE_SOURCE_DIR}/../model/i_parser.h
        ${CMAKE_SOURCE_DIR}/../model/min_max_values.h
        ${CMAKE_SOURCE_DIR}/../model/model.cc
        ${CMAKE_SOURCE_DIR}/../model/model.h
        ${CMAKE_SOURCE_DIR}/../model/object_info.h
        ${CMAKE_SOURCE_DIR}/../model/parser_factory.h
        ${CMAKE_SOURCE_DIR}/../model/parser.h
        ${CMAKE_SOURCE_DIR}/../model/type_command.h
        ${CMAKE_SOURCE_DIR}/../model/type_data_object.h
)

include(GoogleTest)
gtest_discover_tests(3DViewer2_tests)
