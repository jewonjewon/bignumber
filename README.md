# 큰 정수 연산 라이브러리

## 목표

1. 큰 정수 연산 라이브러리

- [ ] 덧셈
- [ ] 뺄셈
- [ ] Schoolbook 곱셈
- [ ] Schoolbook 제곱
- [ ] Karatsuba 곱셈
- [ ] Karatsuba 제곱
- [ ] 워드 단위 긴 나눗셈
- [ ] 이진 긴 나눗셈
- [ ] Left-To-Right binary Method
- [ ] Right-To-Left binary Method
- [ ] Montgomery Ladder Method

2. 검증 함수

- [ ] 덧셈
- [ ] 뺄셈
- [ ] Schoolbook 곱셈
- [ ] Schoolbook 제곱
- [ ] Karatsuba 곱셈
- [ ] Karatsuba 제곱
- [ ] 워드 단위 긴 나눗셈
- [ ] 이진 긴 나눗셈
- [ ] Left-To-Right binary Method
- [ ] Right-To-Left binary Method
- [ ] Montgomery Ladder Method

3. 암호

- [ ] Textbook-RSA 1024, 2048
- [ ] RSA-CRT
- [ ] RSA-OAEP
- [ ] DH Key Exchange Protocol

## 개발 일정

21.12.17 ~ 겨울방학: 빅넘버 라이브러리 완성, RSA(RSA-CRT, RSA-OAEP)완성, DH 키교환 완성

21.12.17 ~ 2022 1학기: ECC 완성

## 개발 현황

| 날짜     | 개발 내용                                 | 비고                                                 |
| -------- | ----------------------------------------- | ---------------------------------------------------- |
| 21.12.21 | Schoolbook 곱셈 구현, 케이스 별 검증 완료 | (ADD, SUB 검증 재확인할 것)                          |
| 21.12.26 | Schoolbook 제곱 구현, 케이스 별 검증 완료 | 모든 함수에서 memory leak 발생 이 부분 다시 확인하기 |

## 유의 사항

- 주석 아주 상세히 기술할 것
- 메모리 누수 확인 잘하기
- 코드 가독성 신경쓰기
