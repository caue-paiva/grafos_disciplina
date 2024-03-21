#include "matriz_adja.h"


void __grafo_ma_lidar_inputs(const uint no1, const uint no2, const uint num_nos){
     if (no1 > num_nos || no2 > num_nos)
       err_exit("valores de no1 ou no2 nao existe no grafo de tam  (%d) || valor no1: %d , valor no2: %d", num_nos,no1,no2);
     if (num_nos <= 0)
        err_exit("num_nos nao pode ser negativo ou zero");
     if (no1 < 0 || no2 < 0)
        err_exit("numero de no1 (%d)  e/ou no2 (%d) nao podem ser negativos", no1, no2);
     if (no1 == no2)
        err_exit("no1 e no2 nao podem ser o mesmo no || Numero do no:  %d", no1); 
}

uint grafo_ma_achar_grau(const uint no, const GrafoMa* grafo){
     assert(grafo);
     __grafo_ma_lidar_inputs(no,0,grafo->num_nos);

     int** matriz = grafo->matriz;
     uint grau = 0;

     for (int i = 0; i < grafo->num_nos; i++){
          if(matriz[no][i] == 1)
             grau+=1;
     }

     return grau;
}

//retorna um array onde o index 0 é o grau do grafo e o 1 é o no com esse grau.
//OBS: aloca memória.
uint* grafo_ma_achar_maior_grau(const GrafoMa* grafo){
      uint maior_grau = -1;
      uint no_maior_grau = -1;

      for (int i = 0; i < grafo->num_nos; i++){
             uint grau_atual = grafo_ma_achar_grau(i,grafo);
             if (grau_atual > maior_grau){
                 maior_grau = grau_atual;
                 no_maior_grau = i;
             }
      }

      int* grau_e_no = (int*) malloc(sizeof(int)*2);
      assert(grau_e_no);

      grau_e_no[0] = maior_grau;
      grau_e_no[1] = no_maior_grau;

      return grau_e_no;
}

GrafoMa* grafo_ma_criar(const uint num_nos){

   GrafoMa* grafo = (GrafoMa*) malloc(sizeof(GrafoMa));
   assert(grafo);

   grafo->num_nos = num_nos;
   grafo->num_arestas = 0;

   int** matriz = (int**) malloc(sizeof(int*) * num_nos);
   assert(matriz);

   for (int i = 0 ; i < num_nos; i++){
      matriz[i] = (int*) calloc( num_nos,sizeof(int)); //calloc inicia todos os valores pra 0
      assert(matriz[i]); 
   }

   grafo->matriz = matriz;
   return grafo;
}

//add conexão em grafo bi-direcional/dígrafo
bool grafo_ma_add_conexao(const uint no1, const uint no2, GrafoMa* grafo){
     assert(grafo);
     __grafo_ma_lidar_inputs(no1,no2,grafo->num_nos);
     if (no1 > grafo->num_nos || no2 > grafo->num_nos)
        err_exit("no1 ou no2 nao existem no grafo com %d nos", grafo->num_nos);

     if(grafo->matriz[no1][no2] == 1) //conexao ja existe
        return false;
     
     grafo->matriz[no1][no2] = 1; //no caso de dígrafos, as conexões são simétricas
     grafo->matriz[no2][no1] = 1;
     
     grafo->num_arestas += 1; //arestas bi-direcionais
     return true;
}
//remover conexão em grafo bi-direcional/dígrafo
bool grafo_ma_remo_conexao(const uint no1, const uint no2, GrafoMa* grafo){
     assert(grafo);
     __grafo_ma_lidar_inputs(no1,no2,grafo->num_nos);

     if(grafo->matriz[no1][no2] == 0) //conexao não existe
        return false;
     
     grafo->matriz[no1][no2] = 0; //no caso de dígrafos, as conexões são simétricas
     grafo->matriz[no2][no1] = 0;

     grafo->num_arestas -= 1; //arestas bi-direcionais

     return true;
}

void grafo_ma_print(const GrafoMa* grafo){
    assert(grafo);
    uint num_nos = grafo->num_nos;
    printf("\n     "); 
    for (int i = 0; i < num_nos; i++){
      printf("%d ", i);
    }
    printf("\n     ");
    for (int i = 0; i < num_nos; i++){
      printf("--");
    }
    printf("\n");


    for (int i = 0; i < num_nos; i++){
      printf("%d: [ ",i); 
      for (int j = 0; j < num_nos; j++){
         printf("%d ", grafo->matriz[i][j]);
      }
      printf("]\n");
      
    }
    
}


int main(){

   GrafoMa* grafo = grafo_ma_criar(3);
   grafo_ma_add_conexao(1,1,grafo);
   grafo_ma_add_conexao(0,2,grafo);
   grafo_ma_add_conexao(1,2,grafo);
   grafo_ma_add_conexao(1,0,grafo);

   grafo_ma_print(grafo);

}

