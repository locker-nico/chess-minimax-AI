//
// Created by nlock on 14.04.2026.
//

#ifndef HELLO_WORLD_NODE_H
#define HELLO_WORLD_NODE_H
#include "chess.hpp"

class Node {

public:
    chess::Board state;
    chess::Move action;
    double utility;
    bool expanded;
    int depth;
    std::vector<Node> children;

    Node(chess::Board state, chess::Move action=chess::Move(), int depth=0);
    void generateChildren();
    std::vector<Node>& getChildren();
    int getNumberOfLegalMoves();
    void updateUtility(double utility);

};


#endif //HELLO_WORLD_NODE_H
