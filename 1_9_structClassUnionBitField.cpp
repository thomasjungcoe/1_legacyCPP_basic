/**
 *      Struct vs Class vs Union vs Bitfields
 * --------------------------------------------------
 * Utilize SOLID principle to create struct, class, and the union
 * The difference between a struct and a class is initialization & 
 *      accessors(mod.): public, private, etc
 * Use "Union" carefully because it can very depending on the platform, 
 *      compiler, setting options
 * 
 * Modern C++:
 *  C++11~ -> unlimited usage of Union & limits on contrcutor, 
 *      destructor, and virtuals have been lifted to better strategize memory efficiency
 *  C++17~ -> variant was added to hold different types in a same container
 *  C++20~ -> bit field declaration * initialization have been added
 */

void main() {
    struct S {
        int x;  // public in default
        int y;
    };

    S s = {10, 20}; // struct supports bracket initializiation

    class C {
        int m_X;    // normally private
        int m_Y;
    public:
        C(int x, int y) {}  // constructor
    };
    C c(10, 20);    // class supports contructors but not {} initialization

    /* struct & class */
    class T {
        // memeber
        int m_D1;

        // static const int s_D2 = 1; // (x) can't use in local class

        // -------
        // member function
        // -------
        T() {}                  // default constructor
        T(const T& other) {}    // copy constructor
        ~T() {}                 // destructor
        T& operator =(const T& other) { return *this;}  // copy asignment operator (복사 대입 연산자)
        
        operator int() const {return 0;}                

        void f1(int) {}
        void f2(int) const {}

        virtual void f3(int) {}
        virtual void f4(int) = 0;

        static void f5(int) {}
        // -------

        // 영거영 상수 enum
        enum {Left, Top, Right, Bottom};

        class NestedClass {
            int m_D3;
        };

        typedef NestedClass Inner;
    }

    // inline function
    // h 에서
    class T {
        int f1() {}     // compiler decides if it's inline
        int f2();       // declared only so no inline
    };

    // cpp 에서
    int T::f2() {}      // no inline

    /*      Friend      */
    class FriendT {
        friend class U;
        friend void Func();
    private:   
        int m_Val1;
        void f() {}
    protected:
        int m_Val2;
        void g() {}

    };

    void Func() {
        FriendT t;
        t.m_Val1;       // not recomended because accessing private field
        t.f();
        t.m_Val2;       // not rec bc protected field
        t.g();
    }
    class U {
        friend class W;
        void f() {
            FriendT t;
            t.m_Val1;    // not rec. private access
            t.f();
            t.m_Val2;
            t.g();
        }
    };
    class V : public U {
        void f() {
            FriendT t;
            t.m_Val1;    // (x) compile error. no relationship to the class
            t.f();
            t.m_Val2;    // (x) compile error. no relationship to the class
            t.g();
        }
    };
    class W {  
        void f() {
            FriendT t;
            t.m_Val1; // (X) 컴파일 오류. friend의 friend는 접근 불가
            t.f();
            t.m_Val2; // (X) 컴파일 오류. friend의 friend는 접근 불가
            t.g();     
        }
    }

    /*      공용체(Union Type)      */
    class C {
    private:
        int m_Val1;
        int m_Val2;

    public:
        // C(int v1, int v2) {}     // (x) compile error bc Union can't have contructor
        // ~C() {}                  // (x) compile error bc Union can't have a destructor
        int GetVal1() const {return m_Val1;}   // can have member function but can't be virutal
        void SetVal1(int val) { m_Val1 = val;}
    };

    struct S1 {
        int x;
        int y;
    };

    struct S2 {
        int x;
        int y;
        int z;
    };

    union U {
        C c;    // members can share memory
        S1 s1;
        S2 s2;
    public:
        int GetX() const {return s1.x;}     // union types can also have function
    };

    U u;
    EXPECT_TRUE(sizeof(u) == sizeof(S2));   // pick the field with highest memory usages
    
    u.s1.x = 10;
    EXPECT_TRUE(u.GetX() == 10);
    EXPECT_TRUE(u.c.GetVal1() == 10);
    EXPECT_TRUE(u.s2.x == 10);

    u.c.SetVal1(20);    // change the value of c but s1 & s2 also changed
    EXPECT_TRUE(u.c.GetVal1() == 20);
    EXPECT_TRUE(u.s1.x == 20);
    EXPECT_TRUE(u.s2.x == 20);


    /*    this pointer    */
    class Outer {
        int m_OuterVal;
        void f() {
            class Inner {
                int m_InnerVal;
                void f() {
                    this->m_InnerVal;       // this of Inner class
                }
            };
            this->m_OuterVal;               // this of outer class
        }
        class Nested {
            int m_NestedVal;
            void f() {
                this->m_NestedVal;          // Nested class's this
            }
        };
        static void Func() {
            this->m_OuterVal;       // (x) compile error bc can't access from static function
        }
    }

    // can't use this for initializatio of list
    class T {
        int m_Val;
    public:
        explicit T(int val) : 
            // this->m_Val(val), // (x) compile error 
            m_Val(this->m_Val) { // (0) this works for param
                this->m_Val;     // (0) also works for this
            }
    };

    /*      delete this can be used to delete itself 
            but if used on stack created obj, exception occurs */
    class T {
    public:
        ~T() {
            std::cout << "T::~T();" << std::endl;
        }
        void Release() {
            delete this;    // (0) deletes itself by calling destructor
        }
    };

    T t1;   // stack construction
    t1.Release();   // (x) exception occurs bc deleting stack created obj

    T* t2 = new T;  // Heap created
    t2->Release();  // (0)


    /*  classes,struct,&union inside function */
    void OuterFunc() {
        class InnerClass {
        public:
            int m_X;
        };
        struct InnerStruct {};      
        union InnerUnion {};

        InnerClass t;
        t.m_X = 10;
        EXPECT_TRUE(t.m_X == 10);
    }

    class Class {
        class NestedClass {};
        struct NestedStruct {};
        union NestedUnion {};
    };
    struct Struct {
        class NestedClass {};
        struct NestedStruct {};
        union NestedUnion {};
    };
    union Union {
        class NestedClass {};
        struct NestedSTruct {};
        union NestedUnion {};
    };
    class Outer {
    private:
        int m_Val;
        static int s_Val;
    public:
        class Nested {
        public:
            void f(Outer *outer) {
                s_Val;      // (0) Outer's private  static accessible
                outer->m_Val;   // (0) Outer's private field accessible
            }
        };
        void g() { 
            Nested nested;
            nested.f(this);     // (0) 개체를 인스턴스화 하여 접근 가능
        }
    };
    Outer::Nested nested; // (O) 외부에서 접근할 경우 :: 사용

    /*      Bit FIeld       */
    class Flag {
    public:
        unsigned char m_Val1 : 2;   // 2bit 00(0), 01(1), 10(2), 11(3)
        unsigned char m_Val2 : 3;   // 3bit 000(0), 001(1), 010(2), 011(3), 100(4), 101(5), 110(6), 111(7)
    };

    Flag flag;
    EXPECT_TRUE(sizeof(flag) == sizeof(unsigned char));

    // 주어진 비트 범위내의 데이터는 잘 저장함
    flag.m_Val1 = 3;    // 0~3 저장
    flag.m_Val2 = 7;    // 0~7 저장

    EXPECT_TRUE(flag.m_Val1 == 3);
    EXPECT_TRUE(flag.m_Val2 == 7);
    
    // 저장 곤간이 부족하면 상위 비트를 버림
    flag.m_Val1 = 5;  // not good -> 101을 대입하면 앞의 1은 저장하지 못하고 01만 저장됨
    flag.m_Val2 = 15; // not good -> 1111을 대입하면 앞의 1은 저장하지 못하고 111만 저장됨

    EXPECT_TRUE(flag.m_Val1 == 1);
    EXPECT_TRUE(flag.m_Val2 == 7);

    unsigned char* ptr = &flag.m_Val1;  // (x) compile error bc no support for pointer to bit field
    unsigned char& ref =  flag.m_Val1; // (X) 컴파일 오류. 비트 필드는 레퍼런스를 지원하지 않습니다.

}