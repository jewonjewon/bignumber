# !/bin/bash

# 실행파일 생성
gcc RSA.c basic.c benchmark.c benchmark_RSA.c benchmark_add.c benchmark_div.c benchmark_gcd.c benchmark_prime.c benchmark_spdm.c benchmark_아무거나.c bi.c bi_add_sub.c bi_bitop.c bi_div.c bi_exp.c bi_gcd.c bi_karatsuba_test.c bi_mul.c bi_prime.c bi_rand.c bi_squ.c bi_test.c main.c -O2 -Wall

# memory leak 
leaks --atExit -- ./a.out 

./a.out 
rm a.out