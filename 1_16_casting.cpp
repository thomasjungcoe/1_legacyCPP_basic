/**
 * 형변환 (const_cast, static_cast, dynamic_cast, reinterpret_cast, explicit) 
 *      과 형변환 연산자 정의
 * ==========================================================================
 * 암시적 형변환은 실수하기 쉽게 만든다. 명시적으로 형변환하라.
 * bool 형변환 연산자 정의는 하지 마라. 나아가 모든 타임의 형변환 연산자 정의를 하지마라.
 *      뜻하지 않게 몰래 암시적 형변환한다.
 * 인자가 1개인 값 생성자는 explicit 로 암시적 형변환을 차단하라.
 * 할수 있는한 최선을 다하여 형변환하지 마라.
 * 
 * Modern C++:
 *  C++11: 중괄호 복사 초기화의 = {} 표현을 차단하기 위해 생성자의 함수 인자가 
 *      여러개 있더라도 explicit를 사용합니다.
 * C++11~: explicit 형변환 연산자가 추가되어 명시적으로 형변환 할수 있습니다.
 * C++11~: shared_ptr 형변환 (const_pointer_cast(), static_pointer_cast(),
 *      dynamic_pointer_cast())가 추가되어 shared_ptr의 관리 개체를 
 *      형변환 할수 있습니다
 * C++17~: reinterpret_pointer_cast()가 추가되었습니다.
 * C++20~: explicit(bool)이 추가되어 특정 조건일 때만 explicit로 동작하게 할수 있습니다.
 * 
 */

{
    // char, signed char, unsigned char, short 는 가능하면 int 로 변환, 안되면 unsigned int
    int a = (char)'a';
    int b = (signed char)'a';
    int c = (unsigned char)'a';
    int d = (short)1;
}
{
    // wchar_t는 int, unsigned int, long, unsigned long 으로 변환
    int a = (wchar_t)L'a';
    unsigned int b = (wchar_t)L'a';

    long c = (wchar_t)L'a';
    unsigned long d = (wchar_t)L'a';
}
{
    // 열거형은 int, unsigned int, long, unsigned long 으로 변환
    enum Color {Black};
    int a = (Color)Black;
    unsigned int b = (Color)Black;
    long c = (Color)Black;
    unsigned d = (Color)Black;
}
{
    // bool 은 int (true : 1, false : 0) 로 변환
    int a = (bool)true;
}
{
    // float 은 double 로 변환
    double e = (float)1.0F;
}
{
    // non-const는 const로 변환. 반대는 컴파일 오류
    int a = 10;
    cons tint* b = &a;
    // int* c = b;  // (x) compile error. const는 non-const로 변환 안됨.
}
{
    // 모든 포인터는 void*로 변환. NULL은 모든 포인터로 변환
    int a = 10;
    void*p = &a;
    p = NULL;
}
{
    // 자식 개체는 부모 개체로 변환됨 (Up Casting)
    class Base {};
    class Derived : public Base {};

    Derived d;
    Base& b = d;
}

