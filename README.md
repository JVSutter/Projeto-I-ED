### PROJETO I - Estruturas de Dados (INE5408)

Este projeto consiste na utilização de estruturas lineares, vistas até o momento no curso, e aplicação de conceitos de pilha e/ou fila para o processamento de arquivos XML contendo matrizes binárias que representam cenários de ação de um robô aspirador. A implementação deverá resolver dois problemas (listados a seguir), e os resultados deverão ser formatados em saída padrão de tela de modo que possam ser automaticamente avaliados no VPL.


## Primeiro problema: validação de arquivo XML

Para esta parte, pede-se exclusivamente a verificação de aninhamento e fechamento das marcações (tags) no arquivo XML (qualquer outra fonte de erro pode ser ignorada). Se houver um erro de aninhamento, deve se impresso erro na tela. Um identificador constitui uma marcação entre os caracteres < e >, podendo ser de abertura (por exemplo: `<cenario>`) ou de fechamento com uma / antes do identificador (por exemplo: `</cenario>`). Como apresentando em sala de aula, o algoritmo para resolver este problema é baseado em pilha (LIFO):

- Ao encontrar uma marcação de abertura, empilha o identificador
- Ao encontrar uma marcação de fechamento, verifica se o topo da pilha tem o mesmo identificador e desempilha. Aqui duas situações de erro podem ocorrer:
- - Ao consultar o topo, o identificador é diferente (ou seja, uma marcação aberta deveria ter sido fechada antes)
- - Ao consultar o topo, a pilha encontra-se vazia (ou seja, uma marcação é fechada sem que tenha sido aberta antes)
- Ao finalizar a análise (parser) do arquivo, é necessário que a pilha esteja vazia. Caso não esteja, mais uma situação de erro ocorre, ou seja, há marcação sem fechamento

## Segundo problema: determinação de área do espaço que o robô deve limpar

Cada XML, contém matrizes binárias, com altura e largura, definidas respectivamente pelas marcações `<altura>` e `<largura>`, e sequência dos pontos, em modo texto, na marcação `<matriz>`. Cada ponto corresponde a uma unidade de área, sendo 0 para não pertencente ou 1 para pertencente ao espaço que deve ser limpo, com passo mínimo do robô em uma de quatro direções possíveis (vizinhança-4). Para cada uma dessas matrizes, pretende-se determinar a área (quantidade de pontos iguais a 1 na região do robô) que deve ser limpa, conforme a posição inicial, linha `<x>` e coluna `<y>`, do robô (primeira linha e primeira coluna são iguais a zero). Para isso, seguem algumas definições importantes:

- A **vizinhança-4** de um ponto na linha x e coluna y, ou seja, na coordenada (x, y), é um conjunto de pontos adjacentes nas coordenadas:
  - (x - 1, y)
  - (x + 1, y)
  - (x, y - 1)
  - (x, y + 1)

- Um **caminho** entre um um ponto p<sub>a</sub> e outro p<sub>b</sub> é uma sequência de pontos distintos p<sub>1</sub>, p<sub>2</sub>, ..., p<sub>n</sub></sub>, de modo que p<sub>i</sub> é vizinho-4 de p<sub>i+1</sub>, sendo i = 1, 2, ..., n - 1

- Um ponto p é **conexo** a um ponto q se existir um caminho de p a q (no contexto deste trabalho, só há interesse em pontos com valor 1, ou seja, pertencentes ao espaço a ser limpo)

- Um **componente conexo** é um conjunto maximal (não há outro maior que o contenha) C de pontos, no qual quaisquer dois pontos selecionados deste conjunto C são conexos

Para a determinação da área a ser limpa, é necessário identificar quantos pontos iguais a 1 estão na região em que o robô se encontra, ou seja, é preciso determinar a área do componente conexo. Conforme apresentado em aula, segue o algoritmo de reconstrução de componente conexo usando uma fila (FIFO):

1. Criar uma matriz R de 0 (zeros) com o mesmo tamanho da matriz de entrada E lida
2. Inserir (x,y) da imagem R, atribuir 1
3. Enquanto a fila não estiver vazia
   - (x,y) ← remover da fila
   - inserir na fila as coordenadas dos quatro vizinhos que estejam dentro do domínio da matriz (não pode ter coordenada negativa ou superar o número de linhas ou de colunas), com intensidade 1 (em E) e ainda não tenha sido visitado (igual a 0 em R)
     - na coordenada de cada vizinho selecionado, na imagem R, atribuir 1

O conteúdo final da matriz R corresponde ao resultado da reconstrução. A quantidade de 1 (uns) deste único componente conexo é a resposta do segundo problema.
