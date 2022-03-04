# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.11)

# 프로젝트 정보
project(
  testcode
  VERSION 0.1
  DESCRIPTION "큰 정수 연산 라이브러리"
  LANGUAGES C)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

# 라이브러리 생성
# add_library(bigint STATIC add.c sub.c mul.c mod.c)
add_library(benchmark STATIC ${SRC_FILES})

# 해당 라이브러리 컴파일 시 사용할 헤더파일 경로
target_include_directories(bigint PUBLIC ${CMAKE_SOURCE_DIR}/includes)

# 해당 라이브러리를 컴파일 할 옵션
target_compile_options(benchmark PUBLIC -Wall -O2)