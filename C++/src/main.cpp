#include <iostream>
#include "chess.hpp"
#include "Node.h"
#include "Minimax.h"

int main(){

    // initialize Board
    chess::Board board;
    Minimax minimax;

    int counter = 0;

    while (true){
        if (counter != 0){
            std::cout << "\n" << "Type move of your opponent: ";
            std::string moveInput;
            std::cin >> moveInput;
            try {
                chess::Move move = chess::uci::uciToMove(board, moveInput);
                board.makeMove(move);
            } catch (...) {

                std::cout << "Move is not valid";
            }
        }
        Node root = Node(board, 0);
        Node result = minimax.flexibleDepthSearch(root);
        std::cout << "\n" << "Result is: " << chess::uci::moveToUci(result.action);
        board = result.state;
        std::cout << "FEN is: " << board.getFen();

        counter += 1;
    }


    return 0;
}