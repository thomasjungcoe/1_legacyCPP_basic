/**
 * 문자열 string
 * =========================================
 * 수정될 필요가 없는 문자열 테이터는 const char* 나 const wchar_t*로 관리하라.
 *      (배열이나 string, wstring 을 쓰면 복제된다.)
 * 멀티 바이트 문자열은 권장하지 않는다. 사용하지 마라.
 * 소스 코드 저장시에는 다국어 처리에 적합하도록 UTF-8 인코딩로 저장하라.
 * 
 * Modern C++:
 *  C++11~: u8"", u"", U"", u"(문자), U"(문자) 리터럴이 추가되어 유니코드를 지원하는
 *      char16_t, char32_t 타입용 문자 상수를 제공합니다.
 *  C++11~: u16string이 추가되어 UTF-16 인코딩 문자열을 지원합니다.
 *  C++11~: u32string이 추가되어 UTF-32 인코딩 문자열을 지원합니다.
 *  C++17~: u8"(문자) 리터럴이 추가되어 유니코드를 지원하는 1byte 크기의 문자 상수를 제공합니다
 *  C++20~: u8string이 추가되어 UTF-8 인코딩 문자열을 지원하니다.
 */

/*  널종료 문자열    */
size_t MyStrlen(const char * str) {
    size_t length = 0;
    while (*str != '\0') {  // 널문자를 만날때까지 카운팅합니다 
        ++str;
        ++length;
    }
    return length;
}
EXPECT_TRUE(MyStrlen("abc") == 3);

char str[] = "abc"; // (0) {'a', 'b', 'c', '\0' };
EXPECT_TRUE(str[0] == 'a');
EXPECT_TRUE(str[1] == 'b');
EXPECT_TRUE(str[2] == 'c');
EXPECT_TRUE(str[3] == '\0');    // 널문자 추가됨
EXPECT_TRUE(sizeof(str) == 4);  // 널문자까지 포함하여 4byte 크기 입니다.
EXPECT_TRUE(sizeof(str) / sizeof(char) == 4);   // 배열 갯수는 널문자를 포함하여 4 입니다.
EXPECT_TRUE(strlen(str) == 3);  // 문자열의 길이는 널문자를 제외한 3입니다.


/* 문자열 상수 수정 */
const char* str1 = "abc";       // 문자열 상수
char* temp = const_cast<char*>(str1);
// (x) 예외 발생. 문자열 상수는 rodata에 있기 때문에 수정할수 없습니다
*temp = 'd';

char str2[] = "abc";    // {'a', 'b', 'c', '\0' };
// (0) 배열은 문자열 상수의 복제본이어서 항목을 수정할수 있습니다.
str2[0] = 'd';
EXPECT_TRUE(str2[0] == 'd');

/*  Aschii code 아스키 코드   */
