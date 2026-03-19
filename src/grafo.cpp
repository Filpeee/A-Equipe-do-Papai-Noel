#include "../include/grafo.hpp"
#include <iostream> 

// Construtor: inicializa o grafo sem conflitos
Grafo::Grafo() {
    num_duendes = 0;
    num_conflitos = 0;

    // Inicializa toda a matriz com 'false', garantindo estado limpo
    for (int i = 0; i < MAX_DUENDES; ++i) {
        for (int j = 0; j < MAX_DUENDES; ++j) {
            matriz_conflito[i][j] = false;
        }
    }
}

// Lê a entrada: número total de duendes e relações de conflito
void Grafo::lerEntrada() {
    std::cin >> num_duendes >> num_conflitos;

    // Lê M pares (u,v) e marca ambos os lados,
    // pois o grafo é não direcionado
    for (int k = 0; k < num_conflitos; ++k) {
        int duendeA, duendeB;
        std::cin >> duendeA >> duendeB;

        matriz_conflito[duendeA][duendeB] = true;
        matriz_conflito[duendeB][duendeA] = true;
    }
}

// Retorna true se houver briga entre A e B
bool Grafo::temConflito(int duendeA, int duendeB) {
    return matriz_conflito[duendeA][duendeB];
}