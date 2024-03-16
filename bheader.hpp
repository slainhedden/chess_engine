#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp> 
#include <SFML/Network.hpp>

enum Player { PLAYER1, PLAYER2 };

enum Piece {
    Empty, // No piece
    WPawn, WBishop, WKnight, WRook, WQueen, WKing, // White pieces
    BPawn, BBishop, BKnight, BRook, BQueen, BKing // Black pieces
};

class Board {
private:
    int width = 8;
    int height = 8;
    std::vector<std::vector<Piece>> board;
    Player CurrentPlayer;
    int turnNumber;

public:
    Board(); // implemented
    void draw(sf::RenderWindow& window); // always updating needs improvement // draws board
    void draw(int x2, int y2); // redraws a specific cell
    void setBoard(); 
    void printBoard(); 
    void movePiece(int x1, int y1, int x2, int y2);  
    void switchPlayer(); 
    Player getCurrentPlayer() const; 
    bool boundsChecker(int x, int y); 
    bool isLegalMove(int x1, int y1, int x2, int y2); //
    bool isBishopLegal(int x1, int y1, int x2, int y2);
    bool isPawnMoveLegal(int x1, int y1, int x2, int y2);
    bool isPawnTakeLegal(int x1, int y1, int x2, int y2);
    bool isKnightMoveLegal(int x1, int y1, int x2, int y2);
    bool isRookMoveLegal(int x1, int y1, int x2, int y2);
    bool isQueenMoveLegal(int x1, int y1, int x2, int y2);
    bool isKingMoveLegal(int x1, int y1, int x2, int y2);
};
