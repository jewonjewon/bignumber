from ctypes import *
import os
import sympy
import math

# 경로 설정
dir = os.getcwd()
dir += "/libBigNumber.so"
# print(dir)

a = math.gcd(3, 15)
print(a)

bigintLib = CDLL(dir)
print(bigintLib.bitlen(4))
