#include "bfs.h"

//dado uma lista de vertices do grafo e um valor, retorna o indice desse valor na lista se existir, senão retorna -1
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
int* bfs_tree_from_vertex(const Graph* graph, const int start_vertex){
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

//retorna o caminho mais curto entre 2 vértices, ou NULL se eles não forem conexos
int* bfs_shortest_path_vertexes(const Graph* graph, const int start_vertex, const int end_vertex, int* path_size){
   assert(graph); assert(start_vertex != end_vertex);
   
   int vertex_num; //numero de vertices do grafo
   int* vertex_list = get_vertex_list(graph, &vertex_num); //lista de vertices do grafo

   int* relationship_list = bfs_tree_from_vertex(graph,start_vertex); //lista de parentesco que a BFS retorna
   int end_vertex_index = __find_index(vertex_list,vertex_num,end_vertex); //indice do vertice do final do caminho

   if (relationship_list[end_vertex_index] == NO_PARENT){ //caso o vertex do final nao tenha parentesco com o do começo
           warn_printf("o vertice final nao e adjacente ao inicial, retornando ponteiro NULL");
           free(vertex_list);
           free(relationship_list);
           return NULL;
   } 

   int shortest_path[vertex_num];  //vetor na stack para o caminho mai proximos, usado para guardar valores internamente na função 
   
   int path_index = 0; //index que vamos colocar no vetor de caminho mais prox
   int cur_parent = relationship_list[end_vertex_index]; //index do pai do ultimo vertice do caminho

   while (cur_parent != NO_PARENT){ //enquanto não chegarmos no vertice raiz
      int cur_parent_val = vertex_list[cur_parent]; //valor do vertice pai 
      shortest_path[path_index] = cur_parent_val; //coloca o valor do vertice pai no caminho de retorno
      path_index++; //prox indice do caminho
      cur_parent = relationship_list[cur_parent]; //acha o novo pai na lista de parentesco
   }

   *path_size = path_index+1; //variavel para saber o tamanho do path

   int* shortest_path_return = (int*) malloc(sizeof(int) * (path_index+1) );
   assert(shortest_path_return);

   shortest_path_return[0] = end_vertex; //primeiro valor do novo caminho é o vertice do final
   for (int i = 1; i < path_index+1; i++){
       shortest_path_return[i] = shortest_path[i-1];
   }

   free(vertex_list);
   free(relationship_list);
   return shortest_path_return;
}

int main(){
   Graph* g1 = graph_create(6);

   add_edge(1,2,3,g1);
   add_edge(1,3,3,g1);
   add_edge(2,4,3,g1);
   add_edge(2,6,3,g1);
   add_edge(6,5,3,g1);

   //print_info(g1);

   /*int* lista_parentesco = bfs_tree_from_vertex(g1,1);

   for (int i = 0; i < 6; i++){
       printf("%d ",lista_parentesco[i]);
   }
   */
   int tamanho;
   int* caminho_curto = bfs_shortest_path_vertexes(g1,1,6,&tamanho);
   for (int i = 0; i < tamanho; i++){
       printf("%d ",caminho_curto[i]);
   }
   printf("\n");

}