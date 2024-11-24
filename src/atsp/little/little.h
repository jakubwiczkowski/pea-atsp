

#ifndef PEA_ATSP_LITTLE_H
#define PEA_ATSP_LITTLE_H


#include "../algorithm.h"
#include <limits>

/**
 * Typ reprezentujący parę wierzchołków, które
 * razem tworzą krawędź
 */
typedef std::pair<vertex_t, vertex_t> edge_l;

/**
 * Algorytm podziału i ograniczenia
 * zaproponowoany przez Little'a
 */
class little: algorithm {
public:
    solution solve(graph &graph) override;

private:
    /**
     * Aktualnie najmniejszy koszt rozwiązania
     */
    int min_sol = std::numeric_limits<int>::max();

    /**
     * Rekurencyjna funkcja obliczająca najkrótszy
     * możliwy cykl Hamiltona w podanym grafie.
     *
     * @param target graf, w którym ma być znaleziony cykl
     * @param cycle aktualna lista krawędzi w cyklu
     * @param lower_bound dolne ograniczenie rozpatrywanych cykli
     * @param best_solution aktualne najlepsze rozwiązanie problemu
     * @param original_graph oryginalny graf, w którym szukany jest cykl
     */
    void traverse_tree(graph target, std::vector<edge_l> cycle, int lower_bound,
                       solution& best_solution, graph& original_graph);

    /**
     * Funkcja, która przeprowadza redukcje
     * wg. algorytmu Little'a
     *
     * @param to_reduce graf, an którym ma być przeprowadzona redukcja
     * @return zredukowany graf oraz o ile ma się zwiększyć dolne ograniczenie
     */
    std::pair<graph, int> reduce(graph& to_reduce);

    /**
     * Znajduje krawędź, która spowoduje największy
     * wzrost dolnego ograniczenia
     *
     * @param reduced_graph zredukowany graf
     * @return krawędź oraz o ile zwiększy się dolne ograniczenie
     */
    std::pair<edge_l, int> division_pair(graph& reduced_graph);

    /**
     * Generuje lewą podmacierz wg. algorytmu Little'a
     *
     * @param reduced zredukowany graf
     * @param edge krawędź, wg. której ma nastapić generacja
     * @param cycle aktualna lista krawędzi wchodzących w cykl
     * @return lewy podgraf
     */
    graph left_subtree(graph& reduced, edge_l edge, std::vector<edge_l>& cycle);
    /**
     * Generuje prawą podmacierz wg. algorytmu Little'a
     *
     * @param reduced zredukowany graf
     * @param row rząd, wg. którego ma nastapić generacja
     * @param column kolumna, wg. której ma nastapić generacja
     * @return prawy podgraf
     */
    graph right_subtree(graph& reduced, vertex_t row, vertex_t column);

    /**
     * Tworzy ścieżkę Hamiltona z listy krawędzi
     * wchodzących w tą ścieżkę.
     *
     * @param edges krawędzie wchodzące w ścieżkę
     * @return ścieżka Hamiltona
     */
    std::vector<vertex_t> path_from_edge_list(std::vector<edge_l>& edges);
    /**
     * zwraca wszystkie możliwe ścieżki Hamiltona
     * z listy krawędzi wchodzących w te ścieżki.
     *
     * @param edges krawędzie wchodzące w ścieżki
     * @return ścieżki Hamiltona
     */
    std::vector<std::vector<vertex_t>> all_paths_from_edge_list(std::vector<edge_l> &edges);

    /**
     * Zwraca koszt podanego cyklu Hamiltona
     *
     * @param graph graf wg. którego ma być liczony koszt
     * @param path cykl Hamiltona
     * @return koszt cyklu
     */
    int calculate_cost(graph& graph, std::vector<vertex_t>& path);
};


#endif //PEA_ATSP_LITTLE_H
