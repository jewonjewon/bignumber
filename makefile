bignum.out: main.o foo.o bar.o 
    gcc -o bignum.out main.o 
 
# main.o: foo.h bar.h main.c
#     gcc -c -o main.o main.c
 
foo.o: bi_local.h bi_local.c
    gcc -c -o local.o local.c
 
bar.o: bi_op.h bi_op.c bi_bitop
    gcc -c -o bi_op.o bi_bitop.c