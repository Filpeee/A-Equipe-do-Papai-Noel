#include <iostream>
#include <vector>     

#include "../include/grafo.hpp"
#include "../include/solucao.hpp" 

int main() {
    // Objeto que representa o grafo contendo os duendes e seus conflitos
    Grafo dados_problema;

    // Lê a entrada padrão no formato especificado pelo enunciado
    dados_problema.lerEntrada();

    // Instancia o resolvedor da solução (algoritmo Meet-in-the-Middle)
    Solucao resolvedor(dados_problema);

    // Executa o algoritmo principal para encontrar a melhor equipe
    resolvedor.encontrarMelhorEquipe();

    // Exibe o resultado final no formato pedido
    resolvedor.imprimirResultado();

    return 0;
}