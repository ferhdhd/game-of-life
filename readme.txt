Trabalho - IA
Pedro Willian Aguiar - GRR20211766
Fernando Gbur dos Santos - GRR20211761

# Contexto

Para resolver o problema foi usado Z3 que é um solver SMT (Satisfiability Modulo Theories). Ele combina técnicas de satisfatibilidade proposicional (SAT) com métodos específicos para cada teoria

No contexto deste projeto, o Z3 é usado para modelar uma matriz onde cada célula é uma variável com possíveis estados (0 ou 1). Restrições baseadas em vizinhança e regras de transição são aplicadas, enquanto uma função de otimização minimiza o número de células vivas na próxima configuração. Isso demonstra a capacidade do Z3 de lidar com restrições e critérios de otimização de forma integrada.

# Utilização Z3

Para instalação e configuração, basta rodar o seguinte comando:

`sudo apt-get install libz3-dev`

ou 

`sudo apt-get install z3`

# Formulação do Problema

Seja uma matriz `n x m`, onde cada célula pode assumir valores `0` ou `1`. As restrições e o objetivo são definidos com base no seguinte:

---

## Restrições

1. **Para células vivas na matriz original (`Mat_OG[i, j] = 1`):**
   - A célula permanece viva (`GameMatrix[i, j] = 1`) se:
     - Ela estava viva anteriormente **e** o número de vizinhos vivos é igual a `2` ou `3`, ou:
     - Ela estava morta anteriormente **e** o número de vizinhos vivos é exatamente `3`.

   Formalmente:
    Mat_OG[i, j] = 1 => (GameMatrix[i, j] = 1 AND (NumAlive[i, j] = 2 OR NumAlive[i, j] = 3)) OR (GameMatrix[i, j] = 0 AND NumAlive[i, j] = 3)


2. **Para células mortas na matriz original (`Mat_OG[i, j] = 0`):**
- A célula permanece morta (`GameMatrix[i, j] = 0`) se:
  - Ela estava morta anteriormente **e** o número de vizinhos vivos é diferente de `3`, ou:
  - Ela estava viva anteriormente **e** o número de vizinhos vivos não é `2` ou `3`.

    Formalmente:
    Mat_OG[i, j] = 0 => (GameMatrix[i, j] = 0 AND NumAlive[i, j] != 3) OR (GameMatrix[i, j] = 1 AND NumAlive[i, j] != 2 AND NumAlive[i, j] != 3)


3. **Domínio das variáveis:**
Cada célula na matriz futura (`GameMatrix[i, j]`) assume valores binários:

GameMatrix[i, j] ∈ {0, 1}, para todo i, j


---

## Função Objetivo

Minimizar o número total de células vivas na próxima matriz (`GameMatrix`):

Minimizar Σ GameMatrix[i, j], para todo i, j (ou seja, minimizar o somatório das células vivas)


---

## Observações

- `NumAlive[i, j]`: Número de vizinhos vivos ao redor da célula `(i, j)`.
- As restrições são aplicadas apenas às células internas da matriz (`1 ≤ i ≤ n-1` e `1 ≤ j ≤ m-1`). As células da borda são ignoradas.

