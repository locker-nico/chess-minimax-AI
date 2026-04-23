//
// Created by nlock on 14.04.2026.
//

#ifndef HELLO_WORLD_MINIMAX_H
#define HELLO_WORLD_MINIMAX_H

#include "chess.hpp"
#include "Node.h"

class Minimax {

public:
    int limit;

    Minimax() = default;
    double terminalTest(Node &node);
    double maxValue(Node &node, double alpha, double beta);
    double minValue(Node &node, double alpha, double beta);
    Node alphaBetaSearch(Node &node);
    Node flexibleDepthSearch(Node &node);


};


#endif //HELLO_WORLD_MINIMAX_H
