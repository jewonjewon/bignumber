def extended_binary_gcd_algorithm_ite(a, b):
    t0, t1, t2 = a, b, 1
    while t0 & 1 == 0 and t1 & 1 == 0:
        t0, t1, t2 = t0 >> 1, t1 >> 1, t2 << 1

    a, b = t0, t1
    u0, v0 = 1, 0
    u1, v1 = 0, 1

    while t0 != 0:
        while t0 & 1 == 0:
            t0 = t0 >> 1
            if (u0 & 1 == 0 and v0 & 1 == 0):
                u0, v0 = u0 >> 1, v0 >> 1
            else:
                u0, v0 = (u0 + b) >> 1, (v0 - a) >> 1
        while t1 & 1 == 0:
            t1 = t1 >> 1
            if (u1 & 1 == 0 and v1 & 1 == 0):
                u1, v1 = u1 >> 1, v1 >> 1
            else:
                u1, v1 = (u1 + b) >> 1, (v1 - a) >> 1
        if(t0 >= t1):
            t0, u0, v0 = t0 - t1, u0 - u1, v0 - v1
        else:
            t1, u1, v1 = t1 - t0, u1 - u0, v1 - v0
    return t1 * t2, u1, v1


a, b = ZZ.random_element(1000), ZZ.random_element(1000)
print("(a,b) = ({},{})".format((a), (b)))
T = extended_binary_gcd_algorithm_ite(a, b)
print("{} = {}({}) + {}({})".format(T[0], a, T[1], b, T[2]))
print(T[0] == a*T[1] + b*T[2])
