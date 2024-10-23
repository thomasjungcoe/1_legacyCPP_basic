/**
 * Pointer & Reference
 * ----------------------------------------------------
 * Use Ref over Pointers (no need for null check)
 * don't return ref to the local var (for they will be lost already)
 * 
 * Modern C++:
 *  C++11~ -> nullptr was added to ensure safer typing
 *  C++11~ -> 이동 연산을 위해 Right hand side (&&) was added to speed up temp obj insertion and calc
 * 
 *  Outline 
 * ---------
 * When the class is too big and return of that class is too heavy
 * When wanting to validate/change the data from the source
 * When wanting to pass a function as param
 * When wanting to utilize inheritance (use parent class -> child class)
 */

// Pointers obtain address value with & and actual value with *
//      depends on the system but 4 bytes or 8 bytes are used

int main(void) {
    int x = 20;
    int* p = &x;     // p references address of x
    *p = 30;        // address of p gets assigned with the value of 30
    EXPECT_TRUE(*p == 30 && x == 30);

    int y = 20;
    int& r = y;     // r is an alias of y
    r = 30;         // 
    EXPECT_TRUE(r == 30 && y == 30);


    
    /*   Null Pointer   */
    #define NULL 0
    // C++11~ nullptr was added to increase type safety

    /*   Safe Null Pointer  */
    // once created, always initialize
    // never null value
    // can't change to different ref

    int& r;         // (x) compile error. can't just contructor ref without a value. it can't just have trash value

    int x = 10;
    int y = 20;

    int& r = x;
    r = y;          // (0) r gets the value of y (not pointing y). r still points x
    y = 30;
    EXPECT_TRUE(x==20 && r==20 && y==30);   // change in value of y doesn' t effect r because r is pointing to x
}

/*   method that doesn't need null check    */
void f(int* p) {    // if a pointer was used as an argument 
    if (p == NULL) {
        // (~) <- not recomended bc what to do if p has NULL
    }
    *p = 20;
}

void f (int &r) {   // if a ref was used, no need to check the NULL
    r = 20;
}

/*      Dangling Pointer        */
int GetX() {
    // (x) compile warning. 
    int x = 10;
    return x;
}

// (x) 예외 발생. 이미 소멸된 지역 변수를 참조함
int& result = GetX();

// (~) not recomended
const int& result = GetX();

int* p = NULL;
int& r = *p;        // (x) malfunction can happen if you assign NULL value to the pointer 
r = 10;             // (x) exception 예외 발생 occurred

/*         Object Pointer           */
int obj = 10;
int* p1 = &obj;     // *p1 수정 가능. p1 수정가능
*p1 = 20;


