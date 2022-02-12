w = 8
W = 2^w



def lehmer_gcd(a, b):
    # initial reductions
    #if a < b:
     #   a, b = b, a
        
    while b >= W:
        size = len(str(bin(a)))-2 - w
        x, y = int(a >> size), int(b >> size)
        A, B, C, D = 1, 0, 0, 1
        while True:
            if y+C == 0 or y+D == 0:
                break
            q = (x+A)//(y+C)
            if q != (x+B)//(y+D):
                break
            A, B, x, C, D, y = C, D, y, A-q*C, B-q*D, x-q*y

        if B:
            a, b = A*a + B*b, C*a + D*b
        else:
            a, b = b, a % b

    while b:
        a, b = b, a%b
    return a
a = 0x9ca214b88481393502
b = 0x5ab440


print(gcd(a, b) == lehmer_gcd(a, b))

print("\n{}".format(lehmer_gcd(a, b)))
print(gcd(a, b))