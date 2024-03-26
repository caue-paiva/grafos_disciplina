#include "bfs.h"

int __find_index(const int* list,const int list_size ,const int item){
   assert(list);

   for (int i = 0; i < list_size; i++){
        if (list[i] == item)
           return i;
   }

   return -1;
}

//retorna a lista de parentesco na forma de uma arvore a partir de um vertice
//o indice da lista é o indice do elemento na lista de vertices do grafo e seu conteudo é o indice nas 2 listas do seu parent
int* bfs_tree_from_vertex(Graph* graph, const int start_vertex){
   assert(graph);

   int vertex_num; //pega o numero de vertices a lista de vertices do grafo
   int* vertex_list = get_vertex_list(graph,&vertex_num);
   assert(vertex_list); assert(vertex_num != 0);
   
   int root_index = __find_index(vertex_list,vertex_num,start_vertex); //acha o index na lista de vertices do vertice do comeco da funcao
   assert(root_index != -1);

   VertexColor color_list[vertex_num]; //lista de cores, distancia e pais de cada vertice
   int distance_list[vertex_num];
   int* parent_list = (int*) malloc(sizeof(int)*vertex_num);
   assert(parent_list);

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
      int cur_vertex_index = __find_index(vertex_list,vertex_num,cur_vertex);
      assert(cur_vertex_index != -1);
      
      int num_adj_vertex;
      int* adj_vertexes = get_adj_vertex(cur_vertex,graph,&num_adj_vertex); //pega a lista de vertices adjancentes do atual

      for (int i = 0; i < num_adj_vertex; i++){ //loop por cada vertice adjancente
         int adj_vertex_index = __find_index(vertex_list,vertex_num,adj_vertexes[i]); //acha o indice do vertice adjacente atual
         assert(adj_vertex_index != -1);

         if (color_list[adj_vertex_index] == WHITE){
             color_list[adj_vertex_index] = GREY;
             distance_list[adj_vertex_index] = distance_list[cur_vertex_index] + 1;
             parent_list[adj_vertex_index] = cur_vertex_index;
             fila_adicionar(fila,adj_vertexes[i]); //adiciona o vértice na lista
         }
      }
      color_list[cur_vertex_index] = BLACK;

   }

   return parent_list;

}

/*
//função onde é tido que o grafo contem vertices com numeros em sequência começando do 0. Ex: 0,1,2,3,4,5
void bfs_sequen_tree_from_vertex(Graph* graph, const int start_vertex){
   assert(graph);

   int vertex_num; //pega o numero de vertices a lista de vertices do grafo
   int* vertex_list = get_vertex_list(graph,&vertex_num);
   assert(vertex_list[0] == 0 || vertex_list[0] == 1);

   if (vertex_list[0] == 1){
      int* vertex_list_temp = (int*) malloc(sizeof(int) * (vertex_num +1) );
      assert(vertex_list_temp);

      for (int i = 0; i < vertex_num+1; i++){ //copia os valores dos vertices mas coloca 0 no começo
          if (i == 0)
             vertex_list_temp[i] = 0;
          else
            vertex_list_temp[i] = vertex_list[i-1];
       
      }

      free(vertex_list);
      vertex_list = vertex_list_temp;
      vertex_num++; //coloca
   }


  
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

*/

int main(){
   Graph* g1 = graph_create(6);

   add_edge(1,2,3,g1);
   add_edge(1,3,3,g1);
   add_edge(2,4,3,g1);
   add_edge(2,6,3,g1);
   add_edge(6,5,3,g1);

   print_info(g1);

   int* lista_parentesco = bfs_tree_from_vertex(g1,1);

   for (int i = 0; i < 6; i++){
       printf("%d ",lista_parentesco[i]);
   }
   printf("\n");

}