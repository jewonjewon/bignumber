

import random
import exp


def get_l(a):
    cnt = 0
    while(True):
        # a와 1을 AND연산을 하였을 때의 결과값이 0이라면, (즉, a의 마지막 비트가 1이 아님을 뜻함)
        if(a & 1 == 0):
            # a를 2로 나눔
            a = a >> 1
            cnt = cnt + 1
        # a의 마지막 비트가 0이면
        else:
            return cnt

# is_composite(판별하고자 하는 정수, , , 임의의 정수)


def is_composite(n, q, l, a):

    # a = a**q mod(n)
    a = exp.modL2r(a, q, n)
    # print("a^(q) = {}".format(a))
    if(a % n == 1):
        return "NOT Composite"

    for j in range(0, l):
        # print("a^(2^{}*q) = {}".format(j, a))
        # n-1 = a mod(n)인 경우, a는 합성수가 아니라고 판단.
        if((a % n) == (n-1)):
            return "NOT Composite"

        # a = a**2 mod(n)
        a = exp.modL2r(a, 2, n)

        # print("a = ", a)

    # l번 반복하면서 for문이 종료되지 않으면  a는 합성수
    return "Composite"

# miller_labin(판별하고자 하는 정수, 판별 횟수)


def miller_rabin(n, k):
    l = get_l(n-1)
    q = (n-1) >> 1
    # print("l = {}, q = {}".format(l, q))

    # k번 시행
    while(k > 0):
        # [2, n-2] 사이의 정수를 무작위로 추출하여 변수 a에 할당.
        a = random.randint(2, n-2)

        # print("a = ", a)

        # is_composite()함수로 반환한 리턴값을 ret 변수에 할당. ret는 "Not composite", "Composite" 둘 중 하나임.
        ret = is_composite(n, q, l, a)

        # ret가 "Composite"을 반환한 경우, 함수는 종료되며 입력받은 n은 합성수임을 알려줌.
        if(ret == "Composite"):
            print("#?")
            return "Composite"

        k = k - 1
    # while문이 k번 시행되는동안 while문이 종료되지 않았을 경우, "Probably Prime" 리턴 이것은 입력받은 수 n이 "높은 확률로 소수일 것"이라고 판별
    return "Probably Prime"


# n = 1234547
# print(miller_rabin(n, 100))


########################################################################################

# miller_rabin() TEST
# n = 12349876812313
# print(miller_rabin(n ,100))


# lboubd ~ ubound사이의 무작위 소수를 뽑는 함수.
def random_prime(lbound, ubound):

    while(True):
        # [lbound, ubound]사이의 무작위 정수를 하나 선택하여 변수 p에 할당.
        p = random.randint(lbound, ubound)
        # 일반적으로 3이상의 소수는 모두 홀수이다. 따라서 무작위로 뽑은 p가 짝수일 경우 다시 p를 무작위로 선택.
        # p가 홀수일 경우, miller_rabin()을 통해 p가 소수인지 아닌지 판별.
        if(p % 2 != 0):
            pp = miller_rabin(p, 40)

            # pp는 p가 합성수인지 소수인지 알려주는 변수 즉 miller_rabin()을 통해 pp가 "Probably Prime"을 반환하였다면 p는 소수.
            if(pp == "Probably Prime"):
                return p
# end random_prime()


# random_prime() TEST
qwe = random_prime(2**511, 2**512)
print("소수 : ", hex(qwe))
