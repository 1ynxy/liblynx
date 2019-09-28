cmake_minimum_required(VERSION 3.5)
project(liblynx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(liblynx
  src/main.cpp
  
  src/inout/file.cpp
  src/inout/debug.cpp
  src/inout/node.cpp

  src/render/vulkan.cpp
)

target_include_directories(liblynx PRIVATE liblynx/)
target_include_directories(liblynx PRIVATE src/)

target_link_libraries(liblynx
  PRIVATE
    
  PUBLIC
    
)

set_target_properties(liblynx PROPERTIES PUBLIC_HEADER liblynx/liblynx.h)
