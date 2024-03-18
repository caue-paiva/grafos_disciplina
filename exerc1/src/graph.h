#ifndef GRAFO_LA_H
   #define GRAFO_LA_H

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
    #define VERTEX_LIST_CHUNK 20 //define de quantos em quantos vertices vamos alocar para a lista de vertices

    typedef struct graph Graph;

    Graph* graph_create();  //cria um grafo vazio
    void remove_graph(Graph** graph); //destroi o grafo e libera a memoria
    bool add_vertex(const int vertex_num, Graph* graph); //add um vertice no grafo

    bool exist_edge(const int vertex1 , const int vertex2, const Graph* graph); //verifica se uma aresta existe
    bool add_edge(const int vertex1, const int vertex2, const int weight ,Graph* graph); //add uma aresta entre 2 vertices
    bool remove_edge(const int vertex1, const int vertex2, Graph* graph); //remove uma aresta entre 2 vertices
    bool remove_edge_smallest_weight(Graph* graph);  //remove a aresta com menor peso no grafo
    
    int* get_adj_vertex(const int vertex, const Graph* graph, int* get_list_size); //retorna uma lista de vertices adjancentes a um vertice
    void print_adj_vertex(const int vertex, const Graph*graph); //printa a lista da funcao acima
    
    void print_info(const Graph* graph); //imprime no terminal um desenho da matriz de adjancencia do grafo
   
    int number_of_vertexes(const Graph* graph); //retorna numero de vertices
    int number_of_edges(const Graph* graph); //retorna numero de arestas
   
    int* get_vertex_list(const Graph* graph, int* get_list_size); //retorna uma lista de vertices no grafo
    void print_vertex_list(const Graph* graph); //imprime lista acima

    int** adjacency_matrix(const Graph* graph); //retorna a matriz de adjacencia (uma copia com memoria alocada)
    

#endif