#include "dynamic.h"
#include <vector>

solution dynamic::solve(graph &graph) {
    int n = graph.get_vertices();
    std::vector<std::vector<int>> dp(1 << n, std::vector<int>(n, std::numeric_limits<int>::max()));
    std::vector<std::vector<vertex_t>> next_vertex(1 << graph.get_vertices(),
                                                   std::vector<vertex_t>(graph.get_vertices(), -1));

    int answer = find_solution(graph, 1, 0, dp, next_vertex);

    std::vector<vertex_t> path;
    path.push_back(0);
    int mask = 1;
    vertex_t pos = 0;
    while (mask != (1 << graph.get_vertices()) - 1) {
        vertex_t next = next_vertex[mask][pos];
        path.push_back(next);
        mask |= (1 << next);
        pos = next;
    }
    path.push_back(0);

    return {path, answer};
}

int dynamic::find_solution(graph &graph, int mask, vertex_t pos,
                           std::vector<std::vector<int>> &dp,
                           std::vector<std::vector<vertex_t>> &next_vertex) {
    int VISITED_ALL = (1 << graph.get_vertices()) - 1;

    if (mask == VISITED_ALL) return graph.get_weight(pos, 0);

    if (dp[mask][pos] != std::numeric_limits<int>::max()) return dp[mask][pos];

    int answer = std::numeric_limits<int>::max();

    for (vertex_t target = 0; target < graph.get_vertices(); ++target) {
        if (target == pos) continue;
        if ((mask & (1 << target)) == 0) {
            int new_answer = graph.get_weight(pos, target) +
                             find_solution(graph, mask | (1 << target), target, dp, next_vertex);
            if (new_answer < answer) {
                answer = new_answer;
                next_vertex[mask][pos] = target;
            }
        }
    }

    return dp[mask][pos] = answer;
}