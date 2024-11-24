#ifndef PEA_ATSP_GRAPH_H
#define PEA_ATSP_GRAPH_H


#include <cstdint>
#include <vector>
#include <set>
#include "../type/types.h"

/**
 * Klasa reprezentująca graf w postaci
 * macierzy sąsiedztwa
 */
class graph {
private:
    /**
     * Ilość wierzchołków w grafie
     */
    uint16_t vertices;

    /**
     * Macierz sąsiedztwa
     */
    int** graph_matrix;

    /**
     * Usunięte rzędy (używane przy algorytmie Little'a)
     */
    bool* deleted_rows;
    /**
     * Usunięte kolumny (używane przy algorytmie Little'a)
     */
    bool* deleted_columns;
public:
    explicit graph(uint16_t vertices);
    graph(const graph& to_copy);

    ~graph();

    /**
     * Funkcja odpowiedzialna za ustawienie podanej wagi
     * na krawędzi (u, v)
     *
     * @param u początek krawędzi
     * @param v koniec krawędzi
     * @param weight waga krawędzi
     */
    void set_edge(vertex_t u, vertex_t v, int weight);

    /**
     * Zwraca ilość wierzchołków w grafie
     *
     * @return ilość wierzchołków w grafie
     */
    [[nodiscard]] uint16_t get_vertices() const;
    /**
     * Zwraca wagę danej krawędzi
     *
     * @param u początek krawędzi
     * @param v koniec krawędzi
     * @return waga krawędzi
     */
    [[nodiscard]] int get_weight(vertex_t u, vertex_t v) const;

    /**
     * Tworzy wektor zawierający listę wszystkich
     * wierzchołków
     *
     * @return lista wszystkich wierzchołków
     */
    [[nodiscard]] std::vector<vertex_t> generate_vertex_list() const;

    /**
     * Usuwa dany rząd z grafu
     *
     * @param row rząd do usunięcia
     */
    void delete_row(vertex_t row) const;
    /**
     * Usuwa daną kolumnę z grafu
     *
     * @param column kolumna do usunięcia
     */
    void delete_column(vertex_t column) const;

    /**
     * Zwraca, czy dany rząd został usunięty z grafu
     *
     * @param row sprawdzany rząd
     * @return czy sprawdzany rząd został usunięty
     */
    bool is_row_deleted(vertex_t row) const;
    /**
     * Zwraca, czy dana kolumna została usunięta z grafu
     *
     * @param column sprawdzana kolumna
     * @return czy sprawdzana kolumna została usunięta
     */
    bool is_column_deleted(vertex_t column) const;

    /**
     * Zwraca rząd macierzy
     *
     * @return rząd macierzy
     */
    int degree();

    /**
     * Wyświetla graf w postaci macierzowej
     */
    void display();

    /**
     * Generuje losowy graf pełny o
     * danej liczbie wierzchołków
     *
     * @param vertices ilość wierzchołków w grafie
     * @return graf pełny
     */
    static graph generate_random_full(uint16_t vertices);
};


#endif //PEA_ATSP_GRAPH_H
