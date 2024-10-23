/**
 *  const | mutable | volatile
 * ----------------------------------
 * respect const
 * just use it
 * const obj & const member doesn' t alter the memory, so no exception occurs
 * 
 * Modern C++:
 *  C++11~ -> constexpr was added to strengthen the compile-time programming
 *  C++20~ -> part of the volatile has become deprecated
 */

void main(void) {

    const int constVal = 10;
    constVal = 20;      // (x) compile error

    constint a = constVal;
    a = 20;             // (x) compile error

    int b = constVal;
    b = 20;             // (0) copied value of a non-const variable can vary
    EXPECT_TRUE(b == 20 && constVal == 10);


    /* -------------------------   */

    int data = 10;
    const int* constPtr = &data;
    const int& constRef = data;

    int* a = constPtr;  // (x) compile error
    const int* b = constPtr;    // (0)
    
    int& c = *constPtr; // (x)
    const int& d = *constPtr; (0)

    int& e = constRef;
    const int& f = constRef;

    /* -------------------------   */
    // const type return
    int GetX1() const { return m_X; }           // (0) member viaralble return as a const
    const int GetX2() const { return m_X; }     // (x) no need to return with a const

    const int* GetX3() const { return &m_X; }   // (0) not changing return value
    int* GetX4 const {return const_cast<int*>(&m_X);} // not rec bc member can be changed secretly
    int* GetX4 { return &m_X; }                 // (0) 

    /* -------------------------   */
    void f(int x) (0)       // x copies the value of x
    void f(const int x);    // not rec bc same as above but f doesn' tchange. no point in calling 
    void f(int* x);         // (0) changes the value of what the x is reference inside f
    void f(int & x);

    void f(const int* x);   // (0) doesn't change the value of what the x is ref inside f
    void f(const int & x);

    /*      constant member function 상수 멤버 함수       */
    class T {
    private:
        int m_Val;
    public:
        void Func() const { // const member function
            m_Val = 10;     // (x) compile error bc can't change the member value in const member function
        }
    }

    /*      변경 가능 지정자 (mutable)      */
    TEST(TestClassicCpp, Mutable) {
        class T {
        public:
            mutable std::wsting m_Lazy;

            const std::wstring& GetString() const {
                if(m_Lazy.empty()) {
                    m_Lazy = L"Lazy String";
                }
                return m_Lazy;
            }
        };
        T t;
        EXPECT_TRUE(t.GetString() == L"Lazy String");
    }
}