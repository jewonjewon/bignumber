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
    return t0*t2
