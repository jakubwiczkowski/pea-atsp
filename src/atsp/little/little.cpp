

#include "little.h"
#include <limits>
#include <queue>

//solution little::solve(graph &graph) {
//    auto reduced = reduce(graph);
//
//    std::cout << "LB = " << reduced.second << std::endl;
//
//    auto div_p = division_pair(reduced.first);
//
//    std::cout << "   ZREDUKOWANY:" << std::endl;
//    reduced.first.display();
//    std::cout << "div_p: " << div_p.first.first << " " << div_p.first.second << std::endl;
//
//    auto left = left_subtree(reduced.first, div_p.first.first, div_p.first.second);
//    auto right = right_subtree(reduced.first, div_p.first.first, div_p.first.second);
//
//    std::cout << "  LEWY:" << std::endl;
//    left.display();
//
//    std::cout << "  PRAWY:" << std::endl;
//    right.display();
//
//    auto xd = reduce(left);
//    std::cout << xd.second << std::endl;
//    xd.first.display();
//
//    return solution();
//}

struct Node {
    graph* current_graph;
    std::vector<edge_l> path;
    int lower_bound;

    bool operator>(const Node &other) const {
        return lower_bound > other.lower_bound;
    }
};

solution little::solve(graph &graph) {
    // Initial reduction of the graph
    auto reduced = reduce(graph);
    int lower_bound = reduced.second;
    int upper_bound = std::numeric_limits<int>::max();
    std::vector<edge_l> best_path;

    // Priority queue to explore nodes
    std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
    pq.push({reduced.first, {}, lower_bound});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        std::cout << pq.size() << std::endl;

        // If the current path includes all vertices, check if it's a better solution
        if (current.path.size() == graph.get_vertices()) {
            std::cout << "    HURRA   " << std::endl;
            if (current.lower_bound < upper_bound) {
                upper_bound = current.lower_bound;
                best_path = current.path;
            }
            continue;
        }

        // Generate left and right subtrees
        auto division_p = division_pair(*current.current_graph);
        auto left = left_subtree(*current.current_graph, division_p.first.first, division_p.first.second);
        auto right = right_subtree(*current.current_graph, division_p.first.first, division_p.first.second);

        // Add left subtree to the priority queue
        auto left_reduced = reduce(*left);
        auto left_path = current.path;
        left_path.push_back(division_p.first);
        pq.push({left_reduced.first, left_path, current.lower_bound + division_p.second});

        // Add right subtree to the priority queue
        auto right_reduced = reduce(*right);
//        auto right_path = current.path;
        pq.push({right_reduced.first, current.path, current.lower_bound});
    }

    // Construct the solution from the best path found
    solution best_solution;
    best_solution.weight = upper_bound;
    for (const auto &edge : best_path) {
        best_solution.vertices.push_back(edge.first);
    }
    best_solution.vertices.push_back(best_path.front().first); // Complete the cycle

    return best_solution;
}

std::pair<graph*, int> little::reduce(graph &to_reduce) {
    auto reduced = new graph(to_reduce);
    int lower_bound = 0;

    // Redukcja rzędów
    for (vertex_t row = 0; row < reduced->get_vertices(); ++row) {
        int lowest = std::numeric_limits<int>::max();

        for (vertex_t col = 0; col < reduced->get_vertices(); ++col) {
            if (to_reduce.get_weight(row, col) == -1) continue;

            if (reduced->get_weight(row, col) < lowest)
                lowest = reduced->get_weight(row, col);
        }

        if (lowest == std::numeric_limits<int>::max()) continue;

        lower_bound += lowest;

        for (vertex_t col = 0; col < reduced->get_vertices(); ++col) {
            if (to_reduce.get_weight(row, col) == -1) continue;

            reduced->set_edge(row, col, reduced->get_weight(row, col) - lowest);
        }
    }

    // Redukcja kolumn
    for (vertex_t col = 0; col < reduced->get_vertices(); ++col) {
        int lowest = std::numeric_limits<int>::max();

        for (vertex_t row = 0; row < reduced->get_vertices(); ++row) {
            if (to_reduce.get_weight(row, col) == -1) continue;

            if (reduced->get_weight(row, col) < lowest)
                lowest = reduced->get_weight(row, col);
        }

        if (lowest == std::numeric_limits<int>::max()) continue;

        lower_bound += lowest;

        for (vertex_t row = 0; row < reduced->get_vertices(); ++row) {
            if (to_reduce.get_weight(row, col) == -1) continue;

            reduced->set_edge(row, col, reduced->get_weight(row, col) - lowest);
        }
    }

    return {reduced, lower_bound};
}

