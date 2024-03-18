# Graphs
## Getting Started

This program is designed to perform various operations on a graph data structure. It allows you to add vertices and edges, remove edges, display information about the graph, and more.

### Run

You can compile and execute the program manually through the Makefile provided.

1. Give permission for the script to become executable:

    ```bash
    make
    ```

2. Execute the program using the following command:

    ```bash
    make run
    ```

Alternatively, you can use the provided shell script to run all test cases present in the test folder and indicate which cases passed.

1. Compile and run the program using the provided Makefile:

    ```bash
    sudo chmod +x runTests.sh
    ```

2. Execute the test cases:

    ```bash
    ./runTests.sh
    ```


### Implementação do TAD Grafos
Um TAD para grafos foi implementado com todas as funcionalidades requeridas, permitindo a criação de um grafo com N vértices, adição de vértices e arestas, além da verificação da existência de arestas, entre outras funcionalidades.

As arestas dos grafos possuem pesos, o que possibilita a implementação de uma função que remove a aresta de menor peso do grafo. O valor -1 indica a inexistência de uma aresta.

O grafo foi implementado usando uma matriz de adjacência, devido à sua eficiência para adicionar e verificar arestas, bem como pela sua simplicidade. Um sistema que registra os números de cada vértice e sua ordem/index de inserção é utilizado, de modo que a matriz não precisa ter o tamanho do número do vértice adicionado.

Por exemplo: Um grafo com vértices [1,2,3] terá um novo vértice de número 10 adicionado. Então, a lista de vértices será [1,2,3,10], e o vértice 10 será indexado na matriz na linha e coluna de número 3. Dessa forma, a matriz cresce de 3x3 para 4x4, e não para 10x10.

### Como Usar
Uma vez que o programa esteja em execução, siga as instruções do menu na tela para interagir com o grafo. Você pode adicionar vértices, adicionar arestas entre vértices, remover arestas, exibir informações sobre o grafo e realizar várias outras operações.

## Casos de Teste
Todos os casos de teste estão localizados na pasta de testes. Você pode executá-los usando o script de shell fornecido (runTests.sh).

## Autores

| Nomes                         |    NUSP    |
| :---------------------------  | ---------- |
| Cauê Paiva Lira               | 14675416   |
| Letícia Barbosa Neves         | 14588659   |
| Luiz Felipe Diniz Costa       | 13782032   |
| Pedro Louro Fernandes         | 13672446   |
| João Pedro Alves Notari Godoy | 14582076   |


