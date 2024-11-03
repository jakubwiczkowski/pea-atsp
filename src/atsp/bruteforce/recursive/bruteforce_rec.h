#ifndef PEA_ATSP_BRUTEFORCE_REC_H
#define PEA_ATSP_BRUTEFORCE_REC_H


#include "../../algorithm.h"

class bruteforce_rec : algorithm {
public:
    solution solve(graph &graph) override;

private:
    permutations_t permute(std::vector<vertex_t>& vertices);
    void permutations(permutations_t& result, std::vector<vertex_t> vertices, int idx);
};


#endif //PEA_ATSP_BRUTEFORCE_REC_H
