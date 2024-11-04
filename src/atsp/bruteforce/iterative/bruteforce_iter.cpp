

#include "bruteforce_iter.h"
#include <limits>

solution bruteforce_iter::solve(graph &graph) {
    std::vector<vertex_t> vertices = graph.generate_vertex_list();

    return permute(graph, vertices);
}

solution bruteforce_iter::permute(graph& graph, std::vector<vertex_t> &vertices) {
    solution best_solution;
    best_solution.weight = std::numeric_limits<int>::max();
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
        int weight = calculate_weight(graph, current_permutation);

        if (best_solution.weight > weight) {
            best_solution.weight = weight;
            current_permutation.push_back(current_permutation[0]);
            best_solution.vertices = current_permutation;
        }

        // sprawdzanie posortowania niemalejacego
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

    return best_solution;
}

int bruteforce_iter::calculate_weight(graph& graph, std::vector<vertex_t> &permutation) {
    int final_weight = 0;
    for (int i = 0; i < permutation.size() - 1; ++i) {
        int weight = graph.get_weight(permutation[i], permutation[i+1]);
        final_weight += weight;
    }
    final_weight += graph.get_weight(permutation[permutation.size() - 1], permutation[0]);

    return final_weight;
}