/* 명시적(explicit) 형변환  (C-style 형변환) -> const_cast, static_cast, dynamic_cast, & reinterpret_cast */
/*  const_cast  */
/*      -> const_cast는 포인터나 참조자의 상수성(constancy)을 뗄수 있습니다 (그러나 상수성 계약 위반이니 하지 마세요.)*/
{
    int a = 10;
    const int&r = a;

    // r이 상수성 계약으로 참조하는데 멋대로 바꿨습니다
    // (~) 비권장. 상수성 계약상 금지입니다
    const_cast<int&>(r) = 20;   // const_cast는 포인터와 참조자만 가능함

    EXPECT_TRUE(a == 20);
}
/* static_cast  */
/*      static_cast는 암시적(implicitly)으로 형변환되지 않는 것들을 명시적(explicitly)으로 형변환할수 
        있습니다. (하지만 타입에 기반한 코딩 계약을 위반하니 사용하지 마세요.)*/
{
    // 실수를 정수로 명시적 변환.
    // (~) 비권장. 그냥 내릴, 반올림, 올림 함수를 쓰세요.
    int a = static_cast<int>(3.14F);
    EXPECT_TRUE(a == 3);

    // 정수를 열거형 상수로 변환.
    // (~) 비권장. 변환 함수를 따로 만드세요.
    enum Color {Black = 0};
    Color b = static_cast<Color>(0);

    // void* 를 다른 포인터로 변환.
    // (~) 비권장. 괜히 void* 바뀌놓지 말고 원래 포인터 타입으로 쓰세요
    int c = 10;
    void* v = & c;
    int * p = static_cast<int*>(v);
}
{
    // 부모 개체를 자식 개체로 변환 (Down Casting)
    class Base {};
    class Derived: public Base {};
    class Other {};

    Derived d;
    Base& b = d;
    // static_cast는 상속관계가 있어야 함(런타임 검사를 수행하지 않음).
    // (~) 비권장. 자식 개체에 의존성을 두지 마세요.
    Derived& downCasting = static_cast<Derived&>(b);

    // (x) compile error. b는 other와 아무런 상속관계가 없음
    Other& other = static_cast<Other&>(b);
}
/*  dynamic_cast    */
/*      dynamic_cast는 상속 관계가 있는 개체간의 형변환을 합니다. (Runtime Type Info(RTTI)가 있는 개체
            (가상 함수가 있는 개체)만 가능.) 변환에 실패하면, 포인터 유형인 경우 널(NULL)을 리턴하고,
            참조 유형인 경우 bad_cast 예외를 발생시킵니다. */
class Base {
public: 
    // dynamic_cast를 사용하려면 가상 함수가 있어야 합니다.
    // RTTI(Runtime Type Info)가 필요하기 때문입니다.
    virtual ~Base() {}
};
class Derived: public Base {};
class Other {};

Derived d;
Base* b = &d;
// dynamic_cast는 상속관계가 있어야 함(런타임 검사를 수행함)
// dynamic_cast는 사용하려면 가상 합수가 있어야 합니다. (가상 합수가 없으면 컴파일 오류)
Derived* downCasting = dynamic_cast<Derived*>(b);
EXPECT_TRUE(downCasting != NULL);

// (0) 상속관계가 아니어서 형변환이 안되면 포인터의 경우 NULL을 리턴하고,
// 참조유형은 bad_cast 예외를 방생시킵니다.
Other* other = dynamic_cast<Other*>(b);
EXPECT_TRUE(other == NULL);


{
    class Base {};
    class Other {};
    Base b;
    // (~) 비권장. 상속관계가 없더라도 변환해 줍니다.
    Other& other = reinterpret_cast<Other&>(b);

    // (x) compile error. 대행의 주소를 그냥 char에 담아버리지는 않습니다.
    char a = reinterpret_cast<char>(&b);

    int i = 10;
    const int* p1 = &i;
    // (x) compile error. 상수성은 지켜줍니다.
    int* p2 = reinterpret_cast<int*>(p1);

    // (~) not recomended. 정수를 포인터로 변환합니다.
    int* p3 = reinterpret_cast<int*>(i);

    // (x) 컴파일 오류. 포인터를 정수로 변환은 안됩니다.
    int j = reinterpret_cast<int>(p3);
    
}

/* 아무 관계도 없는 타입끼리 형변환 */
class T {};
class U {};

// 아무 연관 관계도 없는 타입끼리는 형변환되지 않습니다.
T t;
U u1 = (U)t;                // (x)
U u2 = static_cast<U>(t);   // (x)
U u3 = reinterpret_cast<U>(t) // (x)

// 포인터와 타입은 형변환 됩니다만, 최대한 사용하지 마세요.
U* u4 = (U*)&t;                     // (~) 비권장
U* u5 = static_cast<U*>(&t);        // (x)
U* u6 = reinterpret_cast<U*>(&t)    // (~)

/*  형변환 연산자 정의  */
class T{ 
public: 
    // int 로 형변환 되면 10을 리턴합니다.
    operator int() const { return 10; }

    // char로 형변환 되면 1을 리턴합니다
    operator char() const { return 1; }
};

T t;
int i = t;
char c = t;

EXPECT_TRUE(i == 10);
EXPECT_TRUE(c == 1);

