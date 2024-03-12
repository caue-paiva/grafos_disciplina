#ifndef GRAFO_LA
   #define GRAFO_LA

   #include "stdio.h"
   #include "stdlib.h"
   #include "assert.h"
   #include "stdbool.h"

    #define assert_2ptrs(p1,p2) assert(p1); assert(p2);
    #define assert_3ptrs(p1,p2,p3) assert_2ptrs(p1,p2); assert(p3);

    //simple max and min macro
    #define max(x, y)  ((x) > (y) ? (x) : (y))

    #define min(x, y)  ((x) > (y) ? (y) : (x))

    //frees the pointer pointed by the double pointer and sets it to NULL, this CAN be used on a ptr passed to a func
    #define safe_free_double(double_ptr) do {\
      free(*(double_ptr));\
      *(double_ptr) = NULL;\
    } while(0)
    
    //frees a pointer and sets it to NULL, this CANT be used on a ptr passed to a func
    #define safe_free(ptr) do {\
      free((ptr));\
      (ptr) = NULL;\
    } while(0)
    
    // if a function  returns -1, this raises an error and prints the errno messages, this is useful for stdlib functions that change
    // errno val
    #define errno_check(X) do {\
        if ((X) == -1) {\
            printf("ERROR: (VAR NAME: %s , FILE: %s , LINE: %d) -- Error name: %s \n", #X ,__FILE__,__LINE__, strerror(errno));\
            exit(1);\
        }\
        } while (0)
        //strerror comes from string.h and prints the messages from the errno error


    //nullptr and errno check macro
    #define null_errno_check(ptr) do {\
        void* __null_errno_ptr = (ptr);\
        if((__null_errno_ptr) == NULL){\
           printf("NULL PTR ERROR: (VAR NAME: %s , FILE: %s , LINE: %d) -- Error name: %s \n", #ptr ,__FILE__,__LINE__, strerror(errno));\
           exit(1);\
        }\
    } while(0)

    #define err_exit(...) do {\
            printf("[ERROR] (FILE: %s , LINE: %d) -- ",__FILE__,__LINE__);\
            printf(__VA_ARGS__);\
            printf("\nExit(1)\n");\
            exit(1);\
    } while(0)
    //used to check for null ptrs and displaying errno messages, useful for file opening routines


    //get the size of an array
    #define arr_size(arr) (sizeof( (arr) ) / sizeof((arr)[0]))


    // debug macros
    #define DEBUG 1 //debug or not flag
    #if DEBUG //printf with more debug info
        #define d_printf(...) do {\
            printf("[DEBUG] (FILE: %s , LINE: %d) -- ",__FILE__,__LINE__);\
            printf(__VA_ARGS__);\
            printf("\n");\
        } while(0)
    #else    //does not print anything
        #define d_printf(...) (void)0
    #endif  

    //single line debug printf macro, its reliant on a GCC ##__VA_ARGS__ variable so it might be less portable, it can also work if d_printf is called with no args
    //#define d_printf2(format, ...) printf("[DEBUG] (FILE: %s , LINE: %d) -- " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)



    //ATTENTION: warning arg needs to be a string
    #define warn_printf(warning) printf("[WARNING] %s (FILE: %s , LINE: %d) -- \n", (warning) ,__FILE__,__LINE__);\

    typedef unsigned int uint;


#endif