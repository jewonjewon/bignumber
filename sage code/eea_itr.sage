# sage eea_ite

def EEA_iter(a, b):
    t0, t1 = a, b
    u0, v0 = 1, 0
    u1, v1 = 0, 1
    print("{:4} = ({:4}) * {:4} + ({:4}) * {:4}".format(t0, a, u0, b, v0))
    while t1 != 0:
        q, r = t0 // t1, t0 % t1
        t0, t1 = t1, r
        u2, v2 = u0 - q*u1, v0 - q*v1
        u0, v0 = u1, v1
        u1, v1 = u2, v2
        print("{:4} = ({:4}) * {:4} + ({:4}) * {:4}".format(hex(t0), hex(a), hex(u0), hex(b), hex(v0)))
    return t0 , u0 , v0

A = 0xf352
B = 0x828fae39
C = -0x1aae2658

print ("(a,b) = ({},{})".format(A,B))
result = EEA_iter(A, B)
print(result == xgcd(A,B))
print(hex(xgcd(A, B)[1]))
print((xgcd(A, B)[1]))