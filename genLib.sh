# !/bin/bash
gcc -fPIC -c *.c

gcc -shared -o libBigNumber.so *.o
rm *.o

gcc main.c -lBigNumber.so -Llibs
