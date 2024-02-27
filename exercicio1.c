#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "exercicio1.h"





bool grafo_criar_no(const valor_t valor, const conexao_t tipo_conexao, const int num_conexoes, grafo_t** conexoes) {
    assert(conexoes);
}

bool grafo_criar_conexao(const conexao_t tipo_conexao, grafo_t* no1, grafo_t* no2) {
    assert_2ptrs(no1,no2);
}

bool grafo_remover_conexao(grafo_t* no1, grafo_t* no2, grafo_t* no3) {
    assert_3ptrs(no1,no2,no3);
    //safe_free(2);
}

// todos os grafos devem estar conectados para essa função funcionar corretamente
bool grafo_apagar(grafo_t** grafo_inicial){
    assert(grafo_inicial);
    //free()
}


bool __grafo_rearranjar(){

}

int main(){

    grafo_t grafo1 = {
        .valor = 1,
        .num_conexoes = 2,
        .tipo_conexao = bidirecional,
        .conexoes = NULL,
    };
    grafo_t* ptr = &grafo1;
    grafo_t* ptr2 = (grafo_t*) malloc(sizeof(grafo_t));
   // printf("%d", ptr->tipo_conexao);
    grafo_remover_conexao(ptr2,ptr,NULL);

    

    
}



