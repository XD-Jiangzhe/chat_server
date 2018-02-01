cmake_minimum_required(VERSION 3.5)
project(chat_server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_library(muduo_net muduo_net)
find_library(muduo_base_cpp11 muduo_base_cpp11)

MESSAGE(STATUS ${muduo_base_cpp11})

add_executable(chat_server chat_server.cc Codec.hpp)
target_link_libraries(${PROJECT_NAME} muduo_net muduo_base_cpp11 boost_system pthread)

add_executable(chat_client chat_client.cc Codec.hpp)
target_link_libraries(chat_client muduo_net muduo_base_cpp11 boost_system pthread)

add_executable(chat_server_effective chat_server_effective.cc)
target_link_libraries(chat_server_effective muduo_net muduo_base_cpp11 boost_system pthread)

add_executable(chat_server_highperform chat_server_highperform.cc)
target_link_libraries(chat_server_highperform muduo_net muduo_base_cpp11 boost_system pthread)