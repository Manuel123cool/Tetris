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
#include <array>
#include <iostream>
#include "shapes.h"
#include "game_grid.h"
#include <random> // for std::mt19937
#include <ctime> // for std::time
#include "point_system.h"

namespace MyRandom
{
	// Initialize our mersenne twister with a random seed based on the clock (once at system startup)
	std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
}

Shapes::Shapes(GameGrid &gameGrid, PointSystem &pointSystem,  sf::RenderWindow &window) :
    m_gameGrid(gameGrid), m_pointSystem(pointSystem), m_window(window)
{

}

void Shapes::positoningShape(int x, int y)
{
    sf::Color color;
    switch (m_currentShape)
    {
        case 0:
            color = sf::Color::Black;
            break;
        case 1:
            color = sf::Color::White;
            break;
        case 2:
            color = sf::Color::Red;
            break;
        case 3:
            color = sf::Color::Blue;
            break;
        case 4:
            color = sf::Color::Magenta;
            break;
        case 5:
            color = sf::Color::Cyan;
            break;
        case 6:
            color = sf::Color(191, 182, 63);
            break;
    }
    int movedShape[4];
    for (int i{0}; i < 4; ++i)
    {
        movedShape[i] = (m_shapesPos[m_currentShape][m_currentState][i] + x) + (y * 10);
        m_gameGrid.takeOn(movedShape[i], color);
    }
}


void Shapes::deletePositionShape(int x, int y)
{
    int deleteShape[4];
    for (int i{0}; i < 4; ++i)
    {
        deleteShape[i] = (m_shapesPos[m_currentShape][m_currentState][i] + x) + (y * 10);
        m_gameGrid.takeOff(deleteShape[i]);
    }
}

int Shapes::checkLastBottomRow()
{
    int countHeight = 0;
    int count = -10;
    while (count < 50)
    {
        count += 10;
        for (int j{0}; j < 4; ++j)
        {
            int pos = m_shapesPos[m_currentShape][m_currentState][j];
            if (pos >= count)
            {
                countHeight++;
                break;
            }
        }
    }
    return 20 - countHeight;
}


bool Shapes::checkObsticleBellow(int x, int y)
{
    for (int i{0}; i < 4; ++i)
    {
        int belowPos = (m_shapesPos[m_currentShape][m_currentState][i] + x) + (y * 10) + 10;
        if (m_gameGrid.checkIfOn(belowPos))
        {
            int count = 0;
            for (int j{0}; j < 4; ++j)
            {
                int posInRect = (m_shapesPos[m_currentShape][m_currentState][j] + x) + (y * 10);
                if (posInRect == belowPos)
                {
                    break;
                }
                else
                {
                    ++count;
                }
            }
            if (count == 4)
                return true;

        }
    }
    return false;
}

void Shapes::dropShape()
{
    static int countFrames = 0;
    static bool startMove = true;
    int frameSpeed = m_pointSystem.frameSpeed();
    frameSpeed = m_pointSystem.frameSpeed();
    if (m_shapePosY == 0)
    {
        if (startMove)
        {
            deletePositionShape(m_shapePosX, m_shapePosY);
            m_shapePosX = 4;
            m_currentShape = getRandomNumber(0, 6);
            m_currentState = 0;
            positoningShape(m_shapePosX, m_shapePosY);
            destroyIfRow();
        }
        startMove = false;
    }
    ++countFrames;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        frameSpeed = 5;
    else
        frameSpeed = m_pointSystem.frameSpeed();

    if (countFrames > frameSpeed)
        countFrames = 0;

    if (countFrames == frameSpeed)
    {
        if (checkObsticleBellow(m_shapePosX, m_shapePosY))
        {
            checkLost();
            m_shapePosY = 0;
            startMove = true;
        }
        if (m_shapePosY == checkLastBottomRow())
        {
            m_shapePosY = 0;
            startMove = true;
        }
        if (!startMove)
        {
            deletePositionShape(m_shapePosX,  m_shapePosY);
            ++m_shapePosY;
            positoningShape(m_shapePosX, m_shapePosY);
        }
        countFrames = 0;
    }
}

