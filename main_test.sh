# !/bin/bash

# 실행파일 생성
g++ -o test.out main_test.cpp libs/*.c libs/bi_util.cpp 

# memory leak 
leaks --atExit -- ./test.out

./test.out
rm test.out