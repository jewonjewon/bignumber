# !/bin/bash

cur_dir=${PWD}
cur_dir+="/libs"

cd $cur_dir

# object 파일 생성
gcc -fPIC -c *.c

# object 파일로 동적 라이브러리 생성
gcc -shared -o libBigNumber.so *.o
rm *.o

mv libBigNumber.so /Users/jewon/Desktop/BigNumber

cd ..

# compile &  memory leak 
gcc -o run main_verify.c -L. -lBigNumber && leaks -q --list --atExit -- ./run
# ./run

leaks --atExit -- ./run

./run > verify.py

python3 verify.py

rm run verify.py 
# rm run verify.py libBigNumber.so