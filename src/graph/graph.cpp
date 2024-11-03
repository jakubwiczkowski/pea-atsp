

#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include "graph.h"

graph::graph(uint16_t vertices) {
    this->vertices = vertices;

    this->graph_matrix = new int*[vertices];
    for (int row = 0; row < vertices; ++row) {
        this->graph_matrix[row] = new int[vertices];
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
}

graph::~graph() {
    for (vertex_t row = 0; row < get_vertices(); ++row) {
        delete[] this->graph_matrix[row];
    }
    delete[] this->graph_matrix;
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

void graph::display() {
    for (int i = 0; i < this->get_vertices(); i++) {
        for (int j = 0; j < this->get_vertices(); j++) {
            std::cout << std::setw(3) << this->graph_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<vertex_t> graph::get_adjacent(uint16_t vertex) {
    std::vector<vertex_t> adjacent;
    for (vertex_t possible_adjacent = 0; possible_adjacent < this->get_vertices(); ++possible_adjacent) {
        if (this->get_weight(vertex, possible_adjacent) <= 0) continue;
        adjacent.push_back(possible_adjacent);
    }
    return adjacent;
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
