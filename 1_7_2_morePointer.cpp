#include <iostream>
int main(void) {
    int obj = 10;
    int* p1 = &obj; // *p1 수정 가능. p1 수정 가능
    *p1 = 20;

    const int* p2 = &obj; // *p2 수정 불가. p2 수정 가능
    // *p2 = 20;             // (x) compiler error
    p2 = p1;

    int* const p3 = &obj; // *p3 수정 가능. p3 수정 불가
    *p3 = 20;
    // p3 = p1;              // (x) compiler error

    const int* const p4 = &obj // *p4 can't change p4 can't change
    *p4 = 20;             // (x) compiler error
    p4  = p1;             // (x) compiler error

    int a[2] = {1, 2};

    // pointing to the array itself
    int (* p5)[2] = &a;
    EXPECT_TRUE((*p5)[0] == 1 && (*p5)[1] == 2);    // (*p5) can be used to access obj array

    // pointing to the first idx of the array
    int* p6 = a;
    EXPECT_TRUE(*(p6 + 0) == 1 && *(p6 + 1) == 2);
    EXPECT_TRUE(p6[0] == 1 && p6[1] == 2);

    /*      Function Pointer        */
    void TestFunc(int) {}

    void (*p7)(int) = &TestFunc;
    void (*p8)(int) = TestFunc;     // &TestFunc와 동일

    p7(10);     // (*p7)(10) also possible. calls TestFunc
    p8(10);     // (*p8)(10) also possible. calls TestFunc

    /*      Multipointer (hierarchy example)         */
    class Base{
    public: 
        int m_Value;
        virtual void f() {std::cout << "Base" < std::endl;}
    };
    class Derived : public Base {
    public:
        virtual void f() {std::cout << "Derived" << std::endl;}
    };
    // 다행성 포인터 multipointer
    {
        Derived d;
        Base* p9 = &d; // 부모 클래스 포인터로 자식 클래스 제어
        p9->f();
    }

    // member variable pointer - can be utilized when developing a library
    {
        int Base::* p10 = &Base::m_Value;   // Base class member referencing member field
        Base b;
        b.*p10 = 10;
        EXPECT_TRUE(b.m_Value == 10);
    }

    // Member variable pointer
    {
        void (Base::* p11)() = &Base::f;
        Base b;
        (b.*p11)();     // member function pointer, parenthesis needed. calls Base
    }

    // multi dimentional pointer
    int val = 10;
    int* p = &val;
    int** pp = & p;

    EXPECT_TRUE(*p == 10);

    EXPECT_TRUE(*pp == p); 
    EXPECT_TRUE(**PP == 10);

    int obj = 10;
    int& r1 = obj;
    r1 = 20;

    const int& r2 = obj;    
    r2 = 20;        // (x) compiler error

    int& r3 = 20;   // (x) comp error
    const int& r4 = 20; // (0) 

    /* array reference 배열 참조자 */
    int a[2];
    int (&r5)[2] = a;
    r5[0] = 10
    EXPECT_TRUE(a[0] == 10);

    // function ref
    void (&r6)(int) = TestFunc;
    r6(10);     // TestFunc

    return 0;
}