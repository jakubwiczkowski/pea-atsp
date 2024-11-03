#ifndef PEA_ATSP_ALGORITHM_H
#define PEA_ATSP_ALGORITHM_H


#include "../graph/graph.h"
#include "solution.h"

class algorithm {
public:
    virtual solution solve(graph& graph) = 0;
};


#endif //PEA_ATSP_ALGORITHM_H
