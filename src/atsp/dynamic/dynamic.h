

#ifndef PEA_ATSP_DYNAMIC_H
#define PEA_ATSP_DYNAMIC_H


#include "../algorithm.h"
#include <limits>
#include <utility>

struct node {
    int value = std::numeric_limits<int>::max();
    vertex_t vertex;
    std::vector<vertex_t> vertex_list;

    node* min_node = nullptr;

    node(vertex_t vertex, std::vector<vertex_t> vertex_list) {
        this->vertex = vertex;
        this->vertex_list = std::move(vertex_list);
    };
};

class dynamic: algorithm {
public:
    solution solve(graph &graph) override;

private:
    int find_solution(graph &graph, int mask, vertex_t pos, std::vector<std::vector<int>> &dp, std::vector<std::vector<vertex_t>> &next_vertex);
};


#endif //PEA_ATSP_DYNAMIC_H
