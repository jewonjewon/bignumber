

def bin_gcd_ite(a, b):
    t0, t1, t2 = a, b, 1
    while t0 & 1 == 0 and t1 & 1 == 0:
        t0, t1, t2 = t0 >> 1, t1 >> 1, t2 << 1
    while t1 != 0:
        while t0 & 1 == 0:
            t0 = t0 >> 1
        while t1 & 1 == 0:
            t1 = t1 >> 1
        if t1 >= t0:
            t1 = t1-t0
        else:
            t0 = t0-t1
    print(hex(t0))
    print(hex(t1))
    print(hex(t2))        
    return t0*t2

A = 0x9ca214b88481393502
B = 0x5ab4

print(hex(bin_gcd_ite(A, B)))


print(gcd(A, B) == bin_gcd_ite(A, B))

