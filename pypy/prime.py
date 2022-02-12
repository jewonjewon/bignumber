import random
import exp





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
            pp = miller_rabin(p, 1000)

            # pp는 p가 합성수인지 소수인지 알려주는 변수 즉 miller_rabin()을 통해 pp가 "Probably Prime"을 반환하였다면 p는 소수.
            if(pp == "Probably Prime"):
                return p
# end random_prime()


# random_prime() TEST
qwe = random_prime(2**3, 2**61)
print("소수 : ", qwe)
