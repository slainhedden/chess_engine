#include <cstdint>
#include "bheader.hpp"
#include <iostream>
#include <SFML/Graphics.hpp> // Add this line to include the SFML/Graphics.hpp library

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Chess");
    Board board;

    int start_x = -1, start_y = -1;
    int end_x = -1, end_y = -1;
    // Display the initial board
    window.clear();
    board.draw(window);
    window.display();
    std::cout << "Player 1's turn\n";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Print the current player once the window is opened and when the player switches 
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int x = event.mouseButton.x / 50;
                    int y = event.mouseButton.y / 50;
                    if (start_x == -1 && start_y == -1) {
                        start_x = x;
                        start_y = y;
                        std::cout << "Selected piece at (" << start_x << ", " << start_y << ")" << std::endl;
                    } else if (end_x == -1 && end_y == -1) {
                        end_x = x;
                        end_y = y;
                        std::cout << "Selected destination at (" << end_x << ", " << end_y << ")" << std::endl;

                        // Make the move
                        std::cout << "Moving piece from (" << start_x << ", " << start_y << ") to (" << end_x << ", " << end_y << ")" << std::endl;
                        board.movePiece(start_x, start_y, end_x, end_y);

                        // Reset the selection variables
                        start_x = -1;
                        start_y = -1;
                        end_x = -1;
                        end_y = -1;
                        std::string player = board.getCurrentPlayer() == PLAYER1 ? "Player 1" : "Player 2";
                        std::cout << "Current player: " << player << std::endl;   
                        // Clear the window and redraw the board after the move
                        window.clear();
                        board.draw(window);
                        window.display();
                    }
                }
            }
        }
    }

    return 0;
}