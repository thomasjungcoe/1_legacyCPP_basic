/**
 * 연산자들(Operators)과 연산자 오버로딩
 * ==============================================================
 * 
 * 임시 개체가 생성되지 않도록 이항 산술 연산자 (a = a + b) 보다는 산술형 대입 연산자 (a += b)를 사용하라
 * 후위형 증감 연산자는 헷갈리고, 쓸데없는 임시 개체가 생성되니 사용하지 마라.
 * 비교 연산 오버로딩은 < 을 활용해서 구연하라.
 * 
 * Modern C++:
 *  C++11~: 사용자 정의 리터럴이 추가되어 int operator ""_km(long double val); 와 같이 사용자가 정의해서 
 *      사용할수 있으며, 단위계 처리가 쉬워졌습니다.
 *  C++11~: sizeof...() 연산자가 추가되어 가변 템플릿에서 파라메터 팩의 인자수를 구할수 있습니다.
 *  C++11~: 멤버의 sizeof() 시 동작이 개선되어 개체를 인스턴스화 하지 않더라도 개체 멤버의 
 *      크기를 구할수 있습니다.
 *  C++11~: type_index 가 추가되어 type_info 를 컨테이너에서 관리할수 있습니다.
 *  C++11~: addressof()가 추가되어 operator &() 가 연산자 오버로딩 되었어도 실제 주소를 구할수 
 *      있습니다.
 *  C++20~: 삼중 비교 연산자가 추가되어 비교 연산자 구현이 간소화 되었습니다.
 *  C++20~: 비트 쉬프트 연산자의 기본 비트가 표준화되어 << 1는 곱하기 2의 효과가 있는 비트 (즉, 0)로 채워지고, 
 *      >> 1 은 나누기 2의 효과가 있는 비트(즉, 양수면 0, 음수면 1)로 채워집니다.
 */

/*  복사 대입 연산자    */
// 복사 대입 연산자는 = 와 같은 기본 복사 대입 연산자와 산술 연산이나 비트 연산의 결과값을 대입하는 산술형 대입 
//      연산자가 있습니다. (a += b 는 a = a + b 와 결과가 같습니다.)
/* 
복사 대입	    a = b	O	T& T::operator =(const T2& b);	X
추가 대입	    a += b	O	T& T::operator +=(const T2& b);	T& operator +=(T& a, const T2& b);
빼기 대입	    a -= b	O	T& T::operator -=(const T2& b);	T& operator -=(T& a, const T2& b);
곱셈 대입	    a *= b	O	T& T::operator *=(const T2& b);	T& operator *=(T& a, const T2& b);
나누기 대입	    a /= b	O	T& T::operator /=(const T2& b);	T& operator /=(T& a, const T2& b);
나머지 대입	    a %= b	O	T& T::operator %=(const T2& b);	T& operator %=(T& a, const T2& b);
비트 AND 대입	a &= b	O	T& T::operator &=(const T2& b);	T& operator &=(T& a, const T2& b);
비트 OR 대입	a |= b	O	T& T::operator |=(const T2& b);	T& operator |=(T& a, const T2& b);
비트 XOR 대입	a ^= b	O	T& T::operator ^=(const T2& b);	T& operator ^=(T& a, const T2& b);
비트 Left Shift 대입	a <<= b	O	T& T::operator <<=(const T2& b);	T& operator <<=(T& a, const T2& b);
비트 Right Shift 대입	a >>= b	O	T& T::operator >>=(const T2& b);	T& operator >>=(T& a, const T2& b);
*/

/*  산술(arithmatic) 연산자     */
/*
  항목	    내용	  연산자 오버로딩	개체 멤버 정의	                    개체 비멤버 정의
단항 양수	+a	            O	T T::operator +() const;	        T operator +(const T &a);
단항 음수	-a	            O	T T::operator -() const;	        T operator -(const T &a);
더하기	    a + b	        O	T T::operator +(const T2 &b) const;	T operator +(const T &a, const T2 &b);
빼기	    a - b	        O	T T::operator -(const T2 &b) const;	T operator -(const T &a, const T2 &b);
곱하기	    a * b	        O	T T::operator *(const T2 &b) const;	T operator *(const T &a, const T2 &b);
나누기	    a / b	        O	T T::operator /(const T2 &b) const;	T operator /(const T &a, const T2 &b);
나머지	    a % b	        O	T T::operator %(const T2 &b) const;	T operator %(const T &a, const T2 &b);
비트 NOT	~a	            O	T T::operator ~() const;	        T operator ~(const T &a);
비트 AND	a & b	        O	T T::operator &(const T2 &b) const;	T operator &(const T &a, const T2 &b);
비트 OR	    a | b	        O	T T::operator |(const T2 &b) const;	T operator |(const T &a, const T2 &b);
비트 XOR	a ^ b	        O	T T::operator ^(const T2 &b) const;	T operator ^(const T &a, const T2 &b);
비트 Left Shift	a << b	    O	T T::operator <<(const T2 &b) const;T operator <<(const T &a, const T2 &b);
비트 Right Shift	a >> b	O	T T::operator >>(const T2 &b) const;T operator >>(const T &a, const T2 &b);
*/

