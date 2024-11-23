

#ifndef PEA_ATSP_BRUTEFORCE_ITER_OPT_H
#define PEA_ATSP_BRUTEFORCE_ITER_OPT_H


#include "../../algorithm.h"

class bruteforce_iter_opt: algorithm {
public:
    solution solve(graph &graph) override;

private:
    static solution permute(graph& graph, std::vector<vertex_t>& vertices);
    static int calculate_weight(graph& graph, std::vector<vertex_t>& permutation);
};


#endif //PEA_ATSP_BRUTEFORCE_ITER_OPT_H
