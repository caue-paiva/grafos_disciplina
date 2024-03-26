#include "bfs.h"


void bfs_tree_from_vertex(Graph* graph, const int start_vertex){
   assert(graph);

   int vertex_num; //pega o numero de vertices a lista de vertices do grafo
   int* vertex_list = get_vertex_list(graph,&vertex_num);
   assert(vertex_list); assert(vertex_num != 0);
   
   int root_index = -1; //acha o index na lista de vertices do vertice do comeco da funcao
   for (int i = 0; i < vertex_num; i++){
       if (vertex_list[i] == start_vertex)
          root_index = i;
   }
   assert(root_index != -1);

   VertexColor color_list[vertex_num]; //lista de cores, distancia e pais de cada vertice
   int distance_list[vertex_num];
   int parent_list[vertex_num];

   for (int i = 0; i < vertex_num; i++){ 
       color_list[i] = WHITE; //inicia essa lista com valores padrões
       distance_list[i] = INF;
       parent_list[i] = NO_PARENT;
   }

   color_list[root_index] = GREY; //vertice raiz é inicializado como cinza, distancia 0 e sem parente
   distance_list[root_index] = 0;

   Fila* fila = fila_criar();
   fila_adicionar(fila, start_vertex); //adiciona o primeiro elemento na fila

   while (!fila_vazia(fila)){
      
      Fila_t cur_vertex = fila_remover(fila); //tira o primeiro da fila
      int num_adj_vertex;
      int* adj_vertexes = get_adj_vertex(cur_vertex,graph,&num_adj_vertex); //pega a lista de vertices adjancentes do atual

      for (int i = 0; i < num_adj_vertex; i++){ //loop por cada vertice adjancente
         int adj_vertex_index = -1;
         for (int j = 0; j < vertex_num; j++){ //loop pelos vertices do grafo pra achar o index certos
              if (adj_vertexes[i] == vertex_list[j]){
                  adj_vertex_index = j;
                  break;
              }
         }
         assert(adj_vertex_index != -1);

         if (color_list[adj_vertex_index]== WHITE){
            color_list[adj_vertex_index]= GREY;
            distance_list[adj_vertex_index] = distance_list[root_index] + 1;
         }
      }

   }

}

//função onde é tido que o grafo contem vertices com numeros em sequência. Ex: 1,2,3,4,5
void bfs_sequen_tree_from_vertex(Graph* graph, const int start_vertex){
   assert(graph);

   int vertex_num; //pega o numero de vertices a lista de vertices do grafo
   int* vertex_list = get_vertex_list(graph,&vertex_num);
   assert(vertex_list); assert(vertex_num != 0);
   
   int root_index = -1; //acha o index na lista de vertices do vertice do comeco da funcao
   for (int i = 0; i < vertex_num; i++){
       if (vertex_list[i] == start_vertex)
          root_index = i;
   }
   assert(root_index != -1);

   VertexColor color_list[vertex_num]; //lista de cores, distancia e pais de cada vertice
   int distance_list[vertex_num];
   int parent_list[vertex_num];

   for (int i = 0; i < vertex_num; i++){ 
       color_list[i] = WHITE; //inicia essa lista com valores padrões
       distance_list[i] = INF;
       parent_list[i] = NO_PARENT;
   }

   color_list[root_index] = GREY; //vertice raiz é inicializado como cinza, distancia 0 e sem parente
   distance_list[root_index] = 0;

   Fila* fila = fila_criar();
   fila_adicionar(fila, start_vertex); //adiciona o primeiro elemento na fila

   while (!fila_vazia(fila)){
      
      Fila_t cur_vertex = fila_remover(fila); //tira o primeiro da fila
      int num_adj_vertex;
      int* adj_vertexes = get_adj_vertex(cur_vertex,graph,&num_adj_vertex); //pega a lista de vertices adjancentes do atual

      for (int i = 0; i < num_adj_vertex; i++){ //loop por cada vertice adjancente
         int adj_vertex_index = -1;
         for (int j = 0; j < vertex_num; j++){ //loop pelos vertices do grafo pra achar o index certos
              if (adj_vertexes[i] == vertex_list[j]){
                  adj_vertex_index = j;
                  break;
              }
         }
         assert(adj_vertex_index != -1);

         if (color_list[adj_vertex_index]== WHITE){
            color_list[adj_vertex_index]= GREY;
            distance_list[adj_vertex_index] = distance_list[root_index] + 1
         }
      }

   }

}