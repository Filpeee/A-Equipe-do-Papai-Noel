#ifndef GRAFO_HPP
#define GRAFO_HPP

// Número máximo de duendes permitido pelo enunciado.
const int MAX_DUENDES = 40;

/*
 * Estrutura que representa o grafo de conflitos.
 * Cada vértice é um duende e existe uma aresta entre dois vértices
 * caso os duendes correspondentes briguem entre si.
 */
struct Grafo {
    int num_duendes;    
    int num_conflitos;  

    /*
     * Matriz de conflitos:
     * matriz_conflito[i][j] == true  -> duende i e j não podem estar juntos
     * matriz_conflito[i][j] == false -> sem conflito entre i e j
     */
    bool matriz_conflito[MAX_DUENDES][MAX_DUENDES];

    /*
     * Construtor padrão: inicializa a matriz com ausência de conflitos
     * e define contadores como zero.
     */
    Grafo();

    /*
     * Lê a entrada do problema:
     * 1) Lê N e M
     * 2) Lê M pares de duendes em conflito e registra na matriz
     */
    void lerEntrada();

    /*
     * Retorna true se os duendes A e B brigam entre si.
     * Função auxiliar usada na verificação de equipes.
     */
    bool temConflito(int duendeA, int duendeB);
};

#endif