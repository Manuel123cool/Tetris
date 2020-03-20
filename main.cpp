/*  Tetris: a simple tetris game
    Copyright (C) 2020  Manuel Maria Kümpel

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
