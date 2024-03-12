#ifndef EXERCICIO1_H
    #define EXERCICIO1_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <assert.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <string.h>
    
    #define GRAU_MAX 2

    #define deb(X) do {                                       \
        if ((X) == (X)) {                                      \
            printf("ERROR: (%s) : %d --\n",__FILE__,__LINE__);  \
                                                                 \
        }                                                         \
        } while (0)
    
    //macros
    #define assert_2ptrs(p1,p2) assert(p1); assert(p2);

    #define assert_3ptrs(p1,p2,p3) assert_2ptrs(p1,p2); assert(p3);

    #define  max(x, y)  ((x) > (y) ? (x) : (y))

    #define  safe_free(ptr) \
      free(ptr);             \
      ptr = NULL
    
    #define err_check(X) do {                                            \
        if ((X) == -1) {                                                  \
            printf("ERROR: (%s) : %d -- %s \n",__FILE__,__LINE__, strerror(errno));\
            exit(-1);                                                       \
        }                                                                    \
        } while (0)
        //strerror vem do string.h

    typedef struct no_grafo no_grafo_t;
    typedef enum conexao conexao_t;
    typedef int valor_t;

    enum conexao {
        bidirecional = 0,
        entrada  = 1,
        saida = 2
    };

    struct no_grafo {
        valor_t valor;
        int num_conexoes;
        conexao_t tipo_conexao;
        no_grafo_t** conexoes;
    };



    bool grafo_criar_no(const valor_t valor, const conexao_t tipo_conexao, const int num_conexoes, no_grafo_t** conexoes);
    bool grafo_criar_conexao(const conexao_t tipo_conexao, no_grafo_t* no1, no_grafo_t* no2);
    bool grafo_remover_conexao(no_grafo_t* no1, no_grafo_t* no2, no_grafo_t* no3);
    bool grafo_apagar(no_grafo_t** grafo_inicial);

#endif