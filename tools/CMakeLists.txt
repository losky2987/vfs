cmake_minimum_required(VERSION 3.10)

# 项目名称
project(PackDirProject)

# 设置编译器
set(CMAKE_C_COMPILER gcc)

# 设置编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -fPIC -W -ansi -pedantic -D_FILE_OFFSET_BITS=64")

# 包含目录
include_directories(${PROJECT_SOURCE_DIR}/../include ${PROJECT_SOURCE_DIR}/../src)

# 链接库路径和库
link_directories(${PROJECT_SOURCE_DIR}/../lib)
set(LIBS -lpak -lm)

# 源文件
set(SOURCE_FILES pack_dir.c)

# 可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

# 生成 pack_dir 可执行文件
add_executable(pack_dir ${SOURCE_FILES})
target_link_libraries(pack_dir ${LIBS})

# 清理目标
add_custom_target(clean-all
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pack_dir
        COMMAND ${CMAKE_COMMAND} -E remove pack_dir.o
)
