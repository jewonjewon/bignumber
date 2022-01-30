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
        print("{:4} = ({:4}) * {:4} + ({:4}) * {:4}".format(t0, a, u0, b, v0))
    return t0 , u0 , v0

a = 
b = 

print ("(a,b) = ({},{})".format(a,b))
result = EEA_iter(a, b)
print(result == xgcd(a,b))
