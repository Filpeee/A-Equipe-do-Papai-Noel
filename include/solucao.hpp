#ifndef SOLUCAO_HPP
#define SOLUCAO_HPP

#include "grafo.hpp"
#include <vector>

/*
 * Classe responsável pela resolução completa do problema.
 * Implementa o algoritmo Meet-in-the-Middle combinado com Programação Dinâmica.
 */
class Solucao {
public:

    /*
     * Construtor: recebe a estrutura de grafo contendo os dados lidos.
     * Inicializa variáveis auxiliares e aloca a tabela dp_grupo2.
     */
    Solucao(Grafo& dados);

    /*
     * Método principal da solução:
     * 1) Calcula via DP o melhor conjunto possível do Grupo 2.
     * 2) Itera por todos subconjuntos do Grupo 1 e combina com resultados do Grupo 2.
     */
    void encontrarMelhorEquipe();

    /*
     * Imprime o resultado final:
     * - primeira linha: tamanho da equipe
     * - segunda linha: índices em ordem crescente
     */
    void imprimirResultado();

private:

    // --- Dados de controle ---
    Grafo& grafo;              // Referência ao grafo de entrada
    int num_total_duendes;     // N total
    int ponto_divisao;         // N/2 (divisão entre os grupos)
    int num_duendes_grupo1;    // Tamanho do Grupo 1
    int num_duendes_grupo2;    // Tamanho do Grupo 2

    // Vetor que guarda a melhor equipe global encontrada
    std::vector<int> melhor_equipe_global;

    /*
     * Tabela de Programação Dinâmica:
     * dp_grupo2[mask] -> melhor equipe (vetor) correspondente à máscara analisada.
     */
    std::vector<std::vector<int>> dp_grupo2;

    // --- Funções auxiliares internas ---

    // Etapa 1: Preenche dp_grupo2 usando Programação Dinâmica
    void resolverGrupo2_DP();

    // Etapa 2: Itera sobre todas máscaras do Grupo 1 e combina resultados
    void resolverGrupo1_Combinar();
    
    /*
     * Atualiza melhor_equipe_global se nova_equipe for melhor.
     * Critérios de comparação definidos pelo problema:
     * - maior tamanho
     * - ou, em empate, lexicograficamente menor
     */
    void compararEAtualizarEquipeGlobal(const std::vector<int>& nova_equipe);

    /*
     * Retorna a melhor equipe entre A e B seguindo mesmos critérios de comparação.
     * Usado internamente pela DP do Grupo 2.
     */
    std::vector<int> melhorEquipeLocal(const std::vector<int>& equipeA,
                                       const std::vector<int>& equipeB);

    /*
     * Verifica se existe conflito interno dentro de um vetor de duendes.
     * Útil na validação de máscaras do Grupo 1 antes da combinação.
     */
    bool temConflitoInterno(const std::vector<int>& equipe);
    
    /*
     * Junta duas equipes (ordenadas) em uma só.
     */
    std::vector<int> combinarEquipes(const std::vector<int>& equipeA,
                                     const std::vector<int>& equipeB);
};

#endif