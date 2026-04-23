import math
import random
import time
import numpy as np

class Minimax:
    def __init__(self, time_limit=3):
        self.time_limit = time_limit
        self.limit = 0

    def terminal_test(self, state):
        # count pieces of Max (white)
        white_pawns = len(list(state.state.pieces(piece_type=1, color=True)))
        white_knights = len(list(state.state.pieces(piece_type=2, color=True)))
        white_bishops = len(list(state.state.pieces(piece_type=3, color=True)))
        white_rooks = len(list(state.state.pieces(piece_type=4, color=True)))
        white_queen = len(list(state.state.pieces(piece_type=5, color=True)))

        # count pieces of Min (black)
        black_pawns = len(list(state.state.pieces(piece_type=1, color=False)))
        black_knights = len(list(state.state.pieces(piece_type=2, color=False)))
        black_bishops = len(list(state.state.pieces(piece_type=3, color=False)))
        black_rooks = len(list(state.state.pieces(piece_type=4, color=False)))
        black_queen = len(list(state.state.pieces(piece_type=5, color=False)))

        # Count checkmates and stalemate
        checkmate = 0
        stalemate = 0
        if state.state.is_checkmate() and not state.state.turn:
            checkmate = 1
        elif state.state.is_checkmate() and state.state.turn:
            checkmate = -1
        elif state.state.is_stalemate():
            stalemate = 1

        # Consider number of possible moves
        number_possible_moves = state.get_number_of_legal_moves()

        # Calculate utility by weighting pieces
        utility = ((1*white_pawns + 3*white_knights + 3*white_bishops + 5*white_rooks + 9*white_queen) -
                  (1*black_pawns + 3*black_knights + 3*black_bishops + 5*black_rooks + 9*black_queen)) + 100*checkmate\
                  - 50*stalemate + 0.05*number_possible_moves

        return utility

    def max_value(self, state, alpha, beta):
        if state.depth == self.limit:
            terminal_test_result = self.terminal_test(state)
            state.update_utility(terminal_test_result)
            return terminal_test_result
        v = -999999
        state.generate_children()
        for a in state.get_children():
            v = max(v, self.min_value(a, alpha, beta))
            if v >= beta:
                state.update_utility(v)
                return v
            alpha = max(alpha, v)
        state.update_utility(v)
        return v

    def min_value(self, state, alpha, beta):
        if state.depth == self.limit:
            terminal_test_result = self.terminal_test(state)
            state.update_utility(terminal_test_result)
            return terminal_test_result
        v = 999999
        state.generate_children()
        for a in state.get_children():
            v = min(v, self.max_value(a, alpha, beta))
            if v <= alpha:
                state.update_utility(v)
                return v
            beta = min(beta, v)
        state.update_utility(v)
        return v

    def alpha_beta_search(self, state):
        v = self.max_value(state, -999999, 999999)
        print(v)
        for a in state.get_children():
            if a.utility == v:
                return a

    def iterative_deepening_minimax(self, state, last_utility):
        start_time = time.time()
        for limit in range(5, 6):
            self.limit = limit
            print('limit:', limit)
            result = self.alpha_beta_search(state, start_time=start_time)
            if time.time() - start_time >= self.time_limit:
                print(result)
                return result
        return result

    def flexible_depth_search(self, state):
        suggested_depth = math.log(3200000, state.get_number_of_legal_moves())
        print('Number of legal moves:', state.get_number_of_legal_moves())
        print('Suggested Depth:', suggested_depth)
        self.limit = min(6, round(suggested_depth))
        print('depth:', self.limit)
        result = self.alpha_beta_search(state)
        return result
