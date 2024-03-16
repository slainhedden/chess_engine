#include "bheader.hpp"
#include <iostream>
#include <cmath>
// Function to draw the chess board and pieces
void Board::draw(sf::RenderWindow& window) {
    float cellSize = 50.0f;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);
            cell.setFillColor((i + j) % 2 == 0 ? sf::Color::White : sf::Color::Black);
            // Draw pieces
            window.draw(cell);
            sf::Texture pieceTexture;
            std::string pieceName;

            switch (board[i][j]) {
                case WPawn:   pieceName = "Assets/wp.png"; break;
                case WBishop: pieceName = "Assets/wb.png"; break;
                case WKnight: pieceName = "Assets/wn.png"; break;
                case WRook:   pieceName = "Assets/wr.png"; break;
                case WQueen:  pieceName = "Assets/wq.png"; break;
                case WKing:   pieceName = "Assets/wk.png"; break;
                case BPawn:   pieceName = "Assets/bp.png"; break;
                case BBishop: pieceName = "Assets/bb.png"; break;
                case BKnight: pieceName = "Assets/bn.png"; break;
                case BRook:   pieceName = "Assets/br.png"; break;
                case BQueen:  pieceName = "Assets/bq.png"; break;
                case BKing:   pieceName = "Assets/bk.png"; break;
                default: break;
            }

            if (!pieceName.empty()) {
                if (!pieceTexture.loadFromFile(pieceName)) {
                    std::cerr << "Failed to load image: " << pieceName << std::endl;
                } else {
                    sf::Sprite pieceSprite(pieceTexture);
                    pieceSprite.setScale(cellSize / pieceTexture.getSize().x, cellSize / pieceTexture.getSize().y);
                    pieceSprite.setPosition(j * cellSize, i * cellSize);
                    window.draw(pieceSprite);
                }
            }
        }
    }    // Create a font
    sf::Font font;
    if (!(font.loadFromFile("Roboto-Bold.ttf"))) {
        // Error handling if the font file is not found
        return;
    }

    // Create a text object for the current player
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(24);
    playerText.setFillColor(sf::Color::White);
    playerText.setPosition(10, 10);
    playerText.setString("Current Player: " + std::string(getCurrentPlayer() == PLAYER1 ? "White" : "Black"));

    // Create a text object for the turn number
    sf::Text turnText;
    turnText.setFont(font);
    turnText.setCharacterSize(24);
    turnText.setFillColor(sf::Color::White);
    turnText.setPosition(10, 40);
    turnText.setString("Turn: " + std::to_string(turnNumber));

    // Draw the text objects on the window
    window.draw(playerText);
    window.draw(turnText);
}

// Board constructor
Board::Board() : board(height, std::vector<Piece>(width, Piece::Empty)), CurrentPlayer(PLAYER1), turnNumber(1) {
    setBoard();
}

// Function to set up the initial board configuration
void Board::setBoard() {
    // Set up the initial position of the pieces.
    board = {
        {WRook, WKnight, WBishop, WQueen, WKing, WBishop, WKnight, WRook},
        {WPawn, WPawn,   WPawn,   WPawn,  WPawn, WPawn,   WPawn,   WPawn},
        {Empty, Empty,   Empty,   Empty,  Empty, Empty,   Empty,   Empty},
        {Empty, Empty,   Empty,   Empty,  Empty, Empty,   Empty,   Empty},
        {Empty, Empty,   Empty,   Empty,  Empty, Empty,   Empty,   Empty},
        {Empty, Empty,   Empty,   Empty,  Empty, Empty,   Empty,   Empty},
        {BPawn, BPawn,   BPawn,   BPawn,  BPawn, BPawn,   BPawn,   BPawn},
        {BRook, BKnight, BBishop, BQueen, BKing, BBishop, BKnight, BRook}
    };
}

// Function to print the board to the console
void Board::printBoard() {
    // Print the board to the console.
    for (const auto& row : board) {
        for (const auto& p : row) {
            std::cout << static_cast<int>(p) << " ";
        }
        std::cout << std::endl;
    }
}

