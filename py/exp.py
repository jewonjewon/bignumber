

a = [6909, 125, 11251]


'''
exponentiation
'''
# r2l


def r2l(g, n):

    t = [1, g]

    l = len(bin(n)) - 2  # l: bit length
    n = list(map(int, str(bin(n)[2:])))  # n을 이진수로 변환 후 리스트에 저장.

    for j in range(l-1, -1, -1):
        t[0] = (t[0] * (t[1] ** n[j]))
        t[1] = (t[1] ** 2)
    return t[0]

# left-to-right modular exponentiation


def l2r(g, n):

    t = 1

    l = len(bin(n)) - 2  # l: bit length
    n = list(map(int, str(bin(n)[2:])))  # n을 이진수로 변환 후 리스트에 저장.
    if (n == -1):
        return 1

    for j in range(0, l):
        t = (t ** 2)
        t = (t * (g ** n[j]))

    return t


def mns(g, n):
    t = [1, g]

    l = len(bin(n)) - 2  # l: bit length
    n = list(map(int, str(bin(n)[2:])))  # n을 이진수로 변환 후 리스트에 저장.

    for j in range(0, l):
        t[1-n[j]] = (t[0] * t[1])
        t[n[j]] = (t[n[j]] ** 2)

    return t[0]


'''
modular exponentiation
'''
# r2l


def modR2l(g, n, M):

    t = [1, g]

    l = len(bin(n)) - 2  # l: bit length
    n = list(map(int, str(bin(n)[2:])))  # n을 이진수로 변환 후 리스트에 저장.

    for j in range(l-1, -1, -1):
        t[0] = (t[0] * (t[1] ** n[j])) % M
        t[1] = (t[1] ** 2) % M
    return t[0]

# left-to-right modular exponentiation


def modL2r(g, n, M):

    t = 1

    l = len(bin(n)) - 2  # l: bit length
    n = list(map(int, str(bin(n)[2:])))  # n을 이진수로 변환 후 리스트에 저장.

    for j in range(0, l):
        t = (t ** 2) % M
        t = (t * (g ** n[j])) % M

    return t


def modMns(g, n, M):
    t = [1, g]

    l = len(bin(n)) - 2  # l: bit length
    n = list(map(int, str(bin(n)[2:])))  # n을 이진수로 변환 후 리스트에 저장.

    for j in range(0, l):
        t[1-n[j]] = (t[0] * t[1]) % M
        t[n[j]] = (t[n[j]] ** 2) % M

    return t[0]

# print("Exponentiation")
# print("r2l: {}".format(r2l(a[0], a[1])))
# print("l2r: {}".format(l2r(a[0], a[1])))
# print("mns: {}".format(mns(a[0], a[1])))
# print("그냥: {}".format((a[0]**a[1])))
# # print(l2r(a[0], a[1]) == (a[0]**a[1]))

# print("Modular Exponentiation")
# print("r2l: {}".format(modR2l(a[0], a[1], a[2])))
# print("l2r: {}".format(modL2r(a[0], a[1], a[2])))
# print("mns: {}".format(modMns(a[0], a[1], a[2])))
# print("그냥: {}".format((a[0]**a[1]) % a[2]))
