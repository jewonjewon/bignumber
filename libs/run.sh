# !/bin/bash

gcc -fPIC -c *.c

gcc -shared -o libBigNumber.so *.o
rm *.o

gcc -o run main.c -L. -lBigNumber
./run

# memory leak 
leaks --atExit -- ./run

./run > verify.py

python3 verify.py

rm a.out verify.py