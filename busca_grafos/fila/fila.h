#ifndef PILHA_H
   #define PILHA_H
   #include <stdlib.h>
   #include <stdio.h>
   #include <stdbool.h>
   #include <assert.h>
   
   #define assert_2ptrs(p1,p2) assert(p1); assert(p2);

   #define QUEUE_CHUNK_SIZE 50
   
   typedef unsigned int uint;
   typedef struct fila_ Fila;
   typedef int Fila_t;

   Fila* fila_criar();
   void fila_destruir(Fila** fila);
   bool fila_vazia(const Fila* fila);
   bool fila_adicionar(Fila* fila, Fila_t elem);
   Fila_t fila_remover(Fila* fila);
   Fila_t fila_final(const Fila* fila);
   Fila_t fila_comeco(const Fila* fila);

#endif