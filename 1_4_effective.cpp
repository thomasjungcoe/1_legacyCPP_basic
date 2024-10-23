/***
 *              Effective Range 
 *  keep the effecive range as minimal as possible
 *      ({ }) <-- can be utilized for this purposes
 * 
 *  The reason for this is because as the project scales,
 *      good naming & small scope help reduce conflicts
 * */

namespace {
    int x = 1;      // global
}

TEST(TestClassicCpp, Scope) {
    EXPECT_TRUE(x = 1);     // global still
    int x = 2;
    EXPECT_TRUE(x = 2);     // local referencing global
    {
        int x = 3;
        EXPECT_TRUE(x == 3) // no way to reach local
        ::x = 10;           // :: <-- forcing entry into global
    }
    EXPECT_TRUE(x == 2)     // local var
    EXPECT_TRUE(::x == 10); // global var
}

void f() {
    int a;
    int b;
    // a~b usage codes

    {
        int c;
        int d;
        // c & d usage codes
    }

    {
        int e;
        int f;
        // e & f usage codes
    }
}