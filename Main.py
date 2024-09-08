import Node
import Minimax as mm
import chess

board = chess.Board()

minmax = mm.Minimax(time_limit=20)

last_utility = 0
counter = 0
while(True):
    if counter != 0:
        while(True):
            move = input('Type move of your opponent')
            try:
             board.push(chess.Move.from_uci(move))
             break
            except chess.InvalidMoveError:
                print('Invalid move')
            except chess.IllegalMoveError:
                print('Illegal move')
            except AssertionError:
                print('Illegal move')

    root = Node.Node(board)
    result = minmax.flexible_depth_search(root)
    print('Utility:', result.utility, '\n', result.state, '\nMove:', result.action)
    board = result.state
    last_utility = result.utility

    counter += 1
