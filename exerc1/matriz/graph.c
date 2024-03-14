#include "graph.h"



struct graph {
   int** matrix;
   int* vertex_list;
   int vertex_num;
   int edge_num;
};

//funcoes internas


//dado um vertice com numero x, ele acha a posicao na lista de vertices (e então a linha/coluna da matriz correspodente)
//Pode ser vista com uma funcao de hash:  f(vertice_num) -> index da lista/matriz
int __find_vertex_index(const int vertex_num, const Graph* graph){
   assert(graph);
 
   int* vertex_list = graph->vertex_list;
   int num_of_vertex = graph->vertex_num;

   if(graph->matrix == NULL || vertex_list == NULL){
      return -1;
   }

   for (int i = 0; i < num_of_vertex; i++){
       if (vertex_list[i] == vertex_num)
           return i;
   }

   return -1;
}

int** __realloc_matrix(const int new_size,const int old_size, int**old_matrix) {

      if (old_matrix == NULL) { //criar a matrix pela primeira vez
         int** matrix = (int**) malloc(sizeof(int*) *new_size);
         assert(matrix);

         for (int i = 0 ; i < new_size; i++){
            matrix[i] = (int*) malloc( new_size * sizeof(int)); //calloc inicia todos os valores pra 0
            assert(matrix[i]);

            for (int j = 0; j < new_size; j++){
               matrix[i][j] = NO_EDGE; //inicializa a matrix com todas as arestas como inexistentes
            }
         }   
         return matrix;
      }

      int** matrix = (int**) malloc(sizeof(int*) *new_size);
      assert(matrix);

      for (int i = 0 ; i < new_size; i++){ //andar verticalmente

            matrix[i] = (int*) malloc(new_size * sizeof(int)); 
            assert(matrix[i]);

            if (i < old_size) {
               for (int j = 0; j < old_size; j++){
                   matrix[i][j] = old_matrix[i][j];
               }
               for (int k = old_size; k < new_size; k++){
                    matrix[i][k] = NO_EDGE;
               }
            }else{
               for (int j = 0; j < new_size; j++){
                  matrix[i][j] = NO_EDGE; //inicializa a matrix com todas as arestas como inexistentes
               }
            }
      }   
      return matrix;
}

void __dealloc_matrix(const int size, int**matrix){
   for (int i = 0; i < size; i++){
       free(matrix[i]);
       matrix[i] = NULL; 
   }

   free(matrix);
   matrix=NULL;
}


//funcoes externas
Graph* graph_create(){
   
   Graph* graph = (Graph*) malloc(sizeof(Graph));
   assert(graph);

   graph->vertex_num = 0;
   graph->edge_num = 0;

   graph->matrix = NULL;
   
   int* vertex_list = (int*) malloc(sizeof(int) * VERTEX_LIST_CHUNK); //alocando uma lista de inteiros para guardar os vertices em ordem
   assert(vertex_list);
   graph->vertex_list  = vertex_list;
   
   return graph;
}

void remove_graph(Graph** graph){
     assert_2ptrs(graph,*graph);

     __dealloc_matrix((*graph)->vertex_num, (*graph)->matrix);
     (*graph)->matrix = NULL;

     free((*graph)->vertex_list);
     (*graph)->vertex_list = NULL;
     free(*graph);
     *graph = NULL;
}

bool add_vertex(const int num_vertice, Graph* graph){
   assert(graph);
   
   int num_vertices_antigo = graph->vertex_num;
    int** matriz_antiga = graph->matrix; 

   graph->matrix = __realloc_matrix(num_vertices_antigo+1,num_vertices_antigo, matriz_antiga);
   
   __dealloc_matrix(num_vertices_antigo, matriz_antiga);
   matriz_antiga = NULL;

   graph->vertex_num += 1;

   if ((graph->vertex_num % VERTEX_LIST_CHUNK) == 0) { //estamos no limite da capacidade do array de vertices
       d_printf("realloc");
       int old_size = sizeof(graph->vertex_list)/sizeof(int);
       int* new_array = (int*) realloc(graph->vertex_list, old_size + VERTEX_LIST_CHUNK);
       assert(new_array);
       graph->vertex_list = new_array;
   }

   graph->vertex_list[graph->vertex_num -1] = num_vertice;
   return graph;
}

//funcoes lidando com conexoes/arestas

