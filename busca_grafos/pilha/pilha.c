#include "pilha.h"

struct pilha_ {
   Pilha_t* elementos;
   uint num_elementos;
   uint topo;
};


Pilha* pilha_criar(){
   
   Pilha* pilha = (Pilha*) malloc(sizeof(pilha));
   assert(pilha);

   pilha->elementos = (Pilha_t*) malloc(sizeof(Pilha_t)*STACK_CHUNK_SIZE);
   assert(pilha->elementos);

   pilha->topo = -1;
   pilha->num_elementos = 0;

   return pilha;
}

void pilha_destruir(Pilha** pilha){
     assert_2ptrs(pilha, (*pilha));

     Pilha_t* lista_elementos = (*pilha)->elementos;
     free(lista_elementos);
     lista_elementos = NULL;

     free((*pilha));
     *pilha = NULL;
}

bool pilha_empilhar(Pilha* pilha, Pilha_t elem){
   assert(pilha);

   const uint novo_num_elem = pilha->num_elementos + 1; 
   if ((novo_num_elem % STACK_CHUNK_SIZE) == 0 ){ //pilha chegou num multiplo do tamanho maximo de chunk
         pilha->elementos = (Pilha_t*) malloc( (sizeof(Pilha_t) * pilha->num_elementos) + STACK_CHUNK_SIZE ); //adicionar mais uma chunk pra lista
         assert(pilha->elementos);
   }

   pilha->topo++;
   pilha->elementos[pilha->topo] = elem;
   pilha->num_elementos++;
   
   return true;
}

bool pilha_vazia(const Pilha*pilha){
     assert(pilha);
     return (pilha->num_elementos) == 0;
}

Pilha_t pilha_desempilhar(Pilha* pilha){
   assert(pilha);
   assert(pilha_vazia(pilha) == false);

   Pilha_t elem = pilha->elementos[pilha->topo];
   pilha->topo--;
   pilha->num_elementos--;
   
   return elem;  
}

bool pilha_topo(const Pilha* pilha){
     assert(pilha);
     return pilha->elementos[pilha->topo];
}