class U {};
class T {
public:
    operator U() const { return U(); }  // (~) 비권장. 현변환 연산자를 정의하여 암시적으로 형변환됨
}

T t;

U u1 = t;       // (~) 암시적 변환
U u2 = (U)t;    // (~) C언어 스타일 형변환
U u3 = static_cast<U>(t);       // (0)

/* 타입끼리 변환이 필요하다면 다음처럼 변환 함수를 사용하세요 */
class U {};
class T {
public:
    // int로 변환합니다.
    int ToInt() const {return 10;}

    // char로 변환합니다
    char ToChar() cons t{return 1;}

    // U 로 변환합니다
    U ToU() const { return U(); }
};

T t;
int i = t.ToInt();
char c = t.ToChar();
U u = t.ToU();

/*  안전하지 않은 bool 형변환 연산자 정의   */
class T {
public:
    operator bool() { return true; }
};

T t;
bool status = false;
// (~) 버권장. 컴파일 오류가 나지 않는 비극
// t가 bool로 변환되어 true 가 되고,
// 암시적으로 true 가 int로 변환되어 1이 되고 조건식이 참이 됨
// 의도한 코드인지를 모르겠으나,
// 이렇게 암시적인 상황을 활룡해서 복잡하게 의도하는 건 코드 분석이나 코딩 계약에 좋지 않음
if (0 < t) {
    status = true;
}
EXPECT_TRUE(status == true);


/*      명시적 변환 생성 지정자 (explicit)      */
class T {};
class U {
public:
    U() {} // 기본 생성자
    U(T t) {}   //(~) 비권장. explicit 없이 값 생성자를 정의하면 암시적으로 형변환됨
};

T t;

U u1(t);        // (0) 명시적으로 값 생성자 호출
U u2 = t;       // (~) 비권장. 암시적 변환
U u3 = (U)t;    // (~) 비권장. C 언어 스타일 형변환
U u4 = static_cast<U>(t);   // (0) static_cast 변환
U u5;   // 기본 생성자로 생성
ut = t; // (~) 비권장. 생성후 값 대입시 암시적 변환

/*  명시적 형변환도 못하게 만들고 싶은데, 문법의 한계로 방법이 없네요.  */
class T {};
class U {
public: 
    U() {}      // 기본 생성자
    explicit U(T t) {}      // (0) 암시적 형변환을 금지합니다. 명시적 변환은 가능합니다.
};

T t;

U u1(t);        // (0) 명시적으로 값 생성자 호출
U u2 = t;       // (x)
U u3 = (U)t;    // (~) 비권장. c언어 스타일 형변환
U u4 = static_cast<U>(t);   // (0) static_cast 변환
U u5;   // 기본 생성자로 생성
u5 = t; // (x)

/*  코딩 계약을 무시하는 암시적 형변환      */
class Year {
public:
     Year(int val) {}   // (~) 비권장. int가 암시적 형변환 됩니다
}

class Month {
public:
    enum Val {
        Jan, Feb, Mar, Apr, 
        May, Jun, Jul, Aug, 
        Sep, Oct, Nov, Dec
    };
};

class Day {
public:
    Day(int val) {} // (~) 비권장. int 가 암시적 형변환 됩니다.
};

class Date {
public:
    // (0) Year, Month, Day 를 입력하여야만 생성됩니다.
    Date(Year year, Month::Val month, Day day) {}     
    // Date 클래스는 타입에 기반한 코딩계약을 잘 만들어 주었지만,
    // Year 와 Day 는 인자가 1개인 생성자 (int 타입 전달) 가 있기 때문에,
    // int 를 Year 와 Day 로 암시적으로 형변환합니다.
}

Date d1(Year(2023), Month::Jan, Day(10));   // (0) 코딩 계약 준수.
Date d2(2023, Month::Jan, 10);              // (~) 버권장, 컴파일이 되요
Date d3(31, Month:Jan, 13);                 // (~) 비권장, 31년 1월 13일로 의도하고 입력한게 맞을까요?
/*  그러니, 암시적 형변환이 되지 않도록, 인자가 1개인 값 생성자에 explicit를
꼭 넣으셔야 합니다.     */