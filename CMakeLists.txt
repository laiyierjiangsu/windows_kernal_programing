cmake_minimum_required(VERSION 3.10)
project(WKP VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加子目录（顺序通常不重要，但依赖其他子项目的应放在后面）
add_subdirectory(server)
add_subdirectory(client)