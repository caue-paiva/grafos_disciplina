#ifndef PILHA_H
   #define PILHA_H
   #include <stdlib.h>
   #include <stdio.h>
   #include <stdbool.h>
   #include <assert.h>
   
   #define assert_2ptrs(p1,p2) assert(p1); assert(p2);

   #define STACK_CHUNK_SIZE 50
   
   typedef unsigned int uint;
   typedef struct pilha_ Pilha;
   typedef int Pilha_t;

   Pilha* pilha_criar();
   void pilha_destruir(Pilha** pilha);
   bool pilha_empilhar(Pilha* pilha, Pilha_t elem);
   bool pilha_vazia(const Pilha*pilha);
   Pilha_t pilha_desempilhar(Pilha* pilha);
   Pilha_t pilha_topo(const Pilha* pilha);

#endif