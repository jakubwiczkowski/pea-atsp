

#include "branchandbound.h"
#include <limits>
#include <algorithm>
#include <stack>


solution branchandbound::solve(graph &graph) {
    vertex_t vertices = graph.get_vertices();
    int lower_bound = minimum_spanning_tree(graph);
//    int lower_bound = std::numeric_limits<int>::min();
    int upper_bound = std::numeric_limits<int>::max();

    std::cout << "> Lower bound = " << lower_bound << std::endl;
    std::cout << "> Upper bound = " << upper_bound << std::endl;

    // DFS with bound updating
    // lower bound based on MST

    for (vertex_t start = 0; start < vertices; ++start) {
        std::vector<bool> visited(vertices, false);

        // Create a stack for DFS
        std::stack<vertex_t> stack;

        // Push the current source node.
        stack.push(0);

        while (!stack.empty()) {
            // Pop a vertex from stack and print it
            vertex_t top = stack.top();
            stack.pop();

            if (stack.size() == vertices) {
                // found path

                break;
            }

            // Stack may contain same vertex twice. So
            // we need to print the popped item only
            // if it is not visited.
            if (!visited[top]) {
                std::cout << top << " ";
                visited[top] = true;
            }

            // Get all adjacent vertices of the popped vertex s
            // If a adjacent has not been visited, then push it
            // to the stack.
            for (vertex_t i = 0; i < vertices; ++i) {
                if (i == top) continue;
                if (visited[i]) continue;

                stack.push(i);
            }
        }
    }

    return {};
}

int branchandbound::minimum_spanning_tree(graph &graph) {
    auto vertices = graph.get_vertices();

    std::vector<edge> edges;
    auto parent = new vertex_t[vertices];

    for (vertex_t u = 0; u < vertices; ++u) {
        parent[u] = u;

        // W badanym przypadku (graf jest zawsze pełny)
        // wierzchołek u będzie sąsiadował z każdym wierzchołkiem
        // oprócz siebie

        for (vertex_t v = 0; v < vertices; ++v) {
            if (u == v) continue;
            edges.push_back({u, v, graph.get_weight(u, v)});
        }
    }

    std::sort(edges.begin(), edges.end(), edge::compare);

    vertex_t i = 0;
    vertex_t e = 0;

    int value = 0;

    while (i < vertices - 1) {
        edge next_edge = edges[e++];
        ushort x = find(parent, next_edge.source);
        ushort y = find(parent, next_edge.destination);

        if (x != y) {
            value += next_edge.weight;
            i++;
            union_set(parent, x, y);
        }
    }

    delete[] parent;

    return value;
}

vertex_t branchandbound::find(vertex_t *parent, vertex_t i) {
    if (parent[i] != i) {
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

void branchandbound::union_set(vertex_t *parent, vertex_t x, vertex_t y) {
    vertex_t x_set = find(parent, x);
    vertex_t y_set = find(parent, y);
    parent[x_set] = y_set;
}
