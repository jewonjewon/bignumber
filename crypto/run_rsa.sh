# !/bin/bash

dir=${PWD}
cd ..
cur_dir=${PWD}
cur_dir+="/libs" 

cd $cur_dir

# object 파일 생성
gcc -fPIC -c *.c

# object 파일로 동적 라이브러리 생성
gcc -shared -o libBigNumber.so *.o
rm *.o

mv libBigNumber.so /Users/jewon/Desktop/BigNumber/crypto

cd $dir

# compile &  memory leak 
gcc -o run main_rsa.c rsa.c rsa_crt.c -L. -lBigNumber && leaks -q --list --atExit -- ./run
./run 

# python3 verify.py

rm run libBigNumber.so