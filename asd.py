# Montgomery Reduction Sage Code
def mont_red(x, r, n, nn):
    m = ((x % r) * nn) % r
    t = (x + m*n) >> (len(r.bits()) - 1)
    if(t >= n):
        t = t - n
    return t


w = 8
W = 2 ^ w

N = (N << 1) + 1  # odd N
t = 1

while (True):
    R = W ^ (t)
    if ((gcd(R, N) == 1) and (N < R)):
        break
    else:
        t = t + 1

print("N = {} (given)".format(hex(N)))

print("R = {}".format(hex(R)))
invN = inverse_mod(N, R)
NN = (- invN) % R
phi1 = R % N

print("Pre-computed values:")
print("N^(-1) = {}".format(hex(invN)))
print("N' = {}".format(hex(NN)))
print("phi(1) = R mod N = {}".format(hex(phi1)))
