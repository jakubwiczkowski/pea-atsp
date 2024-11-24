

#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include "graph.h"

graph::graph(uint16_t vertices) {
    this->vertices = vertices;

    this->graph_matrix = new int*[vertices];
    this->deleted_rows = new bool[this->vertices];
    this->deleted_columns = new bool[this->vertices];

    for (int row = 0; row < vertices; ++row) {
        this->graph_matrix[row] = new int[vertices];
        this->deleted_rows[row] = false;
        this->deleted_columns[row] = false;
    }

}

graph::graph(const graph &to_copy) {
    this->vertices = to_copy.get_vertices();

    this->graph_matrix = new int*[this->vertices];
    for (int row = 0; row < this->vertices; ++row) {
        this->graph_matrix[row] = new int[this->vertices];

        for (int column = 0; column < this->vertices; ++column) {
            this->graph_matrix[row][column] = to_copy.get_weight(row, column);
        }
    }

    this->deleted_rows = new bool [this->vertices];
    this->deleted_columns = new bool [this->vertices];

    for (vertex_t u = 0; u < this->vertices; u++) {
        this->deleted_rows[u] = to_copy.is_row_deleted(u);
        this->deleted_columns[u] = to_copy.is_column_deleted(u);
    }
}

graph::~graph() {
    for (vertex_t row = 0; row < get_vertices(); ++row) {
        delete[] this->graph_matrix[row];
    }
    delete[] this->graph_matrix;
    delete[] this->deleted_rows;
    delete[] this->deleted_columns;
}

void graph::set_edge(vertex_t u, vertex_t v, int weight) {
    this->graph_matrix[u][v] = weight;
}

vertex_t graph::get_vertices() const {
    return this->vertices;
}

int graph::get_weight(vertex_t u, vertex_t v) const {
    return this->graph_matrix[u][v];
}

void graph::delete_row(vertex_t row) const {
    this->deleted_rows[row] = true;
}

void graph::delete_column(vertex_t column) const {
    this->deleted_columns[column] = true;
}

bool graph::is_row_deleted(vertex_t row) const {
    return this->deleted_rows[row];
}

bool graph::is_column_deleted(vertex_t column) const{
    return this->deleted_columns[column];
}

void graph::display() {
    std::cout << "    ";
    for (int col = 0; col < this->get_vertices(); ++col) {
        if (is_column_deleted(col)) continue;
        std::cout << std::setw(3) << col << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < this->get_vertices(); i++) {
        if (this->is_row_deleted(i)) continue;
        std::cout << std::setw(3) << i << " ";
        for (int j = 0; j < this->get_vertices(); j++) {
            if (this->is_column_deleted(j)) continue;
            std::cout << std::setw(3) << this->graph_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<vertex_t> graph::generate_vertex_list() const {
    std::vector<vertex_t> vertices;

    for (vertex_t i = 0; i < get_vertices(); ++i) {
        vertices.push_back(i);
    }

    return vertices;
}

graph graph::generate_random_full(uint16_t vertices) {
    static std::random_device r;
    static std::default_random_engine e1(r());
    static std::uniform_int_distribution<int> uniform_dist_weight(1, 500);

    auto generated = graph(vertices);

    for (vertex_t u = 0; u < vertices; u++) {
        for (vertex_t v = 0; v < vertices; v++) {
            if (u == v) {
                generated.set_edge(u, v, -1);
                continue;
            }

            generated.set_edge(u, v, uniform_dist_weight(e1));
        }
    }

    return generated;
}

int graph::degree() {
    int value = this->vertices;

    for (int i = 0; i < this->vertices; i++) {
        if (this->is_column_deleted(i)) value--;
    }

    return value;
}
