#ifndef GRAFO_LA
   #define GRAFO_LA

    #include "stdio.h"
    #include "stdlib.h"
    #include "assert.h"
    #include "stdbool.h"


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

    typedef unsigned int uint;


    /* Design do TAD:

    1) O user apenas vai ser exposto ao tad GrafosLA (grafos com lista de adjacencia)

    2) O TAD internamente é composto por nós (lista encad de arestas) e Nos headers (facilitam o acesso às conexoes), nenhum deles é exposto ao user
    
    3) Para o usuário o numero dos nos começa do 1, mas para lógica interna eles são guardado nos array indexado a partir do 0, então existe lógica
    interna para lidar com isso
    
    */

   #define NO_WGHT -1 // defincao de peso n existente


#endif