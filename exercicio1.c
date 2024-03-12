#include "exercicio1.h"



bool grafo_criar_no(const valor_t valor, const conexao_t tipo_conexao, const int num_conexoes, no_grafo_t** conexoes) {
    assert(conexoes);
}

bool grafo_criar_conexao(const conexao_t tipo_conexao, no_grafo_t* no1, no_grafo_t* no2) {
    assert_2ptrs(no1,no2);
}

bool grafo_remover_conexao(no_grafo_t* no1, no_grafo_t* no2, no_grafo_t* no3) {
    assert_3ptrs(no1,no2,no3);
    //safe_free(2);
}

// todos os grafos devem estar conectados para essa função funcionar corretamente
bool grafo_apagar(no_grafo_t** grafo_inicial){
    assert(grafo_inicial);
    //free()
}


bool __grafo_rearranjar(){

}

int main(){

    no_grafo_t grafo1 = {
        .valor = 1,
        .num_conexoes = 2,
        .tipo_conexao = bidirecional,
        .conexoes = NULL,
    };

    no_grafo_t* ptr = &grafo1;
    no_grafo_t* ptr2 = (no_grafo_t*) malloc(sizeof(no_grafo_t));
   // printf("%d", ptr->tipo_conexao);
    grafo_remover_conexao(ptr2,ptr,NULL);

    //int f_result = open("hahah.txt", O_RDONLY);

    deb(2);


}



