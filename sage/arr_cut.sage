w = 8
cnt = 15
A = [0] * cnt
B = [0] * cnt

a = 0xd1b9a151213ff5db2150aab2d44f1c1c53e62a1504dd91a4d48e08d749740ea28803bec06c7e695612d93345384dbc918857310c662661124b1492863c629fdfb0f81fcbe1645c4d644d29a50e2519f42b190c0f2a123df5670c66d779d54441
b = 0x61c90c012efdacfa21dff116a6d8b230ea5031d8604c9cde
c = -0x162bd33249dac6697720c3c943f9b1987b2fd666cc3d8a


for j in range(cnt):
    A[j] = (a >> (j*w)) & (2^w-1)
    B[j] = (b >> (j*w)) & (2^w-1)
    
for j in range(cnt-1, -1, -1):
    print("A->a[{:}] = {:};".format(j,hex(A[j])), end='\n')

print()    

for j in range(cnt-1, -1, -1):
    print("B->a[{:}] = {:};".format(j,hex(B[j])), end='\n')


if (c != a * b):
    print("{} : {}".format(1109, b * a == c)) #1109
    
print(hex(a*b))