/* 비트 쉬프트 연산자 bit shift operator */
/* << operator */
char ch = 0x20;         // 0010 0000는 십진수 32
EXPECT_TRUE(ch == 32);

ch = ch << 1;           // 0100 0000는 십진수 64.  << 1은 곱하기 2의 효과
EXPECT_TRUE(ch == 64);

ch = ch << 1;           // 1000 0000는 십진수 -128.
EXPECT_TRUE(ch == -128);

ch = ch << 1;           // 0000 0000은 0. 부호 비트를 이동시키면 결과가 정의되지 않았으나, 대부분 0으로 채웁니다.
EXPECT_TRUE(ch == 0);

/* simliar for >> operator */

/* 접근 연산자 */
/*  
 항목	        내용	연산자 오버로딩	    개체 멤버 정의	                         개체 비멤버 정의
=====================================================================================================    
배열 요소       a[b]        o             R& T::operator [](S b);                       x   
                                        cosnt R& T::operator [](S b) const;

포인터 실제값     *a        o            R& T::operator *();                       R& operator *(T a);
                                  const R& T::operator *() const;   
~~~

*/

/* 함수 호출 연산자 */
class T {
public:
    int operator ()(int a, int b) const { return a + b; }
};

T t;
EXPECT_TRUE(t(10, 20) == 30);               // operator() 호출
EXPECT_TRUE(t.operator()(10, 20) == 30);    // t(10, 20) 호출과 동일. operator()를 명시적으로 호출


/* 콤마 연산자 */
class T {
public: 
  static int f(int val) { return val; }
};

int arr[] = { 1, 2, 3 };
int i = 0;

// 1 를 증가시키고, arr의 i 항목을 f dp 전달합니다.
// (~) 비권장. 분석하기 복잡합니다.
EXPECT_TRUE(T::f((++i, arr[i])) == 2);

/* 조건 연산자 */
int result = true ? 10 : 20;
EXPECT_TRUE(result == 10);

/*    생성/소멸 연산자    */
// 개체 생성시 사용하는 new는 하기 단계를 수행합니다.
// 1. 전역 operator new(std::size_t)로 메모리 공간 할당
// 2. 구조체이거나 클래스이면 위치 지정 생성 (Placement New) 인 operator new (size_t, void*) 를 실행하여 생성자 호출
// 3. 메로리 주소를 해당 타입으로 형변환하여 리턴
// 즉 new는
// * operator new: C 언어의 malloc()과 유사
// * 위치 지정 생성 (Placement New) : 생성자 호출

short i;
int arr[10];
class  T {
  int m_Val;
};
struct S {
  int x;
  int y;
};
S s;
S& ref = s; // ref는 s의 참조자

EXPECT_TRUE(sizeof(i) == 2);                  // short 는 2byte
EXPECT_TRUE(sizeof(arr) == sizeof(int) * 10); // 배열은 요소의 전체 크기
EXPECT_TRUE(sizeof(T) = sizeof(int) * 1);     // 클래스와 구조체는 멤버 변수들의 합
EXPECT_TRUE(sizeof(S) = sizeof(int) * 2);
EXPECT_TRUE(sizeof(s) == sizeof(ref));        // 참조자의 크기는 참조하는 개체의 크기와 동일

// 가상 함수 없음
class Base1 {};
class Derived1 : public Base1 {};

// 가상 함수 있음
class Base2 {
public:
  virtual void f() {}
};
class Derived2 : public Base2 {};

// Base1과 개체 b1은 이름이 동일합니다.
{
  Base1 b1;
  const std::type_info& ti1 = typeid(Base1);
  const std::type_info& ti2 = typeid(b1);
  EXPECT_TRUE(ti1 == ti2);
  EXPECT_TRUE(ti1.name() == ti2.name());
}
// 가상 합수가 없는 경우의 참조 - 참조 대상이 Derived1 이지만, 정의한 Base1 타입으로 변경됨
{
  Derived1 d1;
  Base1& b1Ref = d1;  // 가상 함수 없음

  // b1Ref = d1으로 bRef는 Base1 타입이 됨
  EXPECT_TRUE(typeid(b1Ref).name() == typeid(Base1).name());
}
// 가상 함수가 있는 경우의 참조 - 참조 대상인 Derived2 타입으로 유지됨
{
  Derived2 d2;
  Base2& b2Ref = d2;  // 가상 함수 있음

  // b2Ref = d2로 b2Ref는 다형적 동작하며, 여전히 Derived2 타입임. (원래 개체의 타입 정보)
  EXPECT_TRUE(typeid(b2Ref).name() == typeid(Derived2).name());
}
// before()를 이용한 대소 비교
{
  Derived2 d1, d2;
  Base2& b1 = d1;
  Base2& b2 = d2;

  const std::type_info& ti1 = typeid(b1);
  const std::type_info& ti2 = typeid(b2);
  EXPECT_TRUE(ti1.before(ti2) == false) // 모두 Derived2 여서 ti1 < ti2는 false 입니다
  EXPECT_TRUE(ti2.before(ti1) == false); // 모두 Derived2여서 ti2 > ti1는 false입니다.          
}

