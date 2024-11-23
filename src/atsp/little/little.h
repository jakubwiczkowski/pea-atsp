

#ifndef PEA_ATSP_LITTLE_H
#define PEA_ATSP_LITTLE_H


#include "../algorithm.h"
#include <limits>

typedef std::pair<vertex_t, vertex_t> edge_l;

class little: algorithm {
public:

    solution solve(graph &graph) override;

private:
    int min_sol = std::numeric_limits<int>::max();

    void traverse_tree(graph target, std::vector<edge_l> cycle, int lower_bound,
                       solution& best_solution, graph& original_graph);

    std::pair<graph, int> reduce(graph& to_reduce);

    std::pair<edge_l, int> division_pair(graph& reduced_graph);

    graph left_subtree(graph& reduced, edge_l edge, std::vector<edge_l>& cycle);
    graph right_subtree(graph& reduced, vertex_t row, vertex_t column);

    std::vector<vertex_t> path_from_edge_list(std::vector<edge_l>& edges);
    int calculate_cost(graph& graph, std::vector<vertex_t>& path);
};


#endif //PEA_ATSP_LITTLE_H
