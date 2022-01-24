print("### BINARY GCD TEST ###\n")
cnt = 0
A = 0x4d43fed8c8822ad9
B = 0xb3e28c5598
C = 0x1
if (C != gcd(A, B)):
    print("{} : {}".format(0, gcd(A, B) == C)) #0
    print(hex(gcd(A, B)))
    cnt = cnt + 1
A = 0xf558052d112f549811
B = 0x334892990788d66b
C = 0x1
if (C != gcd(A, B)):
    print("{} : {}".format(1, gcd(A, B) == C)) #1
    print(hex(gcd(A, B)))
    cnt = cnt + 1
A = 0x305fe5230df3
B = 0x61edc8d1
C = 0x1
if (C != gcd(A, B)):
    print("{} : {}".format(2, gcd(A, B) == C)) #2
    print(hex(gcd(A, B)))
    cnt = cnt + 1
A = 0x9ca214b88481393502
B = 0x5ab4
C = 0x2
if (C != gcd(A, B)):
    print("{} : {}".format(3, gcd(A, B) == C)) #3
    print(hex(gcd(A, B)))
    cnt = cnt + 1
A = 0x394d9be58a15c4b0f1c5e948e5ca
B = 0xedfed305a1e8f7f6
C = 0x2
if (C != gcd(A, B)):
    print("{} : {}".format(4, gcd(A, B) == C)) #4
    print(hex(gcd(A, B)))
    cnt = cnt + 1
A = 0xd9f3
B = 0xfa5be4
C = 0x1
if (C != gcd(A, B)):
    print("{} : {}".format(5, gcd(A, B) == C)) #5
    print(hex(gcd(A, B)))
    cnt = cnt + 1
A = 0xae20e251
B = 0xa134ff616d9806e10c
C = 0x1
if (C != gcd(A, B)):
    print("{} : {}".format(6, gcd(A, B) == C)) #6
    print(hex(gcd(A, B)))
    cnt = cnt + 1
A = 0x3ac38f81b7e95036fd
B = 0xc87a55442cc00f1e
C = 0x1
if (C != gcd(A, B)):
    print("{} : {}".format(7, gcd(A, B) == C)) #7
    print(hex(gcd(A, B)))
    cnt = cnt + 1
A = 0x9fdd4f4ce2b5f6b2deb2c9
B = 0xcebd6788
C = 0x1
if (C != gcd(A, B)):
    print("{} : {}".format(8, gcd(A, B) == C)) #8
    print(hex(gcd(A, B)))
    cnt = cnt + 1
A = 0xe9797788e0061
B = 0x2958a1475ed7076234
C = 0x1
if (C != gcd(A, B)):
    print("{} : {}".format(9, gcd(A, B) == C)) #9
    print(hex(gcd(A, B)))
    cnt = cnt + 1
if (cnt == 0):
    print("ALL TRUE!")
