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
#include "game_grid.h"
#include "iostream"
#include "point_system.h"

GameGrid::GameGrid(sf::RenderWindow &window) :
    m_window(window)
{
    int count = 0;
    for (int i{0}; i < 20; i++)
    {
        for (int j{0}; j < 10; j++)
        {
            m_shapeArray[count].setPosition(2.5 + j * 20, 2.5 + i * 20);
            m_shapeArray[count].setSize(sf::Vector2f(20.f, 20.f));
            m_shapeArray[count].setFillColor(sf::Color::Yellow);
            ++count;
        }
    }
}

void GameGrid::takeOn(int number, const sf::Color &color)
{
    m_shapeArray[number].setFillColor(color);
}

void GameGrid::takeOff(int number)
{
    m_shapeArray[number].setFillColor(sf::Color::Yellow);
}

void GameGrid::draw()
{
    for (int i{0}; i < 200; ++i)
    {
        m_window.draw(m_shapeArray[i]);
    }
}

bool GameGrid::checkIfOn(int number)
{
    if ( m_shapeArray[number].getFillColor() != sf::Color::Yellow)
        return true;
    else
        return false;
}

sf::Color GameGrid::getColor(int number)
{
    return  m_shapeArray[number].getFillColor();
}