/*   연산자 오버로딩   */ 
// 클래스나 구조체에서 캡슐화를 위해 연산자를 오버로딩 할수 있습니다.
// 복사 대입 연산자 (=)
//    이는 T& t1 = t2 = t3;과 같이 연달아 대입하는 경우를 지원하고, 복사 부하를 줄이기 위함입니다.
//    예외에 안전할수 있도록 보증하는 방법은 swap을 이용한 예외 보증 복사 대입 연산자를 참고하세요.
class T {
private: 
  int m_X;
  int m_Y;
public:
  T& operator =(const T& other) {
    this->m_X = other.m_X;
    this->m_Y = other.m_Y;
    return *this;   // 자기 자신을 리턴합니다.
  }
};
T t1, t2, t3;
t1 = t2 = t3;   // t2 = t3의 결과 t2의 참조자를 리턴하고, t1에 대입합니다.


/*    += 연산자     */
class T {
private:
  int m_Val;
public:
  explicit T(int val) : m_Val(val) {}
  int GetVal() const { return m_Val; }

  // 같은 T타입인 경우
  T& operator +=(const T& other) {
    this->m_Val += other.m_Val;
    return *this;   // 자기 자신을 리턴합니다.
  }

  // int 형도 지원
  T& operator +=(int val) {
    this->m_Val += val;
    return *this;   // 자기 자신을 리턴합니다.
  }
};

T t1(10), t2(20);
t1 += t2;     // operator +=(const T& other) 호출
EXPECT_TRUE(t1.GetVal() == 30);

t1 += 10;     // operator += (int val) 호출
EXPECT_TRUE(t1.GetVal() == 40);


class T {
private:
  int m_Val;
public:
  explicit T(int val) : m_Val(val) {}
  int GetVal() const { return m_Val; }

  // 같은 T타입인 경우
  T operator +(const T& other) {
    return T(this->m_Val + other.m_Val);  // 새로운 개체를 리턴합니다.
  }

  // int 형도 지원
  T operator +(int val) {
    return T(this->m_Val + val);          // 새로운 개체를 리턴합니다.
  }
};

T t1(10), t2(20);
T t3(0);
t3 = t1 + t2;   // operator +(const T& other) 호출
EXPECT_TRUE(t1.GetVal() == 10); 
EXPECT_TRUE(t3.GetVal() == 30); 

t3 = t1 + 10;// operator +(int val) 호출
EXPECT_TRUE(t1.GetVal() == 10); 
EXPECT_TRUE(t3.GetVal() == 20); 

/*    + 보다는 += 이 좋은이유     */
// 산술형 대입 연산자가 참조자 형식 (T&)를 리턴하는데 반해, 이항 산술 연산의 경우 개체 형식(T, 값 타입)을 리턴하는 데요,
//    이는 연산의 결과값을 저장할 임시 개체가 있어야 하기 때문입니다.

T t1(10);
T t2(20);

// (~) 비권장. 임시 개체가 생성됨
T t3 = t1 + t2;   // t1 + t2 인 임시 개체를 생성. t3의 복사 생성자 호출하여 임시 개체 대입

// (0) 권장. 임시 개체가 생성되지 않음
T t3 = t1;    // t3의 복사 생성자를 호출하여 t1값 대입
t3 += t2;     // t3에 t2값 증가

/*    + 연산자 비멤버 버전    */
// + 연산시 int 형을 먼저 작성하면 컴파일 되지 않습니다.
// t3 = 10 + t1; 은 사실 10.operator +(T other) 호출하는 것과 같기 때문입니다.
// int 형인 10 에는 해당 함수가 없으므로 컴파일 오류가 납니다.
T t1(10);
T t2(0);
T t3(0);

t2 = t1 + 10;   // t1.operator +(int val) 호출
t2 = t1.operator +(10); // t2 = t1 + 10과 동일

t3 = 10 + t1; // (x)   10.operator +(T other) 호출합니다. int 형인 10에는 해당 oeprator 가 없습니다.
EXPECT_TRUE(t2.GetVal() == 20 && t3.GetVal() == 20);

