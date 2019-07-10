#include <SFML/Graphics.hpp>
#include <iostream>
#include "game_grid.h"
#include "shapes.h"
#include "point_system.h"

int main()
{
    int windowWidth = 305;
    int windowHeight = 405;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
        "Tetris", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(80);

    GameGrid gameGrid(window);
    PointSystem pointSystem(window);
    Shapes shapes(gameGrid, pointSystem, window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Yellow);
        shapes.update();
        gameGrid.draw();
        pointSystem.update();
        window.display();
    }
    return 0;
}
