#include "lista_adja.h"


struct no {
    int numero_no;
    struct no* prox;
};

struct no_header { //header em cada index para apontar o seu número , o proximo grafo ligado e o grafo final da lista encad
    uint num_header;
    struct no* prox;
    struct no* final;
};

struct grafo_la {
     struct no_header** lista_headers;
     uint num_nos;
};

typedef struct no No;
typedef struct no_header NoHeader;
typedef struct grafo_la GrafoLa;

//funcao de error handling do input de outras funcoes, como por ex: tentar modificar um no que nao existe no grafo
void __grafos_la_aux_verificar_input(const uint tam_grafo, const uint valor_no, const uint valor_conexao){
    if (tam_grafo <= 0 || valor_no <= 0 || valor_conexao <= 0)
        err_exit("valores do tamanho do grafos ou de nos nao podem ser 0 ou negativo || tam grafo %d , valor no %d , valor conexao %d", tam_grafo,valor_no,valor_conexao);

    if (valor_no > tam_grafo || valor_conexao > tam_grafo)
        err_exit("Valor do no para ser modificado ou da conexao nao existe no grafo com %d nos  || valor no %d , valor conexao %d", tam_grafo,valor_no,valor_conexao);
}


//codigo para os nos (lista encad) do grafo

No* __grafos_la_no_final_lista(const No* no_comeco){
    assert(no_comeco);
    No* atual = no_comeco;

    while(atual->prox){
         atual = atual->prox;
    }

    return atual;
}

No* __grafos_la_no_criar(const int numero) {
    if (numero == 0)
        err_exit("Numero do nos comecam a partir do 1, nao pode ser 0");
    
    No* no = (No*) malloc(sizeof(No));
    assert(no);

    no->numero_no = numero;
    no->prox = NULL;

    return no;
}

void __grafos_la_no_destruir(No** no){
    assert_2ptrs(no,*no);

    free(*no);
    *no = NULL;
}


//codigo para os headers de cada no (acessar a lista encad)

static NoHeader** __grafos_la_header_criar_lista(const int tam_lista){
    if (tam_lista <= 0)
        err_exit("Tam da lista n pode ser 0 ou negativo");

    NoHeader** lista_headers = (NoHeader**) malloc(sizeof(NoHeader*) * tam_lista);
    assert(lista_headers);

    for (int i = 0 ; i < tam_lista; i++){
        lista_headers[i] = (NoHeader*) malloc(sizeof(NoHeader*));
        assert(lista_headers[i]);
        lista_headers[i]->prox = NULL; //seta todos os headers com seus números e apontando pra null
        lista_headers[i]->final = NULL;
        lista_headers[i]->num_header = i+1; //num dos nos começam do 1
    }
  
    return lista_headers;
}

static bool __grafos_la_header_adicionar_no(const uint numero_header,const uint numero_conexao, NoHeader** lista_headers) {
     assert_2ptrs(lista_headers,lista_headers[numero_header-1]);
     if (numero_header <= 0)
        err_exit("Numero do nos comecam a partir do 1, nao pode ser 0 ou negativo");
     
     NoHeader* header_atual = lista_headers[numero_header-1];
     No* novo_no = __grafos_la_no_criar(numero_conexao); //cria um novo no para a nova conexao

     if (!header_atual->prox){ //se o NoHeader->prox estiver vazio
         header_atual->prox = novo_no; 
         header_atual->final = novo_no; 
         return true;
     
     }else{ //se o noheader estiver apontando para mais coisas
          No* final = __grafos_la_no_final_lista(header_atual->prox);
          final->prox = novo_no;
          header_atual->final = novo_no;
          return true;
     }
}

NoHeader** grafos_la_realocar_lista(NoHeader**lista_antiga, const int novo_tamanho) {
        assert(lista_antiga);

        NoHeader** nova_lista = (NoHeader**) realloc(lista_antiga, sizeof(NoHeader) * novo_tamanho);
        assert(nova_lista);

        return nova_lista;
}

static void __grafos_print_conexoes_no(const NoHeader* header){
     assert(header);
     No* atual = header->prox;

     while(atual){
        printf("%d ",atual->numero_no);
        atual = atual->prox;
     }
     printf("\n");
}

static bool __grafos_la_header_remover_conexao(const uint num_no, const uint num_conexao, NoHeader**lista_headers ){
     assert(lista_headers);

     NoHeader* header = lista_headers[num_no-1];

     if(!header->prox) //não existem conexoes naquele no
        return false;

     No* comeco = header->prox; 
     No* atual = comeco;
     No* anterior = NULL;

     while(atual){

        if(atual->numero_no == num_conexao){ //achamos o no para remover
            No* prox = atual->prox; //pode ser NULL

            if (atual == comeco) { //o buscado esta no comeco do header
                header->prox = prox;
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


//codigo para o TAD grafos em si (que o user vai acessar)

GrafoLa* grafo_la_criar(const uint numero_nos){
    if (numero_nos < 0)
        err_exit("num de nos n pode ser negativo");

    GrafoLa* grafo = (GrafoLa*) malloc(sizeof(GrafoLa));
    assert(grafo);

    grafo->num_nos = numero_nos;
    grafo->lista_headers = __grafos_la_header_criar_lista(numero_nos);

    return grafo;
}

bool grafo_la_adicionar_conexao(const uint numero_no, const uint nova_conexao, GrafoLa* grafo){
    __grafos_la_aux_verificar_input(grafo->num_nos,numero_no,nova_conexao);

    return __grafos_la_header_adicionar_no(numero_no,nova_conexao,grafo->lista_headers);
}

bool grafo_la_remover_conexao(const int numero_no, const uint conexao, GrafoLa* grafo){
    assert(grafo);
    __grafos_la_aux_verificar_input(grafo->num_nos,numero_no, conexao);

    return __grafos_la_header_remover_conexao(numero_no,conexao,grafo->lista_headers);
}


//funcoes de i/o para o usuário

void grafos_la_print(const GrafoLa* grafo){
     
    NoHeader** lista_headers = grafo->lista_headers;
    uint numero_nos = grafo->num_nos;

    for (int i = 0; i < numero_nos ; i++){
         printf("No: %d ,Conexoes: ", lista_headers[i]->num_header);
         __grafos_print_conexoes_no(lista_headers[i]);
        
    }
    printf("\n");
}


int main(){

    GrafoLa* grafo = grafo_la_criar(6);

    grafo_la_adicionar_conexao(1,3,grafo);
    grafo_la_adicionar_conexao(1,5,grafo);
    grafo_la_adicionar_conexao(6,5,grafo);

    grafos_la_print(grafo);

    bool resultado = grafo_la_remover_conexao(1,6,grafo);
    grafo_la_remover_conexao(1,3,grafo);
    printf("resultado %d \n", resultado);

    grafos_la_print(grafo);

    //printf("%d %d \n", lista_grafos[0]->prox->numero_no, lista_grafos[0]->final->numero_no );

    /*NoHeader** lista_grafos = criar_listas_grafos(3);

    No* no1 = criar_no(2);
    No* no2 = criar_no(3);

    lista_grafos[0] = no1;
    lista_grafos[0]->prox = no2;

    printf("%d \n", lista_grafos[0]->prox->numero_no);*/
}