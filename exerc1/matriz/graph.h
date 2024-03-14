#ifndef GRAFO_LA
   #define GRAFO_LA

    #include "stdio.h"
    #include "stdlib.h"
    #include "assert.h"
    #include "stdbool.h"

    //macros para null handling, debug e outras funcionalidades
    #define assert_2ptrs(p1,p2) assert(p1); assert(p2);
    #define assert_3ptrs(p1,p2,p3) assert_2ptrs(p1,p2); assert(p3);

    
    #define max(x, y)  ((x) > (y) ? (x) : (y))

    #define min(x, y)  ((x) > (y) ? (y) : (x))



    #define err_exit(...) do {\
            printf("[ERROR] (FILE: %s , LINE: %d) -- ",__FILE__,__LINE__);\
            printf(__VA_ARGS__);\
            printf("\nExit(1)\n");\
            exit(1);\
    } while(0)
   
    #define d_printf(...) do {\
            printf("[DEBUG] (FILE: %s , LINE: %d) -- ",__FILE__,__LINE__);\
            printf(__VA_ARGS__);\
            printf("\n");\
    } while(0)
   

    #define warn_printf(warning) printf("[WARNING] %s (FILE: %s , LINE: %d) -- \n", (warning) ,__FILE__,__LINE__);\


    #define NO_EDGE -1 //define para representar a não existencia de uma aresta na matriz de adjacencia com pesos
    #define VERTEX_LIST_CHUNK 2 //define de quantos em quantos vertices vamos alocar para a lista de vertices
   



#endif