bool exist_edge(const int vertex1 , const int vertex2, const Graph* graph){
     assert(graph);
     if (vertex1 == vertex2)
        err_exit("Os 2 vertices nao podem ser iguais, vertice1: %d , vertice2: %d", vertex1, vertex2);

     int ver1_matrix_posi = __find_vertex_index(vertex1,graph);
     int ver2_matrix_posi = __find_vertex_index(vertex2,graph);
     if (ver1_matrix_posi == -1 || ver2_matrix_posi == -1){
         warn_printf("nao voi possivel achar o vertice 1 ou vertice 2");
         return false;
     }
    

     int edge = graph->matrix[ver1_matrix_posi][ver2_matrix_posi];

     if(edge != NO_EDGE)
        return true;
     else
        return false;  
}

bool add_edge(const int vertex1, const int vertex2, const int weight ,Graph* graph){
     assert(graph);
     if (vertex1 == vertex2)
       err_exit("Os 2 vertices nao podem ser iguais, vertice1: %d , vertice2: %d", vertex1, vertex2);

     int new_edge_flag = 1;

     int ver1_matrix_posi = __find_vertex_index(vertex1,graph); //achar a posicao na matrix correspondente dos vertices
     int ver2_matrix_posi = __find_vertex_index(vertex2,graph);
     if (ver1_matrix_posi == -1 || ver2_matrix_posi == -1){
         warn_printf("nao voi possivel achar o vertice 1 ou vertice 2");
         return false;
     }

     if (graph->matrix[ver1_matrix_posi][ver2_matrix_posi] != NO_EDGE)
         new_edge_flag = 0;
     

     graph->matrix[ver1_matrix_posi][ver2_matrix_posi] = weight; //no caso de dígrafos, as conexões são simétricas
     graph->matrix[ver2_matrix_posi][ver1_matrix_posi] = weight;
     
     graph->edge_num += new_edge_flag; //arestas bi-direcionais
     return true;
}

bool remove_edge(const int vertex1, const int vertex2, Graph* graph){
     assert(graph);
     if (vertex1 == vertex2)
        err_exit("Os 2 vertices nao podem ser iguais, vertice1: %d , vertice2: %d", vertex1, vertex2);

     int ver1_matrix_posi = __find_vertex_index(vertex1,graph); //achar a posicao na matrix correspondente dos vertices
     int ver2_matrix_posi = __find_vertex_index(vertex2,graph);
     if (ver1_matrix_posi == -1 || ver2_matrix_posi == -1){
         warn_printf("nao voi possivel achar o vertice 1 ou vertice 2");
         return false;
     }

     if(graph->matrix[ver1_matrix_posi][ver2_matrix_posi] == NO_EDGE) //conexao não existe
        return false;
     
     graph->matrix[ver1_matrix_posi][ver2_matrix_posi] = NO_EDGE; //no caso de dígrafos, as conexões são simétricas
     graph->matrix[ver2_matrix_posi][ver1_matrix_posi] = NO_EDGE;

     graph->edge_num -= 1; //arestas bi-direcionais

     return true;
}

bool remove_edge_smallest_weight(Graph* graph){
   assert_2ptrs(graph,graph->matrix);

   const int vertex_num = graph->vertex_num;
   int smallest_i, smallest_j = -1;
   smallest_i = -1;

   int smallest_weight = 100000000;
   for (int i = 0; i < vertex_num; i++){
          for (int j = 0; j < vertex_num; j++){
               if (graph->matrix[i][j] != -1 && graph->matrix[i][j] < smallest_weight){
                   smallest_weight = graph->matrix[i][j];
                   smallest_i = i;
                   smallest_j = j;
               }
          } 
   }

   if (smallest_i == -1) //não achou nenhuma aresta no grafo
      return false;

   graph->matrix[smallest_i][smallest_j] = NO_EDGE;
   graph->matrix[smallest_j][smallest_i] = NO_EDGE;
   graph->edge_num -= 1;

   return true;

}

//funcoes de input pro user

