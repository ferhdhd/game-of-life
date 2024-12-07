# Formulação Matemática do Problema

Seja uma matriz de tamanho \( n \times m \), onde cada célula pode assumir valores binários \( \{0, 1\} \). Modelamos o problema utilizando as seguintes variáveis e funções:

- \( \text{Mat}_{\text{OG}}[i, j] \): Estado da célula \( (i, j) \) na matriz original.
- \( \text{GameMatrix}[i, j] \): Estado da célula \( (i, j) \) na matriz futura (a ser calculada).
- \( \text{NumAlive}(\text{GameMatrix}, i, j) \): Número de vizinhos vivos da célula \( (i, j) \) na matriz futura.

---

## Restrições

Para cada célula \( (i, j) \), definimos as seguintes regras baseadas nos estados \( \text{Mat}_{\text{OG}} \) e \( \text{GameMatrix} \):

1. **Células vivas na matriz original (\( \text{Mat}_{\text{OG}}[i, j] = 1 \))**:
   - A célula permanece viva (\( \text{GameMatrix}[i, j] = 1 \)) se e somente se:
     - Ela estava viva anteriormente **e** tem \( 2 \) ou \( 3 \) vizinhos vivos, ou:
     - Ela estava morta anteriormente e tem exatamente \( 3 \) vizinhos vivos.
   - Formalmente:
     \[
     \text{Mat}_{\text{OG}}[i, j] = 1 \implies 
     \left(
         (\text{GameMatrix}[i, j] = 1 \land (\text{NumAlive}(\text{GameMatrix}, i, j) = 2 \lor \text{NumAlive}(\text{GameMatrix}, i, j) = 3)) 
         \lor (\text{GameMatrix}[i, j] = 0 \land \text{NumAlive}(\text{GameMatrix}, i, j) = 3)
     \right)
     \]

2. **Células mortas na matriz original (\( \text{Mat}_{\text{OG}}[i, j] = 0 \))**:
   - A célula permanece morta (\( \text{GameMatrix}[i, j] = 0 \)) se:
     - Ela estava morta anteriormente e não tem exatamente \( 3 \) vizinhos vivos, ou:
     - Ela estava viva anteriormente, mas não tem \( 2 \) ou \( 3 \) vizinhos vivos.
   - Formalmente:
     \[
     \text{Mat}_{\text{OG}}[i, j] = 0 \implies 
     \left(
         (\text{GameMatrix}[i, j] = 0 \land \text{NumAlive}(\text{GameMatrix}, i, j) \neq 3) 
         \lor (\text{GameMatrix}[i, j] = 1 \land \text{NumAlive}(\text{GameMatrix}, i, j) \notin \{2, 3\})
     \right)
     \]

---

## Domínio das Variáveis

As variáveis \( \text{GameMatrix}[i, j] \) são definidas como variáveis binárias:
\[
\text{GameMatrix}[i, j] \in \{0, 1\}, \quad \forall i \in \{1, \dots, n\}, \, j \in \{1, \dots, m\}
\]

---

## Restrição de Borda

As regras acima são aplicadas apenas às células \( (i, j) \) onde:
\[
1 \leq i \leq n-1 \quad \text{e} \quad 1 \leq j \leq m-1
\]
As células da borda podem ser tratadas como casos especiais ou ignoradas.

---

## Função Objetivo

Minimizar o número total de células vivas na matriz futura:
\[
\text{Minimizar } \sum_{i=1}^{n} \sum_{j=1}^{m} \text{GameMatrix}[i, j]
\]
