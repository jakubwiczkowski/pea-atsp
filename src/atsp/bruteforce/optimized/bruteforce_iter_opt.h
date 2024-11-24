

#ifndef PEA_ATSP_BRUTEFORCE_ITER_OPT_H
#define PEA_ATSP_BRUTEFORCE_ITER_OPT_H


#include "../../algorithm.h"

/**
 * Algorytm przeszukiwania zupełnego
 */
class bruteforce_iter_opt: algorithm {
public:
    solution solve(graph &graph) override;

private:
    /**
     * Funkcja obliczająca wszystkie permutacje
     * listy wierzchołków
     *
     * @param graph docelowy graf
     * @param vertices lista wierzchołków
     * @return optymalne rozwiązanie problemu Komiwojażera
     */
    static solution permute(graph& graph, std::vector<vertex_t>& vertices);
    /**
     * Funkcja licżaca koszt cyklu Hamiltona
     *
     * @param graph docelowy graf
     * @param permutation cykl Hamiltona
     * @return koszt cyklu Hamiltona
     */
    static int calculate_weight(graph& graph, std::vector<vertex_t>& permutation);
};


#endif //PEA_ATSP_BRUTEFORCE_ITER_OPT_H
