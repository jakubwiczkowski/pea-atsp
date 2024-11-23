

#include "little.h"
#include <limits>
#include <queue>
#include <unordered_map>
#include <algorithm>

solution little::solve(graph &graph) {
    auto cycle = std::vector<edge_l>();
    solution best_solution;
    best_solution.weight = std::numeric_limits<int>::max();

    traverse_tree(graph, cycle, 0, best_solution, graph);

    return best_solution;
}

std::pair<graph, int> little::reduce(graph &to_reduce) {
    auto reduced = graph(to_reduce);
    int lower_bound = 0;

    // Redukcja rzędów
    for (vertex_t row = 0; row < reduced.get_vertices(); ++row) {
        if (to_reduce.is_row_deleted(row)) continue;
        int lowest = std::numeric_limits<int>::max();

        for (vertex_t col = 0; col < reduced.get_vertices(); ++col) {
            if (to_reduce.is_column_deleted(col)) continue;
            if (to_reduce.get_weight(row, col) == -1) continue;

            if (reduced.get_weight(row, col) < lowest) {
                lowest = reduced.get_weight(row, col);
            }
        }

        if (lowest == std::numeric_limits<int>::max()) continue;

        lower_bound += lowest;

        for (vertex_t col = 0; col < reduced.get_vertices(); ++col) {
            if (to_reduce.is_column_deleted(col)) continue;
            if (to_reduce.get_weight(row, col) == -1) continue;

            reduced.set_edge(row, col, reduced.get_weight(row, col) - lowest);
        }
    }

    // Redukcja kolumn
    for (vertex_t col = 0; col < reduced.get_vertices(); ++col) {
        if (to_reduce.is_column_deleted(col)) continue;
        int lowest = std::numeric_limits<int>::max();

        for (vertex_t row = 0; row < reduced.get_vertices(); ++row) {
            if (to_reduce.is_row_deleted(row)) continue;
            if (to_reduce.get_weight(row, col) == -1) continue;

            if (reduced.get_weight(row, col) < lowest) {
                lowest = reduced.get_weight(row, col);
            }
        }

        if (lowest == std::numeric_limits<int>::max()) continue;

        lower_bound += lowest;

        for (vertex_t row = 0; row < reduced.get_vertices(); ++row) {
            if (to_reduce.is_row_deleted(row)) continue;
            if (to_reduce.get_weight(row, col) == -1) continue;

            reduced.set_edge(row, col, reduced.get_weight(row, col) - lowest);
        }
    }

    return {reduced, lower_bound};
}

std::pair<std::pair<vertex_t, vertex_t>, int> little::division_pair(graph &reduced_graph) {
    int max_sum = std::numeric_limits<int>::min();
    std::pair<vertex_t, vertex_t> max_pair;

    for (vertex_t row = 0; row < reduced_graph.get_vertices(); ++row) {
        if (reduced_graph.is_row_deleted(row)) continue;
        for (vertex_t column = 0; column < reduced_graph.get_vertices(); ++column) {
            if (reduced_graph.is_column_deleted(column)) continue;

            if (reduced_graph.get_weight(row, column) == 0) {
                int min_in_row = std::numeric_limits<int>::max();
                int min_in_column = std::numeric_limits<int>::max();

                for (vertex_t col_search = 0; col_search < reduced_graph.get_vertices(); ++col_search) {
                    if (reduced_graph.is_column_deleted(col_search)) continue;
                    if (reduced_graph.get_weight(row, col_search) == -1) continue;
                    if (column == col_search) continue;

                    if (reduced_graph.get_weight(row, col_search) < min_in_row)
                        min_in_row = reduced_graph.get_weight(row, col_search);
                }

                for (vertex_t row_search = 0; row_search < reduced_graph.get_vertices(); ++row_search) {
                    if (reduced_graph.is_row_deleted(row_search)) continue;
                    if (reduced_graph.get_weight(row_search, column) == -1) continue;
                    if (row == row_search) continue;

                    if (reduced_graph.get_weight(row_search, column) < min_in_column)
                        min_in_column = reduced_graph.get_weight(row_search, column);
                }

                if (min_in_row + min_in_column > max_sum) {
                    max_sum = min_in_row + min_in_column;
                    max_pair.first = row;
                    max_pair.second = column;
                }
            }
        }
    }

    return {max_pair, max_sum};
}

