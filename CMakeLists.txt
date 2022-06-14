cmake_minimum_required(VERSION 3.20)

SET(CMAKE_C_COMPILER "/usr/local/bin/gcc-11")
SET(CMAKE_CXX_COMPILER "/usr/local/bin/g++-11")

project(Learning-Cpp C CXX)

set(CMAKE_CXX_STANDARD 17)

set(MAIN_PATH ${PROJECT_SOURCE_DIR})

configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in @ONLY)

# 条件判断
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0 -L/usr/local/lib")
    message("Debug mode:${CMAKE_CXX_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3 -march=native -L/usr/local/lib")
    message("Release mode:${CMAKE_CXX_FLAGS_RELEASE}")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3 -march=native -L/usr/local/lib")
    message("Release mode:${CMAKE_CXX_FLAGS_RELEASE}")
endif()


#find_package(Threads REQUIRED)
#find_package(PkgConfig REQUIRED)
# Find required protobuf package
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()
include_directories(${Protobuf_INCLUDE_DIRS})

add_subdirectory(src/proto)
#include_directories(${PROTO_GEN_C_INCLUDE_DIRS}) # c
include_directories(${PROTO_GEN_CXX_INCLUDE_DIRS}) # cpp

add_executable(Learning-Cpp
        main.cpp
        src/service/SiteDomainService.h
        src/service/Impl/SiteDomainServiceImpl.cpp
        src/threadPool/threadPool.h
        src/service/VipExclusiveDomainService.h
        src/service/Impl/VipExclusiveDomainServiceImpl.cpp
        src/service/VipExclusiveDomainServiceV2.h
        src/service/Impl/VipExclusiveDomainServiceImplV2.cpp
        src/service/SbcConvertService.h
        src/service/Impl/SbcConvertServiceImpl.cpp
        src/service/TrieService.h
        src/service/Impl/TrieServiceImpl.cpp
        config.h.in
        src/service/DemoService.h
        src/service/Impl/DemoServiceImpl.cpp
        src/service/SortService.h
        src/service/Impl/SortServiceImpl.cpp
        ) # 生成可执行文件

target_link_libraries(Learning-Cpp proto_gen_cxx)

#[[add_library(common STATIC
        main.cpp)]] # 生成静态库

#add_library(common SHARED main) # 生成动态库或共享库

include_directories(${CMAKE_CURRENT_SOURCE_DIR})