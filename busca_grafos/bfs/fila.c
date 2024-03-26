#include "fila.h"

struct fila_ {
   Fila_t* elementos;
   uint num_elementos;
   uint final;
   uint comeco;
};

Fila* fila_criar(){

   Fila* fila = (Fila*) malloc(sizeof(Fila));
   assert(fila);

   Fila_t* elementos = (Fila_t*) malloc(sizeof(Fila_t) * QUEUE_CHUNK_SIZE);
   assert(elementos);

   fila->elementos = elementos;
   fila->num_elementos = 0;
   fila->comeco = -1;
   fila->final = 0;

   return fila;
}

void fila_destruir(Fila** fila){
   assert_2ptrs(fila, (*fila));
   
   Fila_t* lista_elem = (*fila)->elementos;
   free(lista_elem);
   lista_elem = NULL;

   free(*fila);
   *fila = NULL;
}

bool fila_vazia(const Fila* fila){
   assert(fila);
   return fila->num_elementos == 0;
}

bool fila_adicionar(Fila* fila, Fila_t elem){
   assert(fila);

   const uint novo_tam_fila = fila->num_elementos + 1;

   if ( (novo_tam_fila%QUEUE_CHUNK_SIZE)==0 ){ //fila chegou num multiplo do tamanho maximo de chunk
      fila->elementos = (Fila_t*) malloc( (sizeof(Fila_t) * fila->num_elementos) + QUEUE_CHUNK_SIZE );
      assert(fila->elementos);
   }

   fila->elementos[fila->final] = elem;
   fila->final++;
   fila->num_elementos++;

   if (fila->comeco == -1)
       fila->comeco = 0;

   return true;
}

Fila_t fila_remover(Fila* fila){
   assert(fila);
   assert(fila_vazia(fila) == false);

   Fila_t elem = fila->elementos[fila->comeco];
   fila->comeco++;
   fila->num_elementos--;

   return elem;
}

Fila_t fila_final(const Fila* fila){
   assert(fila);
   assert(fila_vazia(fila) == false);

   return fila->elementos[fila->final-1];
}

Fila_t fila_comeco(const Fila* fila){
   assert(fila);
   assert(fila_vazia(fila) == false);

   return fila->elementos[fila->comeco];
}

int main(){
   
}