#include "graph.h"

int main() {

    Graph *grafo = graph_create(); // criação do grafo
    int opcao = 0;
    while(opcao >= 0) {
        printf("OPCOES\n");
        printf("0 - adicionar vertice\n1 - adicionar aresta\n2 - remover aresta\n");
        printf("3 - mostrar vértices e arestas\n4 - mostrar lista de vertices adjacentes a um vertice\n");
        printf("5 - remover vertice de menor peso\n6 - numero de vertices\n7 - existe aresta\n");
        printf("8 - sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

            int num_vertice;
            int num_vertice_1;
            int num_vertice_2;

        switch (opcao) {

            case 0:
                printf("Digite o numero do vertice que deseja adicionar: ");
                scanf("%d", &num_vertice);
                add_vertex(num_vertice, grafo);
                break;

            case 1:

                int weight;
                printf("Digite o numero dos vertices que deseja adicionar uma aresta: ");
                scanf("%d", &num_vertice_1);
                scanf("%d", &num_vertice_2);
                printf("Digite o peso da aresta: ");
                scanf("%d", &weight);
                add_edge(num_vertice_1, num_vertice_2, weight, grafo);
                break;

            case 2:

                printf("Digite o numero dos vertices que deseja remover uma aresta: ");
                scanf("%d", &num_vertice_1);
                scanf("%d", &num_vertice_2);
                remove_edge(num_vertice_1, num_vertice_2, grafo);
                break;

            case 3:
                print_info(grafo);
                break;

            case 4:
                printf("Digite o numero do vertice que deseja mostrar a lista de adjacencia: ");
                scanf("%d", &num_vertice);
                print_adj_vertex(num_vertice, grafo);
                break;

            case 5:
                remove_edge_smallest_weight(grafo);
                break;

            case 6:
                printf("O grafo tem %d vertices", number_of_vertexes(grafo));
                break;
            
            case 7:
                printf("Digite o numero dos vertices para verificar se existe aresta entre eles: ");

                if (exist_edge(num_vertice_1, num_vertice_2, grafo)) {
                    printf("Existe.\n");
                } else {
                    printf("Nao existe.\n");
                }
                break;

            case 8:
                opcao = -1;
                break;
            
            default:
                printf("Valor invalido.\n");
                break;
        }
    }








    






    return 0;
}