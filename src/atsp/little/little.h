

#ifndef PEA_ATSP_LITTLE_H
#define PEA_ATSP_LITTLE_H


#include "../algorithm.h"

typedef std::pair<vertex_t, vertex_t> edge_l;

class little: algorithm {
public:

    solution solve(graph &graph) override;

private:
    std::tuple<std::vector<edge_l>, int, int> step(graph& target, std::vector<edge_l> edges, int lower_bound, int upper_bound);

    std::pair<graph*, int> reduce(graph& to_reduce);

    std::pair<edge_l, int> division_pair(graph& reduced_graph);

    graph* left_subtree(graph& reduced, vertex_t row, vertex_t column);
    graph* right_subtree(graph& reduced, vertex_t row, vertex_t column);
};


#endif //PEA_ATSP_LITTLE_H