int Shapes::calcShapeWidth(int state)
{
    int biggestWidth = 0;
    int currentWidth = 0;
    int tenValue = 0;
    int pos = 0;
    for (int i{0}; i < 4; ++i)
    {
        tenValue = 0;
        for (int j{10}; j < 50; j += 10)
        {
            pos = m_shapesPos[m_currentShape][state][i];
            if ((pos < j) && (pos >= j - 10))
                tenValue = j - 10;

        }
        currentWidth = m_shapesPos[m_currentShape][state][i] - tenValue + 1;
            if (currentWidth > biggestWidth)
                biggestWidth = currentWidth;
    }

    int minusPos = 0;
    for (int i{0}; i < 5; ++i)
    {
        for (int j{0}; j < 40; j = j + 10 + i)
        {
            for (int k{0}; k < 4; ++k)
            {
                int pos1 = m_shapesPos[m_currentShape][state][k];
                if (j == pos1)
                {
                    m_minusWidth = minusPos;
                    return biggestWidth;
                }
            }
        }
        minusPos++;
    }
}

bool Shapes::checkCollision(int x, int y)
{
    if (x > (10 - calcShapeWidth(m_currentState)))
        return true;
    if (x < 0 - m_minusWidth)
        return true;


    for (int i{0}; i < 4; ++i)
    {
        int besidePosLeft = (m_shapesPos[m_currentShape][m_currentState][i] + x) + (y * 10);
        if (m_gameGrid.checkIfOn(besidePosLeft))
        {
            int count = 0;
            for (int j{0}; j < 4; ++j)
            {
                int posInRect = (m_shapesPos[m_currentShape][m_currentState][j] + x) + (y * 10) + 1;
                if ((posInRect == besidePosLeft))
                    break;
                else
                    ++count;
            }
            if (count == 4)
                return true;
        }
    }

    for (int i{0}; i < 4; ++i)
    {
        int besidePosRight = (m_shapesPos[m_currentShape][m_currentState][i] + x) + (y * 10);
        if (m_gameGrid.checkIfOn(besidePosRight))
        {
            int count = 0;
            for (int j{0}; j < 4; ++j)
            {
                int posInRect = (m_shapesPos[m_currentShape][m_currentState][j] + x) + (y * 10) - 1;
                if ((posInRect == besidePosRight))
                    break;
                else
                    ++count;
            }
            if (count == 4)
                return true;
        }
    }
    return false;
}

void Shapes::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        deletePositionShape(m_shapePosX, m_shapePosY);
        if (!checkCollision(m_shapePosX - 1, m_shapePosY))
            m_shapePosX--;
        positoningShape(m_shapePosX, m_shapePosY);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        deletePositionShape(m_shapePosX, m_shapePosY);
        if (!checkCollision(m_shapePosX + 1, m_shapePosY))
            m_shapePosX++;
        positoningShape(m_shapePosX, m_shapePosY);
    }
}

void Shapes::checkClicket()
{
    bool checkClickt = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        checkClickt = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        checkClickt = true;

    if (!checkClickt)
        m_isClickt = false;

    else
        m_isClickt = true;
}

int Shapes::getRandomNumber(int min, int max)
{
	std::uniform_int_distribution<> die(min, max); // we can create a distribution in any function that needs it
	return die(MyRandom::mersenne); // and then generate a random number from our global generator
}

void Shapes::moveShape()
{
    static int countFrames = 0;
    ++countFrames;

    if (!m_isClickt)
    {
        move();
        countFrames = 0;
    }
    else if (countFrames == 10)
    {
        move();
        countFrames = 0;
    }
    checkClicket();
}

void Shapes::rotateShape()
{
    static bool isClicket = false;
    bool wasClicket = isClicket;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        isClicket = true;
    else
        isClicket = false;

    if (isClicket && !wasClicket && !checkRotateCollision(m_currentState + 1))
    {
        deletePositionShape(m_shapePosX, m_shapePosY);
        m_currentState++;
        if (m_shapesPos[m_currentShape][m_currentState][0] == -1)
            m_currentState = 0;
        positoningShape(m_shapePosX, m_shapePosY);
    }
}

