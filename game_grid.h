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

#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class GameGrid
{
private:
    std::array<sf::RectangleShape , 200> m_shapeArray;
    sf::RenderWindow &m_window;
public:
    void takeOn(int number, const sf::Color &color);
    void takeOff(int number);
    void draw();
    bool checkIfOn(int number);
    sf::Color getColor(int number);
    GameGrid(sf::RenderWindow &window);
};
