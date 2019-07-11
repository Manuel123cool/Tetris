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
