# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.11)

# 프로젝트 정보
project(
  realcode
  VERSION 0.9
  DESCRIPTION "큰 정수 연산 라이브러리"
  LANGUAGES C)

# 확인할 디렉토리 추가
add_subdirectory(lib)
add_subdirectory(tests)

add_executable (main main.c)

# test 에 op를 링크
target_link_libraries(main PRIVATE bigint test)