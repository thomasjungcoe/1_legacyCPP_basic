/**
 * Life of Static, extern, obj
 * =================================================== 
 * 변수의 수명(유효 범위)은 짧을 수록 좋다. 최대한 임시 개체나 지역 변수로 사용하라
 * 전역 변수나 정전 전역 변수 보다는 함수내 정적 지역 변수를 사용하라.
 * 컴파일러 최적화가 쉽도록 임시 개체를 사용하라.
 * 
 * Modern C++:
 *  C++11~ -> 이동 연산을 위해 우측값 참조(&&)가 추가되어 임시 개체 대입시 속도가 향상되었습니다.
 *  C++17~ -> 임시 구체화와 복사 생략 보증을 통해 컴파일러 의존적이었던 생선자 호출 및
 *             함수 인수 전달 최적화, 최적화등이 표준화 되었습니다.
 *  C++17~ -> 인라인 변수가 추가되어 헤더 파일에 정의된 변수를 여러개의 cpp에서 #include 하더라도 
 *              중복 정의 없이 사용할수 있습니다. 또한, 클래스 정적 멤버 변수 정의 및
 *              초기화가 쉬워젔습니다
 *  C++20 ->  constinit가 추가되어 전역 변수, 정적 전역 변수, 정적 멤버 변수를 컴파일 타임에 
 *              초기화 할수 있습니다.
 */


/** 
 * // global.h 에서
 * extern int g_Val;
 * 
 * // global.cpp 에서
 * int g_Val = 10;
 * 
 * // 여기저기 파일에서
 * #include "global.h"
 * 
 * namespace {
 *  static int s_Val = 10;
 * }
 * 
 * TEST(TestClassicCpp, Static) {
 *  EXPECT_TRUE(s_Val == 10);
 * }
 */

class Date {
    int m_Year;
    int m_Month;
    int m_Day;
public:
    Date(int year, int month, int day) :
        m_Year(year),
        m_Month(month),
        m_Day(day) {}
    ~Date() {}
};

class T {
public: 
    static int s_Val1; // 선언과 정의 분리 필요. 외부에서 초기값이 세팅되어야 함
    // static int s_Val1 = 10;  // (x) compile error. const만 클래스 선언에서 초기화 지원
    static const int s_Val2 = 20;   // const 인 경우 클래스 선언에서 초기화 지원

};

// 선언 외부에서
int T::s_Val1 = 10; // 초기값 세팅

TEST(TestClassicCpp, Static) {
    EXPECT_TRUE(T::s_Val1 == 10);
    EXPECT_TRUE(T::s_Val2 == 20);
}

// 정적 변수의 초기화 순서

int g_X = 10;
int g_Y = g_X;

// Test_A.cpp 에서
int f() { return 10; }
int g_A = f();      // static variable. reset at runtime through f() function

// Test_B.cpp 에서
#include <iostream>


extern int g_A;
int g_B = g_A;  // (~) not recomended; 0 at compile time. later in terms of link level reset.
                //      because there is no garentee of the reset for g_A, the value can range from 0 ~ 10 depending on link level.

int main() {
    std::cout << "g_A: " << g_A << std::endl;
    std::cout << "g_B: " << g_B << std::endl;

    return 0;
}

/*  use of explicit to disallow type-conversion     */
class A {
private: 
    A() {}  // private 여서 외부에서 생성살수 없습니다
public: 
    static A& GetInstance() {
        static A s_A;
        return s_A;
    }
};

class B {
private: 
    explicit B(A) {}    // private 여서 외부에서 생성할수 없습니다. A로부터 생성됩니다.

public:
    static B& GetInstance() {
        static B s_B(A::GetInstance());     // A::GetInstance()로 A개체는 반드시 생성되고 초기화 됨을 보장합니다
        return s_B;
    }
};

class C {
private:
    explicit C(B) {}    // private 여서 외부에서 생성할수 없습니다 B로부터 생성됩니다
public:
    static C& GetInstance() {
        static C s_C(B::GetInstance());     // B::GetInstance9) 로 B 개체는 반드시 생성되고 초기화 됨을 보장합니다.
        return s_C;
    }
};

A& g_A = A::GetInstance();
B& g_B = B::GetInstance();
C& g_C = C::GetInstance();

/* 임시 개체 temp obj */
class T {};

T();   // 임시 개체 T()가 생성되고 아무곳에서도 사용하지 않았으므로 소멸됩니다
T a = T(); // 임시 개체 T()가 생성되고 a 에게 복사 생성합니다. 다만 컴파일러 최적화
           //   의해 생성자를 1회 호출하기는 합니다
T& b = T();// compile error 임시 개체는 소멸되었으므로 참조할수 없습니다.
const T& c = T();   // const로 사용하면 수명이 연장됨니다.

class T {
public:
    static int f(int x) {
        return x * x;   // 리턴시 임시 개체 생성
    }
};

int result = T::f(1 + 1); // 인수ㅇ를 인자에 전달시 임시 개체 생성

/* same as the following */
class T {
public:
    static int f(int x) {
        int temp = x * x;       // 인시 개체 생서하여 리턴합니다
        return temp;
    }
};

// following is not recomended bc compiler might not be able to optimize
int temp = 1 + 1;           // 임시 개체를 생성하여 합수에 전달합니다.
int result = T::f(temp);    // 임수를 인자에 전달시 임시 개체 생성

