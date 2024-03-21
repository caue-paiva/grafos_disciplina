# Grafos

### Implementação do TAD Grafos
Um TAD para grafos foi implementado com todas as funcionalidades requeridas, permitindo a criação de um grafo com N vértices, adição de vértices e arestas, além da verificação da existência de arestas, entre outras funcionalidades.

As arestas dos grafos possuem pesos, o que possibilita a implementação de uma função que remove a aresta de menor peso do grafo. O valor -1 indica a inexistência de uma aresta.

O grafo foi implementado usando uma matriz de adjacência, devido à sua eficiência para adicionar e verificar arestas, bem como pela sua simplicidade. Um sistema que registra os números de cada vértice e sua ordem/index de inserção é utilizado, de modo que a matriz não precisa ter o tamanho do número do vértice adicionado.

Por exemplo: Um grafo com vértices [1,2,3] terá um novo vértice de número 10 adicionado. Então, a lista de vértices será [1,2,3,10], e o vértice 10 será indexado na matriz na linha e coluna de número 3. Dessa forma, a matriz cresce de 3x3 para 4x4, e não para 10x10.

OBS: A contagem dos vértices começa do 1, então ao criar um grafo com 3 vértices, vão ser criado os vértices 1,2 e 3

### Como Usar

**Makefile**:

```bash
make grafos  #vai compilar o programa
```

```bash
make run  #vai executar o programa
```

Uma vez que o programa esteja em execução, siga as instruções do menu na tela para interagir com o grafo. Você pode adicionar vértices, adicionar arestas entre vértices, remover arestas, exibir informações sobre o grafo e realizar várias outras operações.

## Casos de Teste
Todos os casos de teste estão localizados na pasta de testes. Você pode executá-los usando o comando:

```bash
./grafos < 1.in #ou o 2.in
```

## Autores

| Nomes                         |    NUSP    |
| :---------------------------  | ---------- |
| Cauê Paiva Lira               | 14675416   |
| Letícia Barbosa Neves         | 14588659   |
| Luiz Felipe Diniz Costa       | 13782032   |
| João Pedro Alves Notari Godoy | 14582076   |
| Yvis Freire Silva Santos      | 12608793   |


