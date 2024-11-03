

#include "bruteforce_iter.h"
#include <limits>

solution bruteforce_iter::solve(graph &graph) {
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

permutations_t bruteforce_iter::permute(std::vector<vertex_t> &vertices) {
    permutations_t result;
    int n = vertices.size();
    std::vector<int> indices(n);
    for (int i = 0; i < n; ++i) {
        indices[i] = i;
    }

    while (true) {
        std::vector<vertex_t> current_permutation(n);
        for (int i = 0; i < n; ++i) {
            current_permutation[i] = vertices[indices[i]];
        }
        result.push_back(current_permutation);

        int i = n - 1;
        while (i > 0 && indices[i - 1] >= indices[i]) {
            --i;
        }
        if (i <= 0) {
            break;
        }

        int j = n - 1;
        while (indices[j] <= indices[i - 1]) {
            --j;
        }

        std::swap(indices[i - 1], indices[j]);

        j = n - 1;
        while (i < j) {
            std::swap(indices[i], indices[j]);
            ++i;
            --j;
        }
    }

    return result;
}