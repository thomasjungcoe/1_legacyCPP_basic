/**
 *                Array
 *     If speed isn't the top priority, vector could be used for easier
 *          maintainability as well as scalablity 
 *          It also supports dynamic creation and fast access timing
 * 
 *      new[] - delete[] pair 
 * 
 *      Modern C++:
 *      -----------
 *      C++11 -> array was added to mimic the C-style consecutive array container
 *      
 *      
 *      int arr[5];
 *      int* p = new int[5];
 *      delete[] p;
 *      int arr[3] = {1, 2, 3};,
 *      char str[] = "abc";
 *      int arr[] = {1, 2, 3}; 
 * */

#include <string.h>
void main(void) {

    int arr[3];
    EXPECT_TRUE(sizeof(arr) / sizeof(int) == 3);


    int arr1[3];          // not recomended because not initialized
    // int arr1[];        // (x) compile error due to no size
    // int arr1[] = {};   // (x) compile error due to no size && empty {}
    int arr2[] = {0, 1, 2}; // (0) <- 3 
    int arr3[3] = {};       // (0) <- 3
    int arr4[3] = {0, 1, 2};// (0) <- stuffs in {} has to be equal or less than [3]

    EXPECT_TRUE(arr2[2] = 2);
    EXPECT_TRUE(arr3[0] == 0 && arr3[1] == 0 && arr3[2] == 0);
    EXPECT_TRUE(arr4[2] == 0);

    char str1[] = "abc"; // (0) {'a', 'b', 'c', '\0'}
    EXPECT_TRUE(str1[0] == 'a');
    EXPECT_TRUE(str1[1] == 'b');
    EXPECT_TRUE(str1[2] == 'c');
    EXPECT_TRUE(str1[3] == '\0');   // added Null
    EXPECT_TRUE(sizeof(str1) / sizeof(char) == 4);  // size is 4 including NULL
    EXPECT_TRUE(strlen(str1) == 3);        // string length is 3 

    wchar_t str2[] = L"abc";    // (0) {L'a', L'b', L'c', L'\0'};
    EXPECT_TRUE(str2[0] == L'a');
    EXPECT_TRUE(str2[1] == L'b');
    EXPECT_TRUE(str2[2] == L'c');
    EXPECT_TRUE(str2[3] == L'\0');      // NULL added
    EXPECT_TRUE(sizeof(str2) / sizeof(wchar_t) == 4);   // array size of 4
    EXPECT_TRUE(wcslen(str2) == 3);                  // string length is 3


    int arr1[] = {1, 2, 3};

    // int arr2[] = arr1;   // (x) compile error <-- can't assign another array
    int arr2[3];
    for (int i = 0; i < sizeof(arr1) / sizeof(int); ++i) {  
        arr2[i] = arr1[i];
    }
    EXPECT_TRUE(arr2[0] == 1 && arr2[1] == 2 && arr2[2] == 3);

    int* ptr = arr1;        // ptr referencing the array

    ptr[1] = 20;
    EXPECT_TRUE(arr1[1] == 20);

    /**
     *                          vector
     *   arr                    vector
     * int a[5]             vector<int> v(5);
     * int a[5] = {};             X (don't have)
     * a[0]                      v[0]
     * &a[0]                     &v[0]
     * 
     */

    typedef int MyArray[5];
    MyArray arr;        // equivalent to int ar[5]
    arr[0] = 10;        
    EXPECT_TRUE(arr[0] == 10);

    int* p = new int[5];        // int[5] array creation
    delete[] p;                 // destruction, not delete p; <-- only deletes once instead of all the indexes of the array
}

