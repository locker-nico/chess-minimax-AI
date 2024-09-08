# Algorithm
This Bot is using Minimax with alpha-beta pruning.

The utility is being evaluated at certain depths by using a linear utility function based on material value, mobility, checkmates and stalemates.

Actions are ordered by capture-first.

Minimax is implemented as a flexible Depth Limited Search by calculating a fixed depth for each turn of max based on the number of legal moves of the root to limit the number of expanded nodes. Thus a depth of 4-5 plies is being achieved 

# Further Improvements
Due to the consideration of mobility in the utility function, max is able to play a more dynamic game, but the endgame still suffers from random moves. Further improvements might include the use of endgame tablebases and openings.

Also, a better ordering heuristic could allow for a deeper search.
