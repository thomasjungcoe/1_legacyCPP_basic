/**
 *          NAMESPACE
 *  Instead of using prefix to avoid naming conflitcs, use namespaces
 *  Be mindful of the increase scope due to "using" 
 *      (globally, using namespace can be destructive)
 * 
 *  Modern C++:
 *      11 -> inline namespace was added (easier API version composition)
 *      17 -> simple nested namespace can be shortkeyed using "::"
 */

namespace A {
    int f() { return 10; }
}

namespace B {
    int f() { return 20; }
}

// As project scales into bigger one, simple naming can cause conflitcs
// one can avoid by using namespaces
EXPECT_TRUE(A::f() == 10);  // namespace A의 f() 호출
EXPECT_TRUE(B::f() == 20); // 네임스페이스 B의 f() 호출

// Parse 
namespace Parser {
    void Tokenizer() {}
    void Load() {}
}


/**
 * How to use namespaces
 *  항목	내용
    정의	namespace Test {
                void f() {}
            }
    사용	Test::f();
    using   선언	네임스페이스의 특정 항목 사용.
    using   Test::f;
    using   지시문	네임스페이스의 전체 항목 사용.
    using   namespace Test;
 */

namespace C {
    int f() {return 30;} // define
    int g();             // declare
    int h();             // declare
}

namespace C {
    int g() {           // define
        return f();     // don't have to use C::f() on the same namespace
    }
}

int C::h() {            // expressing "C::" to define
    return f();
}
EXPECT_TRUE(C::g() == 30);
EXPECT_TRUE(C::h() == 30);


/*      using different namespace           */
namespace D {
    void d1() {}
    void d2() {
        d1();       // no need for D:: within the same namespace
    }
}

namespace E {
    void e() {
        D::d1();    // need D:: for using another namespace
    }
    void f() {
        using D::d1;    // calling d1 using declare
        d1();           // d1 can be used w/o D:: since it's declared
        D::d2();        // need D:: since new
    }
}

namespace F {
    using namespace D;  // using declare

    void f() {
        d1();           // D::d1 not needed since it's declared
        d2();           // the same
    }
}

/*      don't globally use "using"    */
namespace MyModule1 {
    void Test() {}
}

namespace MyModule2 {
    void Test() {}
}

using namespace MyModule1;      // brings in MyModule1 globally
using namespace MyModule2;

namespace MyModule3 {
    void f() {
        Test();     // (x) compile error because no way to know 
                    //     MyModule1::Test() or MyMydule2::Test()
    }
}

/*          nameless namespace              */
namespace {
    void f();       // can only be used on defined file scope
}

/*          nested namespace        */
namespace MyLib {
    namespace Parser {
        void Tokenizer() {}
    }

    namespace File {
        void Load() {};
        void Save() {};
    }
}

MyLib::Parser::Tokenizer();
MyLib::File::Load();


/*          Alias & synthesis(?)        */
// Can change the name using alias but can't create more function on top of that
namespace MyTestLibrary {
    int f() { return 40; }
}

namespace MTL = MyTestLibrary;  // created Alias

namespace MTL {
    void g() {}         // compile error due to new definition
}

EXPECT_TRUE(MTL::f() == 40);


/*          Multiple alias      */
namespace G {
    int f() {return 50;}
}
namespace H {
    int g() {return 60;}
}
namespace MyModule {
    using namespace G;
    using namespace H;
}

EXPECT_TRUE(MyModule::f() == 50);
EXPECT_TRUE(MyModule::g() == 60);

/*      Managing codes using namespace      */
namespace MyLib {
    namespace Windows {
        int f() {return 1;} // #1
    }
    namespace Linux {
        int f() {return 2;} // #2
    }
};

namespace YourLib {
    using namespace MyLib::Windows; // Windows 버전을 사용합니다.

    int g() {
        return f(); // MyLib::Windows::f()가 호출됩니다.
    }
};

EXPECT_TRUE(YourLib::g() == 1);