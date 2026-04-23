//
// Created by nlock on 14.04.2026.
//

#include <cmath>
#include "Minimax.h"
#include "chess.hpp"

using namespace chess;


double Minimax::terminalTest(Node &node) {

    // Count pieces of Max (white)
    Bitboard whitePawnsBB = node.state.pieces(PieceType::PAWN, Color::WHITE);
    Bitboard whiteKnightsBB = node.state.pieces(PieceType::KNIGHT, Color::WHITE);
    Bitboard whiteBishopsBB = node.state.pieces(PieceType::BISHOP, Color::WHITE);
    Bitboard whiteRooksBB = node.state.pieces(PieceType::ROOK, Color::WHITE);
    Bitboard whiteQueensBB = node.state.pieces(PieceType::QUEEN, Color::WHITE);
    Bitboard whiteKingBB = node.state.pieces(PieceType::KING, Color::WHITE);
    int numPawnsWhite = whitePawnsBB.count();
    int numKnightsWhite = whiteKnightsBB.count();
    int numBishopsWhite = whiteBishopsBB.count();
    int numRooksWhite = whiteRooksBB.count();
    int numQueensWhite = whiteQueensBB.count();
    int numKingWhite = whiteKingBB.count();

    // Count pieces of Min (black)
    Bitboard blackPawnsBB = node.state.pieces(PieceType::PAWN, Color::BLACK);
    Bitboard blackKnightsBB = node.state.pieces(PieceType::KNIGHT, Color::BLACK);
    Bitboard blackBishopsBB = node.state.pieces(PieceType::BISHOP, Color::BLACK);
    Bitboard blackRooksBB = node.state.pieces(PieceType::ROOK, Color::BLACK);
    Bitboard blackQueensBB = node.state.pieces(PieceType::QUEEN, Color::BLACK);
    int numPawnsBlack = blackPawnsBB.count();
    int numKnightsBlack = blackKnightsBB.count();
    int numBishopsBlack = blackBishopsBB.count();
    int numRooksBlack = blackRooksBB.count();
    int numQueensBlack = blackQueensBB.count();

    // Count checkmates and stalemates
    int checkmate = 0;
    int stalemate = 0;

    GameResultReason gameState = node.state.isGameOver().first;
    if (gameState == GameResultReason::CHECKMATE) {

        if (numKingWhite == 1) {

            checkmate = 1;

        } else {
            checkmate = -1;
        }

    } else if (gameState == GameResultReason::STALEMATE){
        stalemate = 1;
    }

    // Consider number of possible moves=
    int numLegalMoves = node.getNumberOfLegalMoves();

    // Calculate utility by weighting pieces
    double utility = (
            (1 * numPawnsWhite + 3 * numKnightsWhite + 3 * numBishopsWhite + 5 * numRooksWhite + 9 * numQueensWhite)
            - (1 * numPawnsBlack + 3 * numKnightsBlack + 3 * numBishopsBlack + 5 * numRooksBlack + 9 * numQueensBlack)
            + 100 * checkmate - 50 * stalemate + 0.05 * numLegalMoves);

    return utility;
}

double Minimax::maxValue(Node &node, double alpha, double beta) {

    if (node.depth == limit) {
        double terminalTestResult = terminalTest(node);
        node.updateUtility(terminalTestResult);
        return terminalTestResult;
    }
    double v = -999999;
    node.generateChildren();
    std::vector<Node> &children = node.getChildren();
    for (int i = 0; i < children.size(); i++) {
        v = std::max(v, minValue(children[i], alpha, beta));
        if (v >= beta) {
            node.updateUtility(v);
            return v;
        }
        alpha = std::max(alpha, v);
    }
    node.updateUtility(v);
    return v;
}

double Minimax::minValue(Node &node, double alpha, double beta) {
    if (node.depth == limit) {
        double terminalTestResult = terminalTest(node);
        node.updateUtility(terminalTestResult);
        return terminalTestResult;
    }
    double v = 999999;
    node.generateChildren();
    std::vector<Node> &children = node.getChildren();
    for (int i = 0; i < children.size(); i++) {
        v = std::min(v, maxValue(children[i], alpha, beta));
        if (v <= alpha) {
            node.updateUtility(v);
            return v;
        }
        beta = std::min(beta, v);
    }
    node.updateUtility(v);
    return v;
}

Node Minimax::alphaBetaSearch(Node &node) {
    double v = maxValue(node, -999999, 999999);
    std::cout << v;
    std::vector<Node> children = node.getChildren();
    for (int i = 0; i < children.size(); i++) {
        if (children[i].utility == v) {
            return children[i];
        }
    }
    throw "No action found";
}

Node Minimax::flexibleDepthSearch(Node &node) {
    std::cout << "Number of legal moves:" << node.getNumberOfLegalMoves() << "\n";
    double suggestedDepth = log(1000000) / log(node.getNumberOfLegalMoves());
    std::cout << "Suggested depth: " << suggestedDepth << "\n";
    limit = std::min(6, (int) round(suggestedDepth));
    std::cout << "Limit: " << limit << "\n";
    Node result = alphaBetaSearch(node);
    return result;
}