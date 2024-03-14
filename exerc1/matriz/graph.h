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

    typedef struct graph Graph;

    Graph* graph_create();
    void graph_destroy(Graph** graph);
    bool add_vertex(const int num_vertice, Graph* graph);
    
    bool exist_edge(const int vertex1 , const int vertex2, const Graph* graph);
    bool add_edge(const int vertex1, const int vertex2, const int weight ,Graph* graph);
    bool remove_edge(const int vertex1, const int vertex2, Graph* graph);
    bool remove_edge_smallest_weight(Graph* graph);  //ainda precisa implementar essa funcao
    
    int* get_adj_vertex(const int vertex, const Graph* graph, int* get_list_size);
    void print_adj_vertex(const int vertex, const Graph*graph);
    
    void print_info(const Graph* graph);
   
    int number_of_vertexes(const Graph* graph);
    int number_of_edges(const Graph* graph);
   
    int* get_vertex_list(const Graph* graph, int* get_list_size);
    void print_vertex_list(const Graph* graph);
    
    // add as funcoes externas
   



#endif