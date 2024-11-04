

#ifndef PEA_ATSP_DYNAMIC_H
#define PEA_ATSP_DYNAMIC_H


#include "../algorithm.h"
#include <limits>
#include <utility>

class dynamic: algorithm {
public:
    solution solve(graph &graph) override;

private:
    int find_solution(graph &graph, int mask, vertex_t pos,
                      std::vector<std::vector<int>> &dp,
                      std::vector<std::vector<vertex_t>> &next_vertex);
};


#endif //PEA_ATSP_DYNAMIC_H
