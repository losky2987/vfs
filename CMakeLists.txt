cmake_minimum_required(VERSION 3.10)

# 项目名称
project(LibPak)

# 设置编译器
set(CMAKE_C_COMPILER gcc)

# 设置编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -fPIC -W -ansi -pedantic")
set(DEFINES "-D_FILE_OFFSET_BITS=64 -DBZ_NO_STDIO")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEFINES}")

# 包含目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 源文件列表
set(SOURCES
    src/pak.c
    src/util.c
    src/vfs.c
    src/stream.c
    src/pool.c
    src/plugin/pak_plugin.c
    src/plugin/bz2compress_plugin.c
    src/hashtable/hashtable.c
    src/hashtable/hashtable_itr.c
    src/hashtable/hashtable_utility.c
    src/crc32/crc32.c
    src/bzip2/blocksort.c
    src/bzip2/huffman.c
    src/bzip2/crctable.c
    src/bzip2/randtable.c
    src/bzip2/compress.c
    src/bzip2/decompress.c
    src/bzip2/bzlib.c
)

# 将所有对象文件输出到objs目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 编译为静态库
add_library(libpak STATIC ${SOURCES})

# 创建工具子目录
add_subdirectory(tools)

# 创建测试子目录
add_subdirectory(examples)

# 清理目标
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove lib/libpak.a
    COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_BINARY_DIR}/objs/*.o
    COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_BINARY_DIR}/bin/pack_dir
    COMMAND ${CMAKE_MAKE_PROGRAM} clean -C tools
    COMMAND ${CMAKE_MAKE_PROGRAM} clean -C examples
)
