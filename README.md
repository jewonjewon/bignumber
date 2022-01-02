# 큰 정수 연산 라이브러리

## 목표

1. 큰 정수 연산 라이브러리

- [x] 덧셈
- [x] 뺄셈
- [x] Schoolbook 곱셈
- [x] Schoolbook 제곱
- [x] Karatsuba 곱셈
- [ ] Karatsuba 제곱
- [ ] 워드 단위 긴 나눗셈
- [ ] 이진 긴 나눗셈
- [ ] Left-To-Right binary Method
- [ ] Right-To-Left binary Method
- [ ] Montgomery Ladder Method

2. 검증 함수

- [x] 덧셈
- [x] 뺄셈
- [x] Schoolbook 곱셈
- [x] Schoolbook 제곱
- [x] Karatsuba 곱셈
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

| 날짜     | 개발 내용                                                                   | 비고                                                          |
| -------- | --------------------------------------------------------------------------- | ------------------------------------------------------------- |
| 21.12.21 | Schoolbook 곱셈 구현, 케이스 별 검증 완료                                   | (ADD, SUB 검증 재확인할 것)                                   |
| 21.12.26 | Schoolbook 제곱 구현, 케이스 별 검증 완료                                   | ~~SQU 함수에서 memory leak 발생 이 부분 다시 확인하기~~, 해결 |
| 21.12.27 | 카라츄바 곱셈 하는중 (음수 \* 양수), reduction에서 오류뜸 , 덧셈, 뺄셈 수정 | 없음                                                          |
| 22.01.02 | 카라츄바 입력정수 양수인 케이스 만 완성                                     | 음수 처리 해야함                                              |

## 유의 사항

- 주석 아주 상세히 기술할 것
- 메모리 누수 확인 잘하기
- 코드 가독성 신경쓰기

# 큰 정수 라이브러리 함수

## bi_logical_op

논리연산자 함수

- 워드 left shift 함수
- 워드 bit shift 함수

## bi_op

산술연산자 함수(e.g. 사칙연산 등)
bi_add, bi_sub, bi_mul, bi_squ

- 덧셈
  - bi_ADD_ABc
  - bi_ADDC
  - bi_ADD
- 뺄셈
  - bi_SUB_AbB
  - bi_SUBC
  - bi_SUB
- 곱셈
  - bi_MUL_AB
  - bi_MULC
  - bi_MUL
- 나눗셈
  - bi_SQU_A
  - bi_SQUC
  - bi_SQU

## bi_test

함수 정확성 검증 테스트 함수

## bi_local

기본적으로 필요한 것들 , 매크로 구조체 정의 등
