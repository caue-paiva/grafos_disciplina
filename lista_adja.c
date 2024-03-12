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

//codigo para os nos (lista encad) do grafo
No* __grafos_la_final_lista(const No* no_comeco){
    assert(no_comeco);
    No* atual = no_comeco;

    while(atual->prox){
         atual = atual->prox;
    }

    return atual;
}

No* grafos_la_criar_no(const int numero) {
    if (numero == 0)
        err_exit("Numero do nos comecam a partir do 1, nao pode ser 0");
    No* no = (No*) malloc(sizeof(No));
    assert(no);

    no->numero_no = numero;
    no->prox = NULL;

    return no;
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

static bool __grafos_la_header_adicionar_no(const int numero_header,No* no, NoHeader** lista_headers) {
     assert_3ptrs(no,lista_headers,lista_headers[numero_header-1]);
     if (numero_header <= 0)
        err_exit("Numero do nos comecam a partir do 1, nao pode ser 0 ou negativo");
     
     NoHeader* header_atual = lista_headers[numero_header-1];

     if (!header_atual->prox){ //se o NoHeader->prox estiver vazio
         d_printf("header vazio");
         header_atual->prox = no; 
         header_atual->final = no; 
         return true;
     
     }else{ //se o noheader estiver apontando para mais coisas
          d_printf("header ja tem items");
          No* final = __grafos_la_final_lista(header_atual->prox);
          final->prox = no;
          header_atual->final = no;
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

bool grafo_la_adicionar_conexao(const int numero_no, No* nova_conexao, GrafoLa* grafo){
    if (numero_no == 0)
        err_exit("Numero do nos comecam a partir do 1, nao pode ser 0");

    if (numero_no > grafo->num_nos){
        err_exit("No para add conexao %d nao existe no grafo com %d nos",numero_no,  grafo->num_nos);
    }
    if (nova_conexao->numero_no > grafo->num_nos){
        err_exit("No da nova conexao %d nao existe no grafo com %d nos", nova_conexao->numero_no,  grafo->num_nos);        
    }
    return __grafos_la_header_adicionar_no(numero_no,nova_conexao,grafo->lista_headers);
}


//funcoes de i/o para o usuário
void grafos_la_print(const GrafoLa* grafo){
     
    NoHeader** lista_headers = grafo->lista_headers;
    uint numero_nos = grafo->num_nos;

    for (int i = 0; i < numero_nos ; i++){
         printf("No: %d ,Conexoes: ", lista_headers[i]->num_header);
         __grafos_print_conexoes_no(lista_headers[i]);
        
    }
}


int main(){

    GrafoLa* grafo = grafo_la_criar(6);
    No* no1 = grafos_la_criar_no(3);
    No* no2 = grafos_la_criar_no(5);

    grafo_la_adicionar_conexao(1,no1,grafo);
    grafo_la_adicionar_conexao(1,no2,grafo);
    grafo_la_adicionar_conexao(6,no2,grafo);

    grafos_la_print(grafo);

    //printf("%d %d \n", lista_grafos[0]->prox->numero_no, lista_grafos[0]->final->numero_no );

    /*NoHeader** lista_grafos = criar_listas_grafos(3);

    No* no1 = criar_no(2);
    No* no2 = criar_no(3);

    lista_grafos[0] = no1;
    lista_grafos[0]->prox = no2;

    printf("%d \n", lista_grafos[0]->prox->numero_no);*/
}