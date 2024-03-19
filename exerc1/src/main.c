#include "graph.h"

int main() {
    int num_vertice;
    printf("Digite o numero de vertices inicial do grafo: ");
    scanf("%d", &num_vertice);

    Graph *grafo = graph_create(num_vertice);  // criacao do grafo

    int opcao = -1;
    while (opcao != 0) {

        printf("--------------------------");
        printf("\nOPCOES\n");
        printf("1 - Adicionar aresta\n");
        printf("2 - Remover aresta\n");
        printf("3 - Mostrar vertices e arestas com Matriz de adjancência\n");
        printf("4 - Mostrar lista de vertices adjacentes\n");
        printf("5 - Remover aresta de menor peso\n");
        printf("6 - Mostrar numero de vertices\n");
        printf("7 - Verificar existencia de aresta\n");
        printf("0 - Sair\n");
        printf("Digite sua opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Input invalido, por favor escreva um numero.\n");
            while(getchar() != '\n'); //limpa o buffer de input
            continue;
        }

        int num_vertice_1, num_vertice_2, weight;

        switch (opcao) {
            case 1:
                printf(
                    "Digite os numeros dos vertices que deseja adicionar uma "
                    "aresta: ");
                scanf("%d %d", &num_vertice_1, &num_vertice_2);
                printf("Digite o peso da aresta: ");
                scanf("%d", &weight);
                add_edge(num_vertice_1, num_vertice_2, weight, grafo);
                break;

            case 2:
                printf(
                    "Digite os numeros dos vertices que deseja remover uma "
                    "aresta: ");
                scanf("%d %d", &num_vertice_1, &num_vertice_2);
                remove_edge(num_vertice_1, num_vertice_2, grafo);
                break;

            case 3:
                print_info(grafo);
                break;

            case 4:
                printf(
                    "Digite o numero do vertice que deseja mostrar a lista de "
                    "adjacencia: ");
                scanf("%d", &num_vertice);
                print_adj_vertex(num_vertice, grafo);
                break;

            case 5:
                remove_edge_smallest_weight(grafo);
                break;

            case 6:
                printf("O grafo tem %d vertices.\n", number_of_vertexes(grafo));
                break;

            case 7:
                printf(
                    "Digite os numeros dos vertices para verificar se existe "
                    "aresta entre eles: ");
                scanf("%d %d", &num_vertice_1, &num_vertice_2);
                if (exist_edge(num_vertice_1, num_vertice_2, grafo)) {
                    printf("Existe aresta.\n");
                } else {
                    printf("Nao existe aresta.\n");
                }
                break;

            case 0:
                break;

            default:
                printf("Valor invalido.\n");
                break;
        }
    }
    remove_graph(&grafo);

    return 0;
}

