# A Equipe do Papai Noel

## Sobre o Projeto
O objetivo deste projeto é selecionar a maior equipe possível de duendes para o Natal, garantindo que nenhum par selecionado possua relações de rivalidade. Em caso de empate, a equipe escolhida deve ser lexicograficamente menor.

## Algoritmos e Estruturas de Dados
O desafio é uma variação do clássico problema do Conjunto Independente Máximo (NP-difícil) aplicado a um grafo não direcionado com até 40 vértices.
* **Matriz de Adjacência:** Utilizada para checagem de conflitos em tempo constante O(1).
* **Meet-in-the-Middle:** Para contornar a limitação da força bruta O(2^N), o conjunto foi dividido pela metade.
* **Programação Dinâmica com Bitmask:** Utilizada para pré-calcular e armazenar as melhores equipes possíveis do segundo subgrupo, otimizando as combinações finais.

## Complexidade
* A aplicação da técnica Meet-in-the-Middle reduziu a complexidade de tempo e memória para O(N * 2^(N/2)).
