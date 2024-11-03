

#include <algorithm>
#include <limits>
#include <iostream>
#include "bruteforce_rec.h"

solution bruteforce_rec::solve(graph &graph) {
    std::vector<vertex_t> vertices = graph.generate_vertex_list();
    solution best_solution;
    best_solution.weight = std::numeric_limits<int>::max();

    permutations_t permutations = permute(vertices);

    int n = 0;
    for (const auto& permutation : permutations) {
        int final_weight = 0;
        n++;
        for (int i = 0; i < permutation.size() - 1; ++i) {
            int weight = graph.get_weight(permutation[i], permutation[i+1]);
            final_weight += weight;
        }
        final_weight += graph.get_weight(permutation[permutation.size() - 1], permutation[0]);

        if (final_weight < best_solution.weight) {
            best_solution.weight = final_weight;
            std::vector<vertex_t> new_best = permutation;
            new_best.push_back(permutation[0]);
            best_solution.vertices = new_best;
        }
    }

    return best_solution;
}


permutations_t bruteforce_rec::permute(std::vector<vertex_t>& vertices) {
    permutations_t result;
    permutations(result, vertices, 0);

    return result;
}

void bruteforce_rec::permutations(permutations_t &result, std::vector<vertex_t> vertices, int idx) {
    if (idx == vertices.size()) {
        result.push_back(vertices);
        return;
    }

    for (int i = idx; i < vertices.size(); i++) {
        std::swap(vertices[idx], vertices[i]);
        permutations(result, vertices, idx + 1);
        std::swap(vertices[idx], vertices[i]);
    }
}