bool Shapes::checkRotateObsticle(int state)
{
    for (int i{0}; i < 4; ++i)
    {
        if (m_gameGrid.checkIfOn(
            (m_shapesPos[m_currentShape][state][i] + m_shapePosX) + (m_shapePosY * 10)))
        {
            int count = 0;
            for (int j{0}; j < 4; ++j)
            {
                if (((m_shapesPos[m_currentShape][state][i] + m_shapePosX) + (m_shapePosY * 10)) ==
                    ((m_shapesPos[m_currentShape][m_currentState][j] + m_shapePosX) + (m_shapePosY * 10)))
                {
                    break;
                }
                else
                {
                    count++;
                }
            }
            if (count == 4)
             return true;
        }
    }
    return false;
}

bool Shapes::checkRotateCollision(int state)
{
    if (m_shapesPos[m_currentShape][state][0] == -1)
            state = 0;

    if (m_shapePosX > (10 - calcShapeWidth(state)))
        return true;

    if (m_shapePosX < 0 - m_minusWidth)
        return true;

    int tempState = m_currentState;
    m_currentState = state;
    if (m_shapePosY > checkLastBottomRow())
    {
        m_currentState = tempState;
        return true;
    }
    m_currentState = tempState;

    if (checkRotateObsticle(state))
        return true;

    return false;
}

void Shapes::destroyIfRow()
{
    bool posOfRects[200] = {0};
    for (int i{0}; i < 200; ++i)
    {
        if (m_gameGrid.checkIfOn(i))
        {
            int count1 = 0;
            for (int j{0}; j < 4; ++j)
            {
                int currentPos = (m_shapesPos[m_currentShape][m_currentState][j] + m_shapePosX) + (m_shapePosY * 10);
                if (i == currentPos)
                    break;
                else
                    count1++;
            }
            if (count1 == 4)
            {
                posOfRects[i] = true;
            }

        }
    }

    int whichRow[4] = {0};
    for (auto &row : whichRow)
        row = -1;

    int count1 = 0;
    for (int i{0}; i < 200; i += 10)
    {
        int count2 = 0;
        for (int j{i}; j < i + 10; j++)
        {
            if (posOfRects[j])
                count2++;

            if(count2 == 10)
            {
                if (i == 0)
                    whichRow[count1] = 0;
                else
                    whichRow[count1] = i / 10;

                count1++;
            }
        }
    }

    for (auto &row : whichRow)
    {
        if (row != -1)
        {
            for (int i{0}; i < 10; ++i)
            {
                m_gameGrid.takeOff(row * 10 + i);
            }
        }
    }

    for (auto &row : whichRow)
    {
        if (row != -1)
        {
            for (int i{row * 10 - 1}; i >= 0; i--)
            {
                if (posOfRects[i])
                {
                    sf::Color color = m_gameGrid.getColor(i);
                    m_gameGrid.takeOff(i);
                    m_gameGrid.takeOn(i + 10, color);
                }
            }
        }
    }

    int count2 = 0;
    for (auto &row : whichRow)
    {
        if (row != -1)
            count2++;
    }
    m_pointSystem.plusLines(count2);
}

void Shapes::checkLost()
{
    int highestPos = 0;
    for (int i{0}; i < 4;  ++i)
    {
        int currentPos = (m_shapesPos[m_currentShape][m_currentState][i] + m_shapePosX) + (m_shapePosY * 10);
        if (currentPos > highestPos)
            highestPos = currentPos;
    }
    int highestRow = highestPos / 10;

    int currentShapeHeight = 20 - checkLastBottomRow();
    if(highestRow - currentShapeHeight < 0)
    {
        m_gameOver = true;
        for (int i{0}; i < 200; i++)
            m_gameGrid.takeOff(i);
    }
}

void Shapes::update()
{
    if (!m_gameOver)
    {
        dropShape();
        moveShape();
        rotateShape();
    }
    else
    {
        m_pointSystem.gameOverVar = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            m_pointSystem.gameOverVar = false;
            m_pointSystem.resetValues();
            m_gameOver = false;
        }
    }
}