//get_list_size é uma variavel para guardar o tamanho da lista de retorno em um inteiro
int* get_adj_vertex(const int vertex, const Graph* graph, int* get_list_size) {
     assert_2ptrs(graph,get_list_size);

     const int vertex_num = graph->vertex_num;
     int arr_arestas[vertex_num]; //vamos declarar um array temporario na stack para guardar a lista de tam maximo vertex_num

     int ver_matrix_posi = __find_vertex_index(vertex,graph);
     assert(ver_matrix_posi != -1); //caso o vertice nao existe gera um erro
     
     int aresta;
     int numero_aresta = 0;
     for (int i = 0; i < vertex_num; i++){
         aresta = graph->matrix[ver_matrix_posi][i];

         if (aresta != NO_EDGE){
            int connected_vertex = graph->vertex_list[i];
            arr_arestas[numero_aresta] = connected_vertex;
            numero_aresta +=1;
         }
     }

     //vamos alocar memoria na heap para a lista final, nesse caso vamos alocar apenas memoria suficiente para as arestas existentes e não para o vertex_num (maximo)
     if (numero_aresta == 0){
         warn_printf("Nao existem arestas conectadas a esse vertice, retornado um ponteiro NULL");
         return NULL;
     }
   
     int* arestas_adja = (int*) malloc(sizeof(int) * numero_aresta);
     assert(arestas_adja);

     for (int i = 0; i < numero_aresta; i++){
         arestas_adja[i] = arr_arestas[i];
     }

     *get_list_size = numero_aresta;

     return arestas_adja;
}

void print_adj_vertex(const int vertex, const Graph*graph){
     assert(graph);
     int size;

     int* list = get_adj_vertex(vertex,graph,&size);
     if (list == NULL)
         return;

     for (int i = 0; i < size; i++){
          printf("%d ", list[i]);
     }
     printf("\n");
}

void print_info(const Graph* graph){
    assert(graph);
    if(graph->vertex_num== 0)
       return;

    int vertex_num = graph->vertex_num;
    int* vertex_list = graph->vertex_list;
    printf("\n     "); 
    for (int i = 0; i < vertex_num; i++){
      printf("%d  ",vertex_list[i]);
    }
    printf("\n     ");
    for (int i = 0; i < vertex_num; i++){
      printf("---");
    }
    printf("\n");


    for (int i = 0; i < vertex_num; i++){
      printf("%d: [ ",vertex_list[i]); 
      for (int j = 0; j < vertex_num; j++){
         int num = graph->matrix[i][j];
         if (num == -1) //para formatar melhor
            printf("%d ", graph->matrix[i][j]);
         else
            printf(" %d ", graph->matrix[i][j]);
      }
      printf("]\n");
      
    }
}

int number_of_vertexes(const Graph* graph){
    assert(graph);
    return graph->vertex_num;
}

int number_of_edges(const Graph* graph){
    assert(graph);
    return graph->edge_num;
}

//get_list_size é uma variavel para guardar o tamanho da lista de retorno em um inteiro
int* get_vertex_list(const Graph* graph, int* get_list_size){
     assert_2ptrs(graph,get_list_size);

     if (graph->vertex_list == NULL){
        warn_printf("Lista de vertices vazia, retornando null");
        return NULL;
     }
     
     int num_vertex = graph->vertex_num;
     *get_list_size = num_vertex; //coloca o tamanho da lista na variavel apontada por esse ponteiro

     int* return_list = (int*)  malloc(sizeof(int) * num_vertex);
     assert(return_list);

     for (int i = 0; i < num_vertex; i++){
        return_list[i] = graph->vertex_list[i];
     }

     return return_list;
}

void print_vertex_list(const Graph* graph){
   assert(graph);

   int vertex_num;
   int* vertex_list = get_vertex_list(graph,&vertex_num);
   if (vertex_list == NULL)
      return;

   printf("Lista de vertices:  ");
  
   for (int i = 0; i < vertex_num; i++){
      printf("%d ", vertex_list[i]);
   }

   printf("\n");
}

int** adjacency_matrix(const Graph* graph){
     assert(graph);

     int** return_ma = __realloc_matrix(graph->vertex_num,graph->vertex_num,graph->matrix);
     assert(return_ma);

     return return_ma;
}

int main(){

   Graph* g1 = graph_create();
   add_vertex(5,g1);
   add_vertex(6,g1);
   add_vertex(7,g1);
   add_vertex(8,g1);

 
   add_edge(5,6,7,g1);
   add_edge(5,7,7,g1);


   print_info(g1);

   int ** matrix = adjacency_matrix(g1);
   remove_edge_smallest_weight(g1);

   print_info(g1);


   
   
   


   
       


}

