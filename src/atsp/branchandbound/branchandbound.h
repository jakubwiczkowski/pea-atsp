

#ifndef PEA_ATSP_BRANCHANDBOUND_H
#define PEA_ATSP_BRANCHANDBOUND_H


#include "../algorithm.h"

struct edge {
    vertex_t source;
    vertex_t destination;
    int weight;

    static bool compare(const edge& x, const edge& y) {
        return x.weight < y.weight;
    }
};

class branchandbound : algorithm {
public:
    solution solve(graph &graph) override;

private:
    int minimum_spanning_tree(graph& graph);

    vertex_t find(vertex_t* parent, vertex_t i);
    void union_set(vertex_t* parent, vertex_t x, vertex_t y);
};


#endif //PEA_ATSP_BRANCHANDBOUND_H
