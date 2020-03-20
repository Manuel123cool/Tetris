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
#include <array>
#include <SFML/Graphics.hpp>
class GameGrid;
class PointSystem;

class Shapes
{
private:
    void positoningShape(int x, int y);
    void deletePositionShape(int x, int y);
    void dropShape();
    GameGrid &m_gameGrid;
    int checkLastBottomRow();
    int calcRightSightSpaceLeft();
    int m_shapePosX = 4;
    int m_shapePosY = 0;
    bool checkObsticleBellow(int x, int y);
    void moveShape();
    bool m_isClickt = false;
    void move();
    void checkClicket();
    bool m_shapeStart = true;
    bool checkCollision(int x, int y);
    int calcShapeWidth(int state);
    int m_currentState = 0;
    int m_currentShape = 0;
    int getRandomNumber(int min, int max);
    void rotateShape();
    int m_minusWidth = 0;
    bool checkRotateCollision(int state);
    bool checkRotateObsticle(int state);
    void destroyIfRow();
    void checkLost();
    bool m_gameOver = false;
    sf::RenderWindow &m_window;
    PointSystem &m_pointSystem;
public:
    void update();
    Shapes(GameGrid &gameGrid, PointSystem &pointSystem, sf::RenderWindow &window);
private:
    const int m_shapesPos[7][5][4] =
    {
        {
            //O Block
            {0,1,10, 11},
            {-1}
        },
        {
            //I Block
            {0, 1, 2, 3},
            {1, 11, 21, 31},
            {-1}
        },
        {
            //J Block
            {0, 10, 11, 12},
            {1, 2, 11, 21},
            {0, 1, 2, 12},
            {1, 11, 21, 20},
            {-1}
        },
        {
            //L Block
            {10, 11, 12, 2},
            {1, 11, 21, 22},
            {0, 10, 1, 2},
            {0, 1, 11, 21},
            {-1}
        },
        {
            //S Block
            {10, 11, 1, 2},
            {0, 10, 11, 21},
            {-1}
        },
        {
            //T Block
            {10, 11, 12, 1},
            {0, 10, 20, 11},
            {0, 1, 2, 11},
            {1, 11, 21, 10},
            {-1}
        },
        {
            //Z Block
            {0, 1, 11, 12},
            {1, 11, 10, 20},
            {-1}
        }
    };
};
