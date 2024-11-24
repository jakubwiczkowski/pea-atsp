

#ifndef PEA_ATSP_DYNAMIC_H
#define PEA_ATSP_DYNAMIC_H


#include "../algorithm.h"
#include <limits>
#include <utility>

/**
 * Algorytm dynamicznego programowania
 * Helda-Karpa
 */
class dynamic: algorithm {
public:
    solution solve(graph &graph) override;

private:
    /**
     * Funkcja znajdująca najmniejszy koszt
     * cyklu Hamiltona w podanym grafie
     *
     * @param graph docelowy graf
     * @param mask
     * @param pos
     * @param dp
     * @param next_vertex
     * @return
     */
    int find_solution(graph &graph, int mask, vertex_t pos,
                      std::vector<std::vector<int>> &dp,
                      std::vector<std::vector<vertex_t>> &next_vertex);
};


#endif //PEA_ATSP_DYNAMIC_H
