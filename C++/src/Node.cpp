//
// Created by nlock on 14.04.2026.
//

#include "Node.h"
#include "chess.hpp"

using namespace chess;

Node::Node(Board state, Move action, int depth) : state(state), action(action), utility(0), depth(depth),
                                                  expanded(false) {}

std::vector <Node> &Node::getChildren() {
    return children;
}

void Node::generateChildren() {

    if (!expanded) {

        // Generate List of legal moves
        movegen movesGenerator;
        Movelist moveList;
        movesGenerator.legalmoves(moveList, state);

        // Iterate through all moves and create a child each
        for (int i = 0; i < moveList.size(); i++) {

            Board child_state = state;
            child_state.makeMove(moveList.at(i));
            Node child_node = Node(child_state, moveList.at(i), depth + 1);
            children.push_back(child_node);

        }

        expanded = true;

    }

}

int Node::getNumberOfLegalMoves() {

    // Generate List of legal moves
    movegen movesGenerator;
    Movelist moveList;
    movesGenerator.legalmoves(moveList, state);
    return moveList.size();

}

void Node::updateUtility(double utility) {
    this->utility = utility;
}