// Function to switch the current player
void Board::switchPlayer() {
    CurrentPlayer = (CurrentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
}

// Function to get the current player
Player Board::getCurrentPlayer() const {
    return CurrentPlayer;
}

// Function to check if the given coordinates are within the board bounds
bool Board::boundsChecker(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

// Function to move a piece on the board
void Board::movePiece(int x1, int y1, int x2, int y2) {
    if (isLegalMove(x1, y1, x2, y2) && boundsChecker(x1, y1) && boundsChecker(x2, y2) &&
        ((getCurrentPlayer() == PLAYER1 && board[y1][x1] >= WPawn && board[y1][x1] <= WKing) ||
         (getCurrentPlayer() == PLAYER2 && board[y1][x1] >= BPawn && board[y1][x1] <= BKing))) {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = Empty;
        switchPlayer();
        turnNumber++;
    }
}

// Function to check if a knight move is legal (horse)
/*
Use the following code to implement the isKnightMoveLegal function:
;
}
*/
bool Board::isKnightMoveLegal(int x1, int y1, int x2, int y2) {
    if (std::abs(x2 - x1) == 2 && std::abs(y2 - y1) == 1) {
        return true;
}
    if (std::abs(y2 - y1) == 2 && std::abs(x2 - x1) == 1) {
        return true;
}
    return false;
}

// Function to check if a rook move is legal
bool Board::isRookMoveLegal(int x1, int y1, int x2, int y2) {
    if (y1 == x1 && board[y2][x2] == Empty) {
        int tx = std::min(x1, x2) + 1;
        while (tx < std::max(x1, x2)) {
            if (board[y1][tx] != Empty) {
                return false;
            }
            tx++;
        }
    }
        if (y1 == y2) {
            int ty = y1;
            while (ty < y2) {
                if (board[ty][x1] != Empty) {
                    return false;
            }
                ty++;
            }
        }
    return true;
}

// Pawn move check
bool Board::isPawnMoveLegal(int x1, int y1, int x2, int y2) {
    if ((y1 + 1 == y2 || (y1 == 1 && y2 == y1 + 2)) && getCurrentPlayer() == PLAYER1) { // white pieces -> start at top
        if (x1 == x2 && board[y2][x2] == Empty) return true; 
        if (isPawnTakeLegal(x1, y1, x2, y2)) {
            // delete the image of the element there
            board[y2][x2] = board[y1][x1];
            board[y1][x1] = Empty;
            return true;
            } 
        return false;
    }

    if (((y1 - 1 == y2) || (y1 == 6 && y2 == y1 - 2)) && getCurrentPlayer() == PLAYER2) { // black pieces -> start at bottom
        if (x1 == x2 && board[y2][x2] == Empty) return true;
        if (isPawnTakeLegal(x1, y1, x2, y2)) {
            // delete the image of the element there
            board[y2][x2] = board[y1][x1];
            board[y1][x1] = Empty;
            return true;
        }
    }
    return false;
}


bool Board::isPawnTakeLegal(int x1, int y1, int x2, int y2) {
    // checks if piece is located there to take
    if (std::abs(x2 - x1) == 1 && ((getCurrentPlayer() == PLAYER1 && y2 - y1 == 1) || (getCurrentPlayer() == PLAYER2 && y1 - y2 == 1))) {
        if ((getCurrentPlayer() == PLAYER1 && board[y2][x2] >= BPawn && board[y2][x2] <= BKing) ||
            (getCurrentPlayer() == PLAYER2 && board[y2][x2] >= WPawn && board[y2][x2] <= WKing)) {
            return true;
        }
    }
    return false;
}



// Bishop move check (not fully implemented)
bool Board::isBishopLegal(int x1, int y1, int x2, int y2) {
    if (std::abs((y2 - y1) / (x2 - x1)) == 1) {
        int tempx = x1;
        int tempy = y1;
        int dx = (x2 > x1) ? 1 : -1; // Determine direction for x
        int dy = (y2 > y1) ? 1 : -1; // Determine direction for y

        tempx += dx; // Move in the correct x direction
        tempy += dy; // Move in the correct y direction
        while (tempx != x2 && tempy != y2) {
            if (board[tempy][tempx] != Empty) {
                return false;
            }
            tempx += dx; // Move in the correct x direction
            tempy += dy; // Move in the correct y direction
        }
        return true;
    }
    return false;
}


// // Function to check if a queen move is legal
bool Board::isQueenMoveLegal(int x1, int y1, int x2, int y2) {
    if (isBishopLegal(x1, y1, x2, y2) || isRookMoveLegal(x1, y1, x2, y2)) {
        return true;
    }
    return false;
}

// // Function to check if a king move is legal
bool Board::isKingMoveLegal(int x1, int y1, int x2, int y2) {
    if (std::abs(x2 - x1) <= 1 && std::abs(y2 - y1) <= 1) {
        return true;
    }
    return false;
}

// // Function to handle pawn promotion
// void Board::handlePawnPromotion(int x, int y) {
//     // ...
// }

// // Function to handle castling
// void Board::handleCastling(int x1, int y1, int x2, int y2) {
//     // ...
// }

// // Function to check if the current player's king is in check
// bool Board::isKingInCheck() {
//     // ...
// }

// // Function to check if the game is over (checkmate or stalemate)
// bool Board::isGameOver() {
//     // ...
// }

// // Function to display the game over screen
// void Board::displayGameOverScreen(sf::RenderWindow& window) {
//     // ...
// }

// // Function to handle move history and undo functionality
// void Board::handleMoveHistory(int x1, int y1, int x2, int y2) {
//     // ...
// }

// // Function to handle the game timer or clock
// void Board::handleTimer() {
//     // ...
// }


// Function to check if a move is legal
bool Board::isLegalMove(int x1, int y1, int x2, int y2) {
    // Check if the source cell is not empty
    if (board[y1][x1] == Empty)
        return false;

    // Check if the destination cell is empty or contains an opponent's piece
    if (board[y2][x2] != Empty &&
        ((getCurrentPlayer() == PLAYER1 && board[y2][x2] < BPawn) ||
         (getCurrentPlayer() == PLAYER2 && board[y2][x2] > BKing)))
        return false;

    // Check if the move is legal based on the piece type
    switch (board[y1][x1]) {
        case WPawn:
            return isPawnMoveLegal(x1, y1, x2, y2);
        case BPawn:
            return isPawnMoveLegal(x1, y1, x2, y2);
        case WBishop:
            return isBishopLegal(x1, y1, x2, y2);
        case BBishop:
            return isBishopLegal(x1, y1, x2, y2);
        case WKnight:
            return isKnightMoveLegal(x1, y1, x2, y2);
        case BKnight:
            return isKnightMoveLegal(x1, y1, x2, y2);
        case WRook:
            return isRookMoveLegal(x1, y1, x2, y2);
        case BRook:
            return isRookMoveLegal(x1, y1, x2, y2);
        case WQueen:
            return isQueenMoveLegal(x1, y1, x2, y2);
        case BQueen:
            return isQueenMoveLegal(x1, y1, x2, y2);
        case WKing:
            return isKingMoveLegal(x1, y1, x2, y2);
        case BKing:
            return isKingMoveLegal(x1, y1, x2, y2);
        
        // Add cases for other piece types
        default:
            return false;
    }
}

