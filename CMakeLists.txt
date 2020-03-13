cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

# set the project name
project(TcpLib)

# add the executable
add_executable(TcpLib  main.cpp Packet.cpp TcpListener.cpp TcpSocket.cpp SocketUtils.cpp)

target_compile_options(TcpLib PRIVATE -fexceptions -g)

