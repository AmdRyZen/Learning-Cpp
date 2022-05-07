cmake_minimum_required(VERSION 3.20)
project(Learning-Cpp)

set(CMAKE_CXX_STANDARD 17)

set(MAIN_PATH ${PROJECT_SOURCE_DIR})

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")

configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in @ONLY)

# 条件判断
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
    message("Debug mode:${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3 -march=native")
    message("Release mode:${CMAKE_C_FLAGS_RELEASE}")
else()
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3 -march=native")
    message("Release mode:${CMAKE_C_FLAGS_RELEASE}")
    #message("else:${CMAKE_BUILD_TYPE}")
    #message("else:${CMAKE_C_FLAGS_RELEASE}")
endif()

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
add_library(common STATIC
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
        src/service/Impl/SortServiceImpl.cpp) # 生成静态库

#add_library(common SHARED main) # 生成动态库或共享库

include_directories(${CMAKE_CURRENT_SOURCE_DIR})