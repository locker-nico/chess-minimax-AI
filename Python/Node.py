import copy
import copy as cp
import random

import chess

class Node:
    def __init__(self, state, action='root', depth=0):
        self.state = state
        self.utility = 0
        self.action = action
        self.depth = depth
        self.children = []
        self.expanded = False

    def generate_children(self):
        if not self.expanded:
            moves = list(self.state.legal_moves)

            # Order heuristic, captures first
            moves_ordered = []
            for move in moves:
                if self.state.is_capture(move):
                    moves_ordered.append(move)
                    moves.remove(move)

            # append remaining moves
            for move in moves:
                moves_ordered.append(move)

            for move in moves_ordered:
                child_state = copy.deepcopy(self.state)
                child_state.push(move)
                child_node = Node(child_state, action=move, depth=self.depth+1)
                self.children.append(child_node)

            self.expanded = True

    def get_children(self):
        return self.children

    def get_number_of_legal_moves(self):
        return len(list(self.state.legal_moves))

    def update_utility(self, utility):
        self.utility = utility
