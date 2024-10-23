/**
 * Memory Segment
 * ======================================================
 * 힙에 동적으로 메모리에 할당한 것은 명시적으로 소멸시켜라
 * 스택에 생성된 변수는 유효 범위가 종료되면 자동 소멸된다.
 */

// heap
int * p = new int;
// ...
delete p; // new로 생성한 것은 반드시 delete

// stack
int f1(int a) {
    int b = 10;
    return f2(a, b);
}

int f2(int a, int b) {
    int c = 20;
    return a + b + c;
}