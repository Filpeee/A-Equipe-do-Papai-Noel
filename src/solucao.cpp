#include "../include/solucao.hpp"
#include <iostream>
#include <vector>

// Construtor: inicializa referências e aloca tabela da DP
Solucao::Solucao(Grafo& dados) : grafo(dados) {
    num_total_duendes = grafo.num_duendes;
    ponto_divisao = num_total_duendes / 2;
    num_duendes_grupo1 = ponto_divisao;
    num_duendes_grupo2 = num_total_duendes - num_duendes_grupo1;

    // Tamanho da DP do Grupo 2: 2^(|G2|)
    unsigned int tamanho_dp = 1 << num_duendes_grupo2;
    dp_grupo2.resize(tamanho_dp);

    // Começa sem equipe melhor definida
    melhor_equipe_global.clear();
}

// Executa o algoritmo completo Meet-in-the-Middle
void Solucao::encontrarMelhorEquipe() {
    resolverGrupo2_DP();        // pré-processamento com DP do Grupo 2
    resolverGrupo1_Combinar();  // combinação com Grupo 1
}

// Imprime o resultado final no formato desejado
void Solucao::imprimirResultado() {
    std::cout << melhor_equipe_global.size() << std::endl;

    // Imprime os membros em ordem crescente
    for (unsigned int i = 0; i < melhor_equipe_global.size(); ++i) {
        std::cout << melhor_equipe_global[i];
        if (i < melhor_equipe_global.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

// ETAPA 1: Programação Dinâmica para o Grupo 2
void Solucao::resolverGrupo2_DP() {
    unsigned int num_subconjuntos_g2 = 1 << num_duendes_grupo2;

    dp_grupo2[0] = std::vector<int>(); // Base da DP: conjunto vazio

    // Para cada subconjunto possível de G2
    for (unsigned int mask = 1; mask < num_subconjuntos_g2; ++mask) {

        // Encontra o menor índice ativo na máscara
        int i = 0;
        while (!((mask >> i) & 1)) i++;

        int duende_atual_abs = i + ponto_divisao;
        int bit_i = 1 << i;

        // Opção A: não incluir 'i'
        std::vector<int> equipe_sem_duende = dp_grupo2[mask ^ bit_i];

        // Opção B: incluir 'i', removendo incompatíveis
        unsigned int mask_compativel = mask ^ bit_i;

        for (int j = 0; j < num_duendes_grupo2; ++j) {
            if ((mask_compativel >> j) & 1) {
                int duende_j_abs = j + ponto_divisao;

                if (grafo.temConflito(duende_atual_abs, duende_j_abs)) {
                    mask_compativel &= ~(1 << j);  // Remove do conjunto
                }
            }
        }

        // Monta nova equipe contendo o duende atual
        std::vector<int> equipe_base_compativel = dp_grupo2[mask_compativel];
        std::vector<int> equipe_com_duende;
        equipe_com_duende.push_back(duende_atual_abs);

        for (unsigned int k = 0; k < equipe_base_compativel.size(); ++k) {
            equipe_com_duende.push_back(equipe_base_compativel[k]);
        }

        // Guarda o melhor entre incluir ou excluir
        dp_grupo2[mask] = melhorEquipeLocal(equipe_sem_duende, equipe_com_duende);
    }
}

// ETAPA 2: Testa todas máscaras do Grupo 1 e combina com DP do Grupo 2
void Solucao::resolverGrupo1_Combinar() {
    unsigned int num_subconjuntos_g1 = 1 << num_duendes_grupo1;

    for (unsigned int mask_g1 = 0; mask_g1 < num_subconjuntos_g1; ++mask_g1) {
        
        std::vector<int> equipe_g1;
        bool g1_valida = true;

        // Constrói equipe do Grupo 1 checando conflitos internos
        for (int i = 0; i < num_duendes_grupo1; ++i) {
            if ((mask_g1 >> i) & 1) { // duende presente na máscara
                for (unsigned int j = 0; j < equipe_g1.size(); ++j) {
                    if (grafo.temConflito(i, equipe_g1[j])) {
                        g1_valida = false;
                        break;
                    }
                }
                if (!g1_valida) break;
                equipe_g1.push_back(i);
            }
        }

        if (!g1_valida) continue; // Inválida → próximo subconjunto

        // Máscara permitida inicial de G2: todos disponíveis
        unsigned int mask_permitida_g2 = (1 << num_duendes_grupo2) - 1;

        // Remove incompatíveis com membros de G1
        for (unsigned int i = 0; i < equipe_g1.size(); ++i) {
            int duende_g1 = equipe_g1[i];
            for (int j = 0; j < num_duendes_grupo2; ++j) {
                if ((mask_permitida_g2 >> j) & 1) {
                    int duende_g2_abs = j + ponto_divisao;
                    if (grafo.temConflito(duende_g1, duende_g2_abs)) {
                        mask_permitida_g2 &= ~(1 << j);
                    }
                }
            }
        }

        // Recupera melhor equipe possível do Grupo 2
        std::vector<int> equipe_g2 = dp_grupo2[mask_permitida_g2];

        // Combina as equipes e tenta atualizar melhor solução
        std::vector<int> equipe_total = combinarEquipes(equipe_g1, equipe_g2);
        compararEAtualizarEquipeGlobal(equipe_total);
    }
}

// Funções auxiliares

// Retorna a melhor equipe local entre A e B
std::vector<int> Solucao::melhorEquipeLocal(
    const std::vector<int>& equipeA,
    const std::vector<int>& equipeB) {

    if (equipeA.size() > equipeB.size()) return equipeA;
    if (equipeB.size() > equipeA.size()) return equipeB;

    // Tamanho igual -> comparar lexicograficamente
    for (unsigned int i = 0; i < equipeA.size(); ++i) {
        if (equipeA[i] < equipeB[i]) return equipeA;
        if (equipeB[i] < equipeA[i]) return equipeB;
    }
    return equipeA; // idênticas
}

// Atualiza melhor equipe global se nova é superior
void Solucao::compararEAtualizarEquipeGlobal(
    const std::vector<int>& nova_equipe) {

    if (nova_equipe.size() > melhor_equipe_global.size()) {
        melhor_equipe_global = nova_equipe;
        return;
    }
    if (nova_equipe.size() < melhor_equipe_global.size()) return;

    // Tamanhos iguais -> desempate lexicográfico
    for (unsigned int i = 0; i < nova_equipe.size(); ++i) {
        if (nova_equipe[i] < melhor_equipe_global[i]) {
            melhor_equipe_global = nova_equipe;
            return;
        }
        if (nova_equipe[i] > melhor_equipe_global[i]) return;
    }
}

// Junta dois vetores ordenados 
std::vector<int> Solucao::combinarEquipes(
    const std::vector<int>& equipeA,
    const std::vector<int>& equipeB) {

    std::vector<int> equipe_combinada;
    unsigned int i = 0, j = 0;

    while (i < equipeA.size() && j < equipeB.size()) {
        if (equipeA[i] < equipeB[j]) equipe_combinada.push_back(equipeA[i++]);
        else equipe_combinada.push_back(equipeB[j++]);
    }

    while (i < equipeA.size()) equipe_combinada.push_back(equipeA[i++]);
    while (j < equipeB.size()) equipe_combinada.push_back(equipeB[j++]);

    return equipe_combinada;
}