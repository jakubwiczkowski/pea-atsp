#ifndef PEA_ATSP_GRAPH_H
#define PEA_ATSP_GRAPH_H


#include <cstdint>
#include <vector>
#include <set>
#include "../type/types.h"

class graph {
private:
    uint16_t vertices;

    int** graph_matrix;

    bool* deleted_rows;
    bool* deleted_columns;
public:
    explicit graph(uint16_t vertices);
    graph(const graph& to_copy);

    ~graph();

    void set_edge(vertex_t u, vertex_t v, int weight);

    std::vector<uint16_t> get_adjacent(vertex_t vertex);

    [[nodiscard]] uint16_t get_vertices() const;
    [[nodiscard]] int get_weight(vertex_t u, vertex_t v) const;

    [[nodiscard]] std::vector<vertex_t> generate_vertex_list() const;

    void delete_row(vertex_t row) const;
    void delete_column(vertex_t column) const;

    bool is_row_deleted(vertex_t row) const;
    bool is_column_deleted(vertex_t column) const;

    int degree();

    void display();

    static graph generate_random_full(uint16_t vertices);
};


#endif //PEA_ATSP_GRAPH_H
