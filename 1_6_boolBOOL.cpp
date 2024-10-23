/**
 * BOOL vs bool
 *  use bool over BOOL!
 *  C++17 -> depreciated the "bool"'s inc/dec calculation
 * 
 *  항목	BOOL	bool
    정의	Visual C++ typedef int BOOL;	C++ 표준 타입
    값  	#define TRUE  1,     
            #define FALSE 0	                true,
                                            false
    용량	sizeof(BOOL) == sizeof(int)	     1 <= sizeof(bool) <= sizeof(long)(Visual C++ 은 1byte)
 */

/* Refactoring the BOOL to bool
BOOL result = f();

bool result = f() ? true : false; // because BOOL is equivalent to byte (int), it's faster
                                  // but if the performance is that important, use assembly instead
                                  // bool only handles true/false so it's more trustworthy while
                                  // BOOL keeps integer value                                  
                                  // also better for readability on a more complex proj since bool only keeps true/false
*/