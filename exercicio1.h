#ifndef EXERCICIO1_H
    #define EXERCICIO1_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <assert.h>
    #include <errno.h>
    
    #define GRAU_MAX 2
    #define assert_2ptrs(p1,p2) assert(p1); assert(p2);

    #define assert_3ptrs(p1,p2,p3) assert_2ptrs(p1,p2); assert(p3);

    #define  max(x, y)  ((x) > (y) ? (x) : (y))

    #define  safe_free(ptr) \
      free(ptr);            \
      ptr = NULL
    
    #define err_check(X) ({ int _val = (X);(_val == -1) ? \
                          (printf("ERROR: ("__FILE__") : %d -- %s \n",__LINE__, errno)); \
                          exit(-1);-1;})


    typedef struct grafo grafo_t;
    typedef enum conexao conexao_t;
    typedef int valor_t;

    enum conexao {
        bidirecional = 0,
        entrada  = 1,
        saida = 2
    };

    struct grafo {
        valor_t valor;
        int num_conexoes;
        conexao_t tipo_conexao;
        grafo_t** conexoes;
    };

    bool grafo_criar_no(const valor_t valor, const conexao_t tipo_conexao, const int num_conexoes, grafo_t** conexoes);
    bool grafo_criar_conexao(const conexao_t tipo_conexao, grafo_t* no1, grafo_t* no2);
    bool grafo_remover_conexao(grafo_t* no1, grafo_t* no2, grafo_t* no3);
    bool grafo_apagar(grafo_t** grafo_inicial);

#endif