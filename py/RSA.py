import random
import time


def gcd(a, b):

    t0 = a
    t1 = b

    while (t1 != 0):
        t2 = t0
        t0 = t1
        t1 = t2 % t1

    return t0


def xgcd(a, m):
    t0, t1 = a, m
    u0, u1 = 1, 0

    while (t1 != 0):
        t2, t0 = t0, t1
        q, t1 = t2 // t1, t2 % t1
        u2, u0 = u0, u1
        u1 = u2 - q * u1

    if (u0 < 0):
        u0 = u0 + m

    return u0


def RSA_keygen(p, q):
    N = p*q
    phi = (p-1) * (q-1)

    while (True):
        e = random.randint(2, phi)

        if (gcd(e, phi) == 1):
            d = xgcd(e, phi) % phi

            if (e != d):
                return e, d, N, phi


def power_mod(g, n, M):
    # USING LEFT-TO-RIGHT BINARY METHOD
    t = 1

    l = len(bin(n)) - 2
    n = list(map(int, str(bin(n)[2:])))

    for j in range(0, l):
        t = (t ** 2) % M
        t = (t * (g ** n[j])) % M

    return t


def RSA_enc(m, e, N):
    ciphertext = power_mod(m, e, N)
    return ciphertext


def RSA_dec(c, d, N):
    plaintext = power_mod(c, d, N)
    return plaintext


def RSA_1024(m):

    p = 0x1aa6802d3de59367588e7fbdaad991c7be0ab1a8cd60e8831176381cf1c3cd681542ba8553840d93df720d6aa1307c821020dbd0ecaff20ef0dfd49b07c3437bf
    q = 0x9fffc7d3f434baaef0443f2c7cff1bdb0bb092a947ca4ed6c328fcff344cdb01df5d1df258cddbb357812a8b7a153636d5a959078cf6605e90d34ab2a4a78465
    # RSA KEY GENERATION
    parameter = [0]*4
    parameter = RSA_keygen(p, q)

    e = parameter[0]
    d = parameter[1]
    N = parameter[2]

    # RSA ENCRYPTION
    c = RSA_enc(m, e, N)

    # RSA DECRYPTION
    recovered_msg = RSA_dec(c, d, N)
    # PRINT OUTPUT
    # show(parameter, recovered_msg, m)


def RSA_2048(m):

    p = 0xa9ca8bad40a5f6b8917345ae5248d379476c6bc0ed03ddb46220e40a45a14ec92aed547b05eb3553ff6261c4182ae86ffbb9854dd4cf1b7df94801807f0d360fcaff3099d0cc109604dc6784616eab9fc06681c29555a590c0964e1e3e6f39ac882949f24a1553e7c4717dc883908a1d7b7f6eb90d721689389bb6cdaf432cdf
    q = 0x1aef2240aeca42ee24a15922505ec571b6b70da42666a62c07bb5480430236263bff0abc42bd7867d00675781dc374674b0e1518bd58f839d8088083879467916a4bc4acf3c59bef2a8fde9b77533e92ea0f567a6b49ffe4fee60ee2d86f8777e8552657e63e73de7864f7aa85f8ebc767f52b3e45129f75efadb507389631aaf

    # RSA KEY GENERATION
    parameter = [0]*4
    parameter = RSA_keygen(p, q)

    e = parameter[0]
    d = parameter[1]
    N = parameter[2]

    # RSA ENCRYPTION
    c = RSA_enc(m, e, N)

    # RSA DECRYPTION
    recovered_msg = RSA_dec(c, d, N)
    # PRINT OUTPUT
    # show(parameter, recovered_msg, m)


def show(parameter, newmsg, msg):
    # SHOW
    print("phi N      : {}".format(parameter[3]))
    print("public  key: {}".format(parameter[0]))
    print("secrete key: {}".format(parameter[1]))
    print("N          : {}".format(parameter[2]))
    print("recovered message: {}".format(newmsg))
    print(newmsg == msg)


def main():
    msg = 20172258
    cnt = 1000

    start1 = time.time()

    for j in range(cnt):
        RSA_1024(msg)
    end1 = time.time()

    start2 = time.time()

    for j in range(cnt):
        RSA_2048(msg)
    end2 = time.time()

    print("RSA-1024")
    print("{}-times: {} sec".format(cnt, (end1 - start1)))
    print("Total: {} sec".format((end1-start1)/cnt))
    print("\n")

    print("RSA-2048")
    print("{}-times: {} sec".format(cnt, (end2-start2)))
    print("Total: {} sec".format((end2-start2)/cnt))


main()
