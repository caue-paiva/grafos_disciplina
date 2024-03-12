#include "lista_adja.h"


struct no {
    int numero_no;
    struct no* prox;
};

struct no_header { //header em cada index para apontar o seu número , o proximo grafo ligado e o grafo final da lista encad
    int num_header;
    struct no* prox;
    struct no* final;
};

typedef struct no No;
typedef struct no_header NoHeader;

No* grafos_la_criar_no(const int numero) {
    No* no = (No*) malloc(sizeof(No));
    assert(no);

    no->numero_no = numero;
    no->prox = NULL;

    return no;
}

NoHeader** grafos_la_criar_lista_headers(const int tam_lista){

    NoHeader** lista_headers = (NoHeader**) malloc(sizeof(NoHeader*) * tam_lista);
    assert(lista_headers);

    for (int i = 0 ; i < tam_lista; i++){
        lista_headers[i]->prox = NULL; //seta todos os headers com seus números e apontando pra null
        lista_headers[i]->final = NULL;
        lista_headers[i]->num_header = i;
    }
  
    return lista_headers;
}

NoHeader** grafos_la_realocar_lista(NoHeader**lista_antiga, const int novo_tamanho) {
        assert(lista_antiga);

        NoHeader** nova_lista = (NoHeader**) realloc(lista_antiga, sizeof(NoHeader) * novo_tamanho);
        assert(nova_lista);

        return nova_lista;
}

bool grafos_la_adicionar_no(const int numero_header, const No* no, NoHeader** lista_headers) {

     if (lista_headers[numero_header]) //se exister um valor
        return false;
    

}


int main(){

    NoHeader** lista_grafos = criar_listas_grafos(3);

    No* no1 = criar_no(2);
    No* no2 = criar_no(3);

    lista_grafos[0] = no1;
    lista_grafos[0]->prox = no2;

    printf("%d \n", lista_grafos[0]->prox->numero_no);
}