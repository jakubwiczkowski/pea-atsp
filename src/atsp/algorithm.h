#ifndef PEA_ATSP_ALGORITHM_H
#define PEA_ATSP_ALGORITHM_H


#include "../graph/graph.h"
#include "solution.h"

/**
 * Klasa reprezentująca algorytm służący
 * do rozwiązania Asymetrycznego Problemu Komiwojażera
 */
class algorithm {
public:
    /**
     * Funkcja rozwiązująca problem Komiwojażera
     * na podanym grafie
     *
     * @param graph graf, w którym ma być znaleziony najkrótszy cykl Hamiltona
     * @return rozwiązanie problemu Komiwojażera
     */
    virtual solution solve(graph& graph) = 0;
};


#endif //PEA_ATSP_ALGORITHM_H