graph little::left_subtree(graph &reduced, edge_l edge, std::vector<edge_l>& cycle) {
    auto new_graph = graph(reduced);

    new_graph.delete_row(edge.first);
    new_graph.delete_column(edge.second);

    new_graph.set_edge(edge.second, edge.first, -1);

    if (cycle.size() == 1)
        return new_graph;

    std::vector<vertex_t> longest_path = path_from_edge_list(cycle);

    new_graph.set_edge(longest_path[longest_path.size() - 1], longest_path[0], -1);

    return new_graph;
}

graph little::right_subtree(graph &reduced, vertex_t row, vertex_t column) {
    auto new_graph = graph(reduced);

    // Nieskończoność w miejsce krawędzi (row, column)
    new_graph.set_edge(row, column, -1);

    return new_graph;
}

void little::traverse_tree(graph target, std::vector<edge_l> cycle,
                           int lower_bound, solution& best_solution,
                           graph& original_graph) {
    auto [reduced_graph, reduced] = reduce(target);

    if (lower_bound + reduced < min_sol) {
        if (reduced_graph.degree() == 2) {
            min_sol = lower_bound + reduced;

            for (vertex_t u = 0; u < reduced_graph.get_vertices(); ++u) {
                if (reduced_graph.is_row_deleted(u)) continue;
                for (vertex_t v = 0; v < reduced_graph.get_vertices(); ++v) {
                    if (reduced_graph.is_column_deleted(v)) continue;
                    if (reduced_graph.get_weight(u, v) != 0) continue;

                    cycle.emplace_back(u, v);
                }
            }

            std::vector<vertex_t> path = path_from_edge_list(cycle);
            path.push_back(path[0]);
            int cost = calculate_cost(original_graph, path);

            if (cost < best_solution.weight) {
                best_solution.weight = cost;
                best_solution.vertices = path;
            }

        } else {
            auto [pair, max] = division_pair(reduced_graph);
            std::vector<edge_l> new_cycle(cycle);
            new_cycle.push_back(pair);
            traverse_tree(left_subtree(reduced_graph, pair, new_cycle),
                          new_cycle,
                          lower_bound + reduced,
                          best_solution, original_graph);

            if (lower_bound + reduced + max < min_sol) {
                traverse_tree(right_subtree(reduced_graph, pair.first, pair.second),
                              cycle,
                              lower_bound + reduced,
                              best_solution, original_graph);
            }
        }
    }
}

std::vector<vertex_t> little::path_from_edge_list(std::vector<edge_l> &edges) {
    std::unordered_map<vertex_t, vertex_t> map;
    std::set<vertex_t> cycle_vertices;
    for (auto& [u, v]: edges) {
        cycle_vertices.emplace(u);
        cycle_vertices.emplace(v);
        map[u] = v;
    }

    // skonstruowanie najdłuższej ścieżki z możliwych krawędzi
    size_t longest = 0;
    std::vector<vertex_t> longest_path;
    for (auto& vertex: cycle_vertices) {
        std::vector<vertex_t> current_path;
        vertex_t current = vertex;
        current_path.push_back(current);
        while (map.find(current) != map.end()) {
            current = map[current];
            if (std::find(current_path.begin(), current_path.end(), current) != current_path.end())
                break;
            current_path.push_back(current);
        }
        if (current_path.size() > longest) {
            longest_path = current_path;
            longest = longest_path.size();
        }
    }
    return longest_path;
}

int little::calculate_cost(graph& graph, std::vector<vertex_t> &path) {
    int final_weight = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        int weight = graph.get_weight(path[i], path[i + 1]);
        final_weight += weight;
    }

    return final_weight;
}
