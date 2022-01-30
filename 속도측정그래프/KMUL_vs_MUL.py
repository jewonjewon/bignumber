import time
import matplotlib.pyplot as plt
import random


# x: 밑수를 의미하는 리스트 한개만 있으면 됨

x = ['8', '16', '24', '32', '40', '48']
y1 = [
    0.161468,
    0.552178,
    1.572143,
    3.240256,
    5.896350,
    9.443568]

y2 = [0.105530,
      0.333709,
      0.653689,
      1.008003,
      1.528774,
      1.954221]

# y3 = [
# 3.797982, 3.367312, 3.227951, 3.232265, 3.315596, 3.496603, 3.740610, 3.905522, 4.067783, 4.282122, 4.417197, 4.606118, 4.733289, 4.843801, 4.809741, 4.813502, 4.840626, 4.842201, 4.860876, 4.844404
# ]

# y1: w =8
# y2: w = 32
# y3: w = 64


u = 1

plt.title("Karastuba Multiplication v.s. Schoolbook Multiplication")


# plt.xticks([8, 16, 24, 32, 40, 48], labels=['8', '', '16',
#            '', '24', '', '32', '', '40', '', '48'])

#
# plt.xticks([8, 16, 24, 32, 40, 48], labels=[1, 2, 3, 4, 5, 6])

# plt.plot([8, 16, 24, 32, 40, 48])
# plot()메서드를 통해 x축에는 x(=date)값, y축에는 y1(= 6월 서울의 'AveTemp' 데이터) 선 색깔은 하늘색'skyblue'로 설정 그리고 범례는 Seoul로 설정.
plt.plot(x, y1, 'skyblue', label="Schoolbook MUL")
plt.plot(x, y2, 'orange', label="Karatsuba MUL")
# plt.plot(x, y3, 'red', label="w = 64")
# plt.plot(x,y4,'green', label="Naive")

# plt.xticks([1, 2, 3, 4, 5, 6], labels=['8', '16', '24', '32', '40', '48'])

plt.legend()
# x축 글자의 가독성을 위해 글자를 70도 가량 회전시킴.
plt.xticks(rotation=70)
plt.xlabel("wordlen")
# y축의 이름을 "Temperature"로 설정.
plt.ylabel("time (s)")
plt.show()
