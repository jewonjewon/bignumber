///@file bi_util.h
///@author Jewon Lee
///@date 2022-11-22
///@brief bigint util

#ifndef __BI_UTIL_H__
#define __BI_UTIL_H__

#include <iostream>
#include <math.h>

#include "bi.h"

using namespace std;

int getBlockLen(int len);

/// @brief 입력받은 문자가 16진수인지 확인
/// @param ch 문자
/// @return 16진수일 경우 true(1), 아닐 경우 false(0) 출력
bool isHex(char ch);

/// @brief 16진수를 문자로 바꿈
/// @param ch 문자
/// @return 16진수
word hexToDigit(char ch);

/// @brief 16진수 문자열을 워드로 변환
/// @param h 문자열
/// @return 16진수 워드
word hexToWord(const char h[], int len);

/// @brief 16진수 문자열을 bigint 배열에 할당
/// @param src 16진수 문자열(const char *)
/// @param dst bigint형 배열
/// @param len src의 길이
void hexstrToBigint(word *dst, const char *src);

#endif