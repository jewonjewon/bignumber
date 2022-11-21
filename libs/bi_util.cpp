#include <iostream>
#include <math.h>

#include "../includes/bi_util.h"
#include "../includes/bi.h"

int getBlockLen(int len)
{
    return (int)ceil((long double)len / WORD_LEN);
}

/// @brief 입력받은 문자가 16진수인지 확인
/// @param ch 문자
/// @return 16진수일 경우 true(1), 아닐 경우 false(0) 출력
bool isHex(char ch)
{
    return ((ch >= '0') && (ch <= '9') || (ch >= 'A') && (ch <= 'F') || (ch >= 'a') && (ch <= 'f'));
}

/// @brief 16진수를 문자로 바꿈
/// @param ch 문자
/// @return 16진수
word hexToDigit(char ch)
{
    // ch가 16진수가 아닐 경우 에러값 리턴하며 함수 종료
    if (!isHex(ch))
    {
        // cout << ch << " is not a hex value.\n";
        perror("hexToDigit()");
        exit(1);
    }

    // ch가 '0'~'9'일 경우
    if ((ch >= '0') && (ch <= '9'))
        return ch - '0';
    /// ch가 'A'~'F'일 경우
    else if ((ch >= 'A' && (ch <= 'F')))
        return ch - 'A' + 10;
    /// ch가 'a'~'f'일 경우
    else if ((ch >= 'a' && (ch <= 'f')))
        return ch - 'a' + 10;
    // 알 수 없는 에러
    else
    {
        cout << "unknown error\n";
        return -1;
    }
}

/// @brief 16진수 문자열을 워드로 변환
/// @param h 문자열
/// @return 16진수 워드
word hexToWord(const char h[], int len)
{
    word ret = 0;

    for (int j = 0; j < len; j++)
    {
        if (!isHex(h[j]))
        {
            perror("ERROR in hexToWord()");
            exit(1);
        }
    }

    for (int j = len - 1; j >= 0; j--)
    {
        ret |= ((hexToDigit(h[j]) & 0xf) << (4 * (len - j - 1)));
    }

    return ret;
}

/// @brief 16진수 문자열을 bigint 배열에 할당
/// @param src 16진수 문자열(const char *)
/// @param dst bigint형 배열
/// @param len src의 길이
void hexstrToBigint(word *dst, const char *src, int len)
{
    char h[WORD_LEN];
    int blklen = getBlockLen(len);

    for (int i = 0; i < (len / WORD_LEN); i++)
    {
        memcpy(h, src + len - WORD_LEN * (i + 1), WORD_LEN);
        dst[i] = hexToWord(h, WORD_LEN);
    }

    // 최상단 블록 처리
    if ((len % WORD_LEN) != 0)
    {
        memcpy(h, src, (len % WORD_LEN));
        dst[len / WORD_LEN] = hexToWord(h, len % WORD_LEN);
    }
}
