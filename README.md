# Chess Game
 Chess Game on Console 
This program is a chess game implemented in C++ that utilizes dynamic memory allocation and pointers to manage the chessboard and game pieces. It provides a complete chess experience with functionalities such as move validation, check, checkmate, stalemate detection, and piece promotion.

Key Features
1. Dynamic Memory Allocation
Flexible Piece Management: Each chess piece (king, queen, bishop, knight, rook, and pawn) is created using dynamic memory allocation, allowing for efficient use of memory and flexibility in piece management.
Pointer Utilization: The program uses pointers to manipulate piece objects, facilitating memory management, particularly when pieces are moved or captured.
2. Game Mechanics
Movement Validation: The program checks if a move is legal based on the piece type and its current position. Each piece has specific movement rules that are enforced to ensure fair play.
Check and Checkmate Detection: After every move, the program checks if the player's king is in check. If it is, the user is limited to moves that would get their king out of check. The program also detects checkmate scenarios, concluding the game when the king has no legal moves.
Stalemate Detection: The program checks for stalemate conditions where the player has no legal moves but is not in check, ending the game in a draw.
3. Advanced Features
Undo/Redo Functionality: By maintaining a history of board states, the program allows players to undo their moves, enhancing the gaming experience and providing a safety net for players making mistakes.
Piece Promotion: When a pawn reaches the opposite side of the board, the program offers the option to promote it to a higher-ranking piece (typically a queen), adding depth to the gameplay.
4. User Interaction
Command Line Interface: Players interact with the game via a command-line interface, selecting pieces to move by specifying their source and destination coordinates.
Real-time Updates: The board is visually updated after every move, providing immediate feedback on the game state.
