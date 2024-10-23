/**
 * Enum
 * -----------------------
 * 
 * Enum can be used on Class or namespaces to reduce name range
 * 
 * Modern C++:
 * C++11~ 범위 있는 열거형이 추가되어 이름 충돌 회피가 쉬워졌고, 
 *           암시적 형변환을 차단하며, 전방 선언도 지원합니다.
 * C++11~ enum basic type can be assigned
 * C++20~ using enum
 * 
 * enum Week { Sunday, Monday };
 * Week obj = Sunday;
 */

enum Week {
    Sunday, Monday, Tuesday, Wednesday,
    Thursday, Friday, Saturday
};

Week week = Sunday;

Class Week {
public:
    enum Val {
        Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
    };
};

Week::Val val = Week::Sunday;
EXPECT_TRUE(val == Week::Sunday);