std::pair<std::pair<vertex_t, vertex_t>, int> little::division_pair(graph &reduced_graph) {
    int max_sum = std::numeric_limits<int>::min();
    std::pair<vertex_t, vertex_t> max_pair;

    for (vertex_t row = 0; row < reduced_graph.get_vertices(); ++row) {
        for (vertex_t column = 0; column < reduced_graph.get_vertices(); ++column) {
            if (reduced_graph.get_weight(row, column) == -1) continue;
            if (reduced_graph.get_weight(row, column) != 0) continue;

            int min_in_row = std::numeric_limits<int>::max();
            int min_in_column = std::numeric_limits<int>::max();

            for (vertex_t col_search = 0; col_search < reduced_graph.get_vertices(); ++col_search) {
                if (reduced_graph.get_weight(row, col_search) == -1) continue;
                if (column == col_search) continue;

                if (reduced_graph.get_weight(row, col_search) < min_in_row)
                    min_in_row = reduced_graph.get_weight(row, col_search);
            }

            for (vertex_t row_search = 0; row_search < reduced_graph.get_vertices(); ++row_search) {
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

    return {max_pair, max_sum};
}

//graph* little::left_subtree(graph &reduced, vertex_t row, vertex_t column) {
//    auto new_graph = new graph(reduced.get_vertices() - 1);
//
//    // skopiować wartości ze zredukowanego grafu bez row rzędu i column kolumny
//
//    vertex_t new_row_idx = 0;
//    for (vertex_t copy_row = 0; copy_row < reduced.get_vertices(); ++copy_row) {
//        if (copy_row == row) {
//            continue;
//        }
//
//        vertex_t new_column_idx = 0;
//        for (vertex_t copy_column = 0; copy_column < reduced.get_vertices(); ++copy_column) {
//            if (copy_column == column) {
//                continue;
//            }
//
//            if (copy_row == column && copy_column == row) {
//                new_graph->set_edge(new_row_idx, new_column_idx, -1);
//            } else {
//                new_graph->set_edge(new_row_idx, new_column_idx, reduced.get_weight(copy_row, copy_column));
//            }
//
//            new_column_idx++;
//        }
//
//        new_row_idx++;
//    }
//
//    return new_graph;
//}

graph* little::left_subtree(graph &reduced, vertex_t row, vertex_t column) {
    auto new_graph = new graph(reduced);

    // skopiować wartości ze zredukowanego grafu bez row rzędu i column kolumny

    for (vertex_t copy_row = 0; copy_row < reduced.get_vertices(); ++copy_row) {
        for (vertex_t copy_column = 0; copy_column < reduced.get_vertices(); ++copy_column) {
            if (!(copy_row == row || copy_column == column)) continue;

            new_graph->set_edge(copy_row, copy_column, -1);
        }
    }

    return new_graph;
}

graph* little::right_subtree(graph &reduced, vertex_t row, vertex_t column) {
    auto new_graph = new graph(reduced);

    // Nieskończoność w miejsce krawędzi (row, column)
    new_graph->set_edge(row, column, -1);

    return new_graph;
}
//std::tuple<std::vector<edge_l>, int, int>
//little::step(graph &target, std::vector<edge_l> edges, int lower_bound, int upper_bound) {
//    auto reduced = reduce(target);
//
//    // Base case: if the graph is reduced to 2 vertices, return the solution
//    if (reduced.first.get_vertices() == 2) {
//        for (vertex_t row = 0; row < reduced.first.get_vertices(); ++row) {
//            for (vertex_t col = 0; col < reduced.first.get_vertices(); ++col) {
//                if (reduced.first.get_weight(row, col) != -1) {
//                    edges.push_back({row, col});
//                    lower_bound += reduced.first.get_weight(row, col);
//                }
//            }
//        }
//        return {edges, lower_bound, upper_bound};
//    }
//
//    auto division_p = division_pair(reduced.first);
//    auto left = left_subtree(reduced.first, division_p.first.first, division_p.first.second);
//    auto right = right_subtree(reduced.first, division_p.first.first, division_p.first.second);
//
//    // Explore the left subtree
////    auto left_result = step(left, edges, lower_bound + division_p.second, upper_bound);
////    if (std::get<1>(left_result) < upper_bound) {
////        upper_bound = std::get<1>(left_result);
////        edges = std::get<0>(left_result);
////    }
////
////    // Explore the right subtree
////    auto right_result = step(right, edges, lower_bound, upper_bound);
////    if (std::get<1>(right_result) < upper_bound) {
////        upper_bound = std::get<1>(right_result);
////        edges = std::get<0>(right_result);
////    }
//
//    return {edges, upper_bound, upper_bound};
//}
////std::tuple<std::vector<edge_l>, int, int>
//little::step(graph &target, std::vector<edge_l> edges, int lower_bound, int upper_bound) {
//    auto reduced = reduce(target);
//
//    // warunek końcowy rekurencji
//    if (reduced.first.get_vertices() == 2) {
//        //TODO: poprawnie to zrobić
//        return {edges, lower_bound, upper_bound};
//    }
//
//    auto division_p = division_pair(reduced.first);
//    edges.push_back(division_p.first);
//
//    auto left = left_subtree(reduced.first, division_p.first.first, division_p.first.second);
//    auto left_ret = step(left, edges, reduced.second, upper_bound);
//
//    auto right = right_subtree(reduced.first, division_p.first.first, division_p.first.second);
//
//
//    return std::tuple<std::vector<edge_l>, int, int>();
//}
