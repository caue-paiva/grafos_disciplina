#include "../inc/lista_adja.h"
/*

struct no_aresta {
    int numero_no;
    int peso;
    struct no* prox;
};

//headers representam os nos e apontam para o comeco de suas arestas, pro final das arestas e prox prox_header (prox no na lista)
struct vertex { 
    int num;
    int weight;
    struct vertex* edges;
    struct vertex* next_vertex;
};

struct grafo_la {
     struct no_header* vertex_list;
     uint num_nos;
};

typedef struct no_aresta NoAresta;
typedef struct vertex Vertex;
typedef struct grafo_la Grafo;

//funcao de error handling do input de outras funcoes, como por ex: tentar modificar um no que nao existe no grafo
void __grafos_la_aux_verificar_input(const uint tam_grafo, const uint valor_no, const uint valor_conexao){
    if (tam_grafo <= 0 || valor_no <= 0 || valor_conexao <= 0)
        err_exit("valores do tamanho do grafos ou de nos nao podem ser 0 ou negativo || tam grafo %d , valor no %d , valor conexao %d", tam_grafo,valor_no,valor_conexao);

    if (valor_no > tam_grafo || valor_conexao > tam_grafo)
        err_exit("Valor do no para ser modificado ou da conexao nao existe no grafo com %d nos  || valor no %d , valor conexao %d", tam_grafo,valor_no,valor_conexao);
}


//codigo para os nos (lista encad) do grafo

static NoAresta* __grafos_la_no_final_lista(NoAresta* no_comeco){
    assert(no_comeco);
    NoAresta* atual = no_comeco;

    while(atual->prox){
         atual = atual->prox;
    }

    return atual;
}

Vertex* __create_vertex(const int num, const int weight){
        Vertex* vertex =  (Vertex*) malloc(sizeof(Vertex));
        assert(vertex);

        vertex->edges = NULL;
        vertex->next_vertex = NULL;
        vertex->num = num;
        vertex->weight = weight;

        return vertex;
}

//codigo para os headers de cada no (acessar a lista encad)

static bool __grafos_la_header_adicionar_conexao(const uint numero_header,const uint numero_conexao, Vertex** lista_headers) {
     assert_2ptrs(lista_headers,lista_headers[numero_header-1]);
     if (numero_header <= 0)
        err_exit("Numero do nos comecam a partir do 1, nao pode ser 0 ou negativo");
     
     Vertex* header_atual = lista_headers[numero_header-1];
     NoAresta* novo_no = __grafos_la_no_criar(numero_conexao); //cria um novo no para a nova conexao

     if (!header_atual->comeco_arestas){ //se o Vertex->prox estiver vazio
         header_atual->comeco_arestas = novo_no; 
         header_atual->final_arestas = novo_no; 
         return true;
     
     }else{ //se o noheader estiver apontando para mais coisas
          NoAresta* final = __grafos_la_no_final_lista(header_atual->comeco_arestas);
          final->prox = novo_no;
          header_atual->final_arestas = novo_no;
          return true;
     }
}

static Vertex** grafos_la_realocar_lista(Vertex**lista_antiga, const int novo_tamanho) {
        assert(lista_antiga);

        Vertex** nova_lista = (Vertex**) realloc(lista_antiga, sizeof(Vertex) * novo_tamanho);
        assert(nova_lista);

        return nova_lista;
}

static void __grafos_header_print_conexoes_no(const Vertex* header){
     assert(header);
     NoAresta* atual = header->comeco_arestas;

     while(atual){
        printf("%d ",atual->numero_no);
        atual = atual->prox;
     }
     printf("\n");
}

static bool __grafos_la_header_remover_conexao(const uint num_no, const uint num_conexao, Vertex**lista_headers ){
     assert(lista_headers);

     Vertex* header = lista_headers[num_no-1];

     if(!header->comeco_arestas) //não existem conexoes naquele no
        return false;

     NoAresta* comeco = header->comeco_arestas; 
     NoAresta* atual = comeco;
     NoAresta* anterior = NULL;

     while(atual){

        if(atual->numero_no == num_conexao){ //achamos o no para remover
            NoAresta* prox = atual->prox; //pode ser NULL

            if (atual == comeco) { //o buscado esta no comeco do header
                header->comeco_arestas = prox;
                __grafos_la_no_destruir(&atual);
                return true;
            }

            //o no a ser removido esta no meio da lista
            anterior->prox = prox; //prox do anterior vira prox do atual
            __grafos_la_no_destruir(&atual);
            return true;
        }

        anterior = atual;
        atual = atual->prox;
     }

     return false;
}

static bool __grafos_la_header_destruir_conexoes(Vertex* header){
            assert(header);

            if(!header->comeco_arestas) // se o header nao estiver apontando para ngm
               return false;
            
            NoAresta* atual = header->comeco_arestas;
            NoAresta* aux = atual;

            while(atual){
                atual = atual->prox;
                __grafos_la_no_destruir(&aux);
                aux = atual;
            }

            header->comeco_arestas = NULL;
            return true;
}

//como estamos num vetor e vamos remover um nó , precisamos shiftar eles
bool __grafo_la_header_shiftar_lista(const uint numero_de_nos,const uint numero_header, Vertex** lista_headers){
    assert(lista_headers);
    // se temos 5 nos -> 0,1,(2),3,4
    uint num_nos = numero_de_nos - 1; // 5
    uint num_header = numero_header - 1; // 3 o input comeca de 1, a logica do array comeca do 0
    
    for (int i = num_header; i < num_nos; i++ ) { //vamos chegar ate o penultimo elemento
        lista_headers[i] = lista_headers[i+1];
    }

    lista_headers[num_nos] = NULL; //não vamos dar free no ponteiro da ultima posicao pq os dados dele devem continuar a existir, mas outra posicao

    return true;
}

//se o vertice existe, retorna ele, senao retorna null
Vertex* __get_vertex(const int vertex_num, const Grafo* graph){
     assert(graph);

    if(graph->vertex_list == NULL) { //caso o grafo esteja vazio
        return NULL;
    }

    Vertex* cur_vertex = graph->vertex_list;
    if(cur_vertex->num == vertex_num)
       return cur_vertex;

    while(cur_vertex->next_vertex){
        cur_vertex = cur_vertex->next_vertex;
        if(cur_vertex->num == vertex_num)
            return cur_vertex;
    }

    return NULL;
}


//codigo para o TAD grafos em si (que o user vai acessar)



Grafo* graph_create(){

    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    assert(grafo);

    grafo->num_nos = 0;
    grafo->vertex_list = NULL;

    return grafo;
}

bool add_vertex(const int num, const int weight, Grafo* grafo) {
    assert(grafo);

    Vertex* first_vertex = grafo->vertex_list;

    if (first_vertex == NULL){ //grafo não tem nenhum vertice
       Vertex * first_vertex = __create_vertex(num,weight);

       grafo->vertex_list = first_vertex;
       grafo->num_nos += 1;

       return true;
    }

    Vertex* cur_vertex = first_vertex;

    while(cur_vertex->next_vertex != NULL){
         cur_vertex = first_vertex->next_vertex;
    }

    Vertex* new_vertex = __create_vertex(num,weight);
    cur_vertex->next_vertex = new_vertex;

    grafo->num_nos += 1;

    return true;
}


bool add_edge(const int vertex1, const int vertex2, const int weight ,Grafo* grafo){
    assert(grafo);

    if( (!__get_vertex(vertex1,grafo))||(!__get_vertex( vertex2,grafo)) ) {
        warn_printf("vertice 1 ou 2 nao existem no grafo");
        return false;
    }


    Vertex* first_vertex = __get_vertex(vertex1,grafo);
    Vertex* second_vertex = __get_vertex(vertex2,grafo);

    while(first_vertex->edges){
         first_vertex = first_vertex->edges;
    }
    first_vertex->edge = __create_vertex(vertex2)


    
}

bool grafo_la_remover_conexao(const int numero_no, const int conexao, Grafo* grafo){
    assert(grafo);
    __grafos_la_aux_verificar_input(grafo->num_nos,numero_no, conexao);

    return __grafos_la_header_remover_conexao(numero_no,conexao,grafo->lista_headers);
}

bool grafo_la_remover_no(const uint numero_no,Grafo* grafo) {
    assert(grafo); 
    __grafos_la_aux_verificar_input(grafo->num_nos,numero_no,1); //1 pq n temos valor de conexao
    
    Vertex* header = grafo->lista_headers[numero_no-1];

    __grafos_la_header_destruir_conexoes(header); //destruir as conexoes do header que vai ser removido
    __grafo_la_header_shiftar_lista(grafo->num_nos,numero_no,grafo->lista_headers); //shiftar a lista sequencial

    grafo->num_nos -= 1;

    //criar funcao para remover todas as outras conexoes do no removido dos outros nos, ou usar a funcao que ja existe
    return true;
}

//funcoes de i/o para o usuário

void grafos_la_print(const Grafo* grafo){
     
    Vertex** lista_headers = grafo->lista_headers;
    uint numero_nos = grafo->num_nos;

    for (int i = 0; i < numero_nos ; i++){
         printf("NoAresta: %d ,Conexoes: ", lista_headers[i]->num_header);
         __grafos_header_print_conexoes_no(lista_headers[i]);
        
    }
    printf("\n");
}


int main(){

    Grafo* grafo = grafo_la_criar(6);

    grafo_la_adicionar_conexao(1,3,grafo);
    grafo_la_adicionar_conexao(1,5,grafo);
    grafo_la_adicionar_conexao(6,1,grafo);
    grafo_la_adicionar_conexao(3,1,grafo);
    grafo_la_adicionar_conexao(6,3,grafo);

    grafos_la_print(grafo);

    grafo_la_remover_no(6,grafo);

  

    grafos_la_print(grafo);


    //printf("%d %d \n", lista_grafos[0]->prox->numero_no, lista_grafos[0]->final->numero_no );

    /*Vertex** lista_grafos = criar_listas_grafos(3);

    No* no1 = criar_no(2);
    No* no2 = criar_no(3);

    lista_grafos[0] = no1;
    lista_grafos[0]->prox = no2;

    printf("%d \n", lista_grafos[0]->prox->numero_no);*/
