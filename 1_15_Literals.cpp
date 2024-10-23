/**
 * Literals & escape words
 * ========================================================
 * 문자열 상수를 많이 만들면, 프로그램 용량이 커진다. 비슷한 문장을 쓸데없이 여러개 작성하지 마라.
 * 
 * Modern C++:
 *  C++11~: long long 용 정수형 상수인 ll, ull, LL, ULL 리터럴이 추가되었습니다
 *  C++11~: nullptr 리터럴이 추가되어 좀더 타입에 안전한 코딩 계약이 가능해 졌습니다.
 *  C++11~: u8"", u"", U"", u"(문자), U"(문자) 리터럴이 추가되어 유니코드를 지원하는
 *      char16_t, char32_t 타입용 문자 상수를 제공합니다.
 *  C++11~: R"()" 리터럴이 추가되어 개행이나 이스케이프 문자를 좀더 편하게 입력할 수 있습니다
 *  C++11~: 사용자 정의 리터럴이 추가되어 int operator "" _km(long double val); 와 같이 사용자가 정의해서 사용할수 있으며,
 *      단위계 처리가 쉬워졌습니다.
 *  C++14~: 이진 리터럴이 추가되어 0b, 0B 접두어로 이진수 상수를 표현할수 있습니다. 
 *  C++14~: 숫자 구분자가 추가되어 1'000'000와 같이 작은 따옴표(')를 숫자 사이에 선택적으로 넣을수 있으며,
 *       가독성이 좋아졌습니다. 
 *  C++14~: 표준 사용자 정의 리터럴이 추가되어 operator ""s, operator ""min, operator ""if, 등 문자영,
 *      날짜 / 시간, 복소수 관련 표현이 간편해 졌습니다.
 *  C++17~: u8"(문자) 리터럴이 추가되어 유니코드를 지원하는 1byte 크기의 문자 상수를 제공합니다
 *  C++17~: 16진수 부동 소수점 리터럴이 추가되어 0xA.9p11 과 같이 16지수로 실수를 표현할수 있습니다.
 * 
 *  리터럴은각 타입에 따른 상수값입니다 (constant). 컴파일 타임에 값이 결정되며, 대부분 코드 세그면트에
 *      저장되어 그 값을 수정할수 없습니다. 문자열 상수만 데이터 세그먼트의 rodata에 저장됩니다.
 * 
 */

int main(void) {

    bool a = true;
    bool b = false;

    int c = 10;     // 10진수
    int d = 010;    // 8 진수
    int e = 0x1a;   // 16 진수
    unsigned int f = 10U;       // unsigned u or U
    unsigned long g = 10U;      //
    long h = 10L;               // long
    unsigned long i = 10UL;     // unsigned long
    long h = 10L;               // long. l or L
    unsigned long i = 10UL;     // unsigned long. u/U/l/L

    double j = 3.14;
    double k = 3.14e10;
    float l = 3.14F;
    float m = 3.14e10F;
    long double n = 3.14L;
    long double o = 3.14e10L;


    /*  const pointer */
    const char* str1 = "abc";           // 문자열 상수
    const wchar_t* str2 = L"abc";       // 와이드 문자열 상수

    char str3[] = "abc";        // {'a', 'b', 'c', '\0'};
    EXPECT_TRUE(str3[0] == 'a');
    EXPECT_TRUE(str3[1] == 'b');
    EXPECT_TRUE(str3[2] == 'c');
    EXPECT_TRUE(str3[3] == '\0');       // 널문자가 추가됨

    wchar_t str4[] = L"abc";    // {L'a', L'b', L'c', L'\0' };
    EXPECT_TRUE(str4[0] == L'a');
    EXPECT_TRUE(str4[1] == L'b');
    EXPECT_TRUE(str4[2] == L'c');
    EXPECT_TRUE(str4[3] == L'\0');
    
    
}