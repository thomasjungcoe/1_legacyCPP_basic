/**
 *          TYPES 
 *  don' get attached on the size of the type as it can vary among OS, compilers, system bits
 *  C++11~ auto & decltype() was added to assume type based on value
 *  C++11~ using was added to make it more verbose than using typedef
 *  C++11~ long long was added to garantee at least 8 byte size
 *  C++11~ char16_t, char32_t type was added to support UTF-16 & UTF-32 encoding
 *  C++20~ char8_t was added to support UTF-8
 *  C++20~ 정수(integer)에서 2의 보수 범위를 보장합니다.
 *  항목        	내용
    1의 보수	1byte로 -127 ~ 127 표현
    2의 보수	1byte로 -128 ~ 127 표현
 */

using namespace std;

typedef unsigned long ulong;
ulong myVal; // type's alias

// arrays
typedef int myArray[5];
MyArray arr;    // equivalent to int arr[5];
arr[0] = 10     // inserting 10 to the first idx
EXPECT_TRUE(arr[0] == 10);

// structs
typedef struct {int a; int b;} myData, *pMyData;
MyData myData1;
MyData* myData2;
pMyData myData3;    // same as MyData*
myData1.a = 10;
EXPECT_TRUE(myData1.a == 10);

// function pointer
typedef int (*Func)(int, int);      // function pointer typedef

int f(int a, int b) {return a + b;} // definition of the function
Func func = f;                      // saving the function pointer


// template type redefinition
template <class T>
struct ClassT {
    typedef T Type;
    typedef const T ConstType;
};
ClassT<int>::ConstType constVal = 20;


/* sizeof() - allows us to classify the size of the object in byte size */
class MyClass {
    int m_X;
    int m_Y;
};

MyClass myClass;
MyClass& myClassRef = myClass;

EXPECT_TRUE(sizeof(myClass) == 8);
EXPECT_TRUE(sizeof(myClass) == sizeof(myClassRef)); // return size of sizeof class and ref of the class are equal


/*       max value of the type          */
EXPECT_TRUE(std::numeric_limits<int>::max() = 2147483647);
EXPECT_TRUE(std::numeric_limits<int>::min() = -2147483648);