// T t = 10 + other; 지원
inline T operator +(int left, const T& right) {
  T result(left + right.GetVal());
  return result;
}

class T {
private: 
  int m_Val;

public:
  explicit T(int val) : m_Val(val) {}
  int GetVal() const {return m_Val;}

  // 전위형
  T& operator ++() {
    ++m_Val;
    return *this;   // 자기 자신을 리턴합니다.
  }

  // 후위형. 인자 int 는 전위형과 구분하기 위한 더미 입니다
  const T operator ++(int) {    
    // t++++가 안되도록 const T를 리턴합니다
    T result = *this; // 복제합니다
    ++m_val;          // this의 값을 증가시킵니다.
    return result;    // 증가시키기 전에 복제한 값을 리턴합니다.
  }
};

T t(10);
T t1 = ++t;
EXPECT_TRUE(t1.GetVal() == 11); // 증가시킨 후 값
EXPECT_TRUE(t.GetVal() == 11);

T t2 = t++; 
EXPECT_TRUE(t2.GetVal() == 11); // (△) 비권장. 의도한 것인지 조금 헷갈립니다. 증가시킨 전 값. 
EXPECT_TRUE(t.GetVal() == 12);


class T {
private:  
  int m_Val;
public:
  explicit T(int val) : m_Val(val) {}
  int GetVal() const { return m_Val; }

  bool operator <(const T& other) const {
    return this->m_Val < other.m_Val;
  }

  bool operator ==(const T& other) const {
    return m_Val == other.m_Val;    // < 로부터 구현하면 !(*this < other || other < *this)로 할수 있습니다. 단 < 을 2회 하므로 비효율적입니다. 
  }
  
  bool operator !=(const T& other) const {
    return !(*this == other);
  }

  bool operator >(const T& other) const {
    return other < *this;
  }

  bool operator <=(const T& other) const {
    return !(other < *this);
  }

  bool operator >=(const T& other) const {
    return !(*this < other);
  }
};

T t1(10);
T t2(10);
EXPECT_TRUE(t1 == t2);

T t1(10);
T t2(20);
EXPECT_TRUE(t1 != t2);

T t1(10);
T t2(20);
EXPECT_TRUE(t1 < t2);

T t1(20);
T t2(10);
EXPECT_TRUE(t1 > t2);

T t1(10);
T t2(20);
EXPECT_TRUE(t1 <= t2);

T t1(10);
T t2(10);
EXPECT_TRUE(t1 <= t2);

T t1(20);
T t2(10);
EXPECT_TRUE(t1 >= t2);

class T {
private:
    int m_Val;
public:
    explicit T(int val) : m_Val(val) {}
    int GetVal() const {return m_Val;}

    bool operator <(const T& other) const {
        return this->m_Val < other.m_Val;
    } 

    bool operator ==(const T& other) const {
        return m_Val == other.m_Val; // < 로부터 구현하면, !(*this < other || other < *this)로 할 수 있습니다. 단 < 을 2회 하므로 비효율적입니다.
    }
    bool operator !=(const T& other) const {
        return !(*this == other);
    }
    bool operator >(const T& other) const {
        return other < *this;
    }
    bool operator <=(const T& other) const {
        return !(other < *this);
    }
    bool operator >=(const T& other) const {
        return !(*this < other);
    }
};

T t1(10);
T t2(10);
EXPECT_TRUE(t1 == t2);

T t1(10);
T t2(20);   
EXPECT_TRUE(t1 != t2);

T t1(10);
T t2(20);  
EXPECT_TRUE(t1 < t2); 

T t1(20);
T t2(10);  
EXPECT_TRUE(t1 > t2);  

T t1(10);
T t2(20); 
EXPECT_TRUE(t1 <= t2);

T t1(10);
T t2(10);
EXPECT_TRUE(t1 <= t2);

T t1(20);
T t2(10); 
EXPECT_TRUE(t1 >= t2);

T t1(10);
T t2(10); 
EXPECT_TRUE(t1 >= t2);   

/*   enum 열거형 연산자 오버로딩    */
class Week {
public: 
  enum Val {
    Sunday, Monday, Tuesday, Wednesday,
      Thursday, Friday, Saturday
  };
};
// 전위 증가
Week::Val& operator ++(Week::Val& d) {
  return d = (Week::Saturday == d) ? Week::Sunday : static_cast<Week::Val>(d + 1);
}

Week::Val val = Week::Saturday;

EXPECT_TRUE(++val == Week::Sunday);   // 토요일 에서 1 증가하면, 제일 처음 값인 일요일로 순화됨
EXPECT_TRUE(++val == Week::Monday);   // 일요일 에서 1 증가하면 월요일