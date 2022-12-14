# 큰 정수 연산 라이브러리(Big Number library)
64비트 이상의 큰 정수 연산(사칙연산, gcd 등)을 위한 함수로 구성한 라이브러리 
## 목표(Goal)
- 안정적인 라이브러리 개발
  - 메모리 누수, 컴파일 에러가 없는 라이브러리 개발
- 연산 정확성 검증
  - Python, SageMath 등 큰 정수 연산을 지원하는 언어를 이용하여 연산 정확성 검증 수행
- RSA 구현
  - 개발한 큰 정수 연산 라이브러리를 하여 RSA 구현
### 큰 정수 연산 함수
- [x] Addition
- [x] Subtraction
- [x] Schoolbook Multiplication
- [x] Schoolbook Square
- [x] Karatsuba Multiplication
- [x] Karatsuba Square
- [x] 워드 단위 긴 나눗셈
- [x] Binary long division
- [x] Left-To-Right binary Method
- [x] Right-To-Left binary Method
- [x] Montgomery Ladder Method

### 소수 생성

### 검증

- [x] 덧셈
- [x] 뺄셈
- [x] Schoolbook 곱셈
- [x] Schoolbook 제곱
- [x] Karatsuba 곱셈
- [x] Karatsuba 제곱
- [x] 워드 단위 긴 나눗셈
- [x] 이진 긴 나눗셈
- [x] Left-To-Right binary Method
- [x] Right-To-Left binary Method
- [x] Montgomery Ladder Method

3. 암호

- [x] Textbook-RSA 1024, 2048
- [x] RSA-CRT
- [ ] RSA-OAEP

## 유의 사항

- 주석 아주 상세히 기술할 것
- 메모리 누수 확인 잘하기
- 코드 가독성 신경쓰기

# 큰 정수 라이브러리 함수

## bi_logical_op

논리연산자 함수

- 큰 정수 SHIFT 함수
  - bit LEFT shift + word LEFT shift 함수 $\rightarrow$ bi_lshift()
  - word LEFT shift 함수 $\Rightarrow$ bi_word_lshift(bigint 구조체, 워드 단위 시프트 수)

## bi_op

산술연산자 함수(e.g. 사칙연산 등)
bi_add, bi_sub, bi_mul, bi_squ

- 덧셈
  - bi_ADD_ABc
  - bi_add_core
  - bi_add
- 뺄셈
  - bi_SUB_AbB
  - bi_sub_core
  - bi_sub
- 곱셈
  - bi_MUL_AB
  - bi_mul_core
  - bi_mul
  - bi_kmul_core
  - bi_kmul
- 제곱
  - bi_SQU_A
  - bi_squ_core
  - bi_squ
  - bi_ksqu_core
  - bi_ksqu
- 나눗셈
  - bi_long_div_2word
  - bi_div_core2
  - bi_div_core
  - bi_div
  - bi_bin_long_div

## bi_test

함수 정확성 검증 테스트 함수

## bi_local

기본적으로 필요한 것들 , 매크로 구조체 정의 등
