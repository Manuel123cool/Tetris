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

class PointSystem
{
private:
    int m_score = 0;
    int m_lines = 0;
    int m_level = 1;
    void drawText(sf::Vector2f pos, std::string string);
    sf::RenderWindow &m_window;
public:
    PointSystem(sf::RenderWindow &window);
    void plusLines(int lines);
    int frameSpeed();
    void gameOver();
    bool gameOverVar = false;
    void resetValues();
    void update();
};
