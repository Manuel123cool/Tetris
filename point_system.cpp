#include <SFML/Graphics.hpp>
#include "point_system.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

PointSystem::PointSystem(sf::RenderWindow &window) :
    m_window(window)
{
}

void PointSystem::plusLines(int lines)
{
    m_lines += lines;
    switch (lines)
    {
        case 1:
            m_score += 50 *(m_level + 1);
            break;
        case 2:
            m_score += 150 *(m_level + 1);
            break;
        case 3:
            m_score += 350 *(m_level + 1);
            break;
        case 4:
            m_score += 1000 *(m_level + 1);
            break;
    }

    if (m_lines % 10 == 0 && lines)
        m_level++;
}

void PointSystem::drawText(sf::Vector2f pos, std::string myString)
{
    sf::Font font;
    if (!font.loadFromFile("futura-normal_[allfont.de].ttf"))
    {
        std::cerr << "Error loading font\n";
    }

    sf::Text text;
    text.setFont(font);
    text.setString(myString);
    text.setCharacterSize(22);
    text.setPosition(pos);
    text.setColor(sf::Color::Black);

    m_window.draw(text);
}

int PointSystem::frameSpeed()
{
    return 80 - m_level * 5;
}
void PointSystem::update()
{
    sf::RectangleShape rectangle(sf::Vector2f(100.f, 405));
    rectangle.setPosition(sf::Vector2f(205.f, 0));

    m_window.draw(rectangle);

    drawText(sf::Vector2f(210.f, 10.f), "Score: ");
    drawText(sf::Vector2f(210.f, 35.f), std::to_string(m_score));
    drawText(sf::Vector2f(210.f, 60.f), "Lines: ");
    drawText(sf::Vector2f(210.f, 85.f), std::to_string(m_lines));
    drawText(sf::Vector2f(210.f, 110.f), "Level: ");
    drawText(sf::Vector2f(210.f, 135.f), std::to_string(m_level));

    if (gameOverVar)
        gameOver();
}

void PointSystem::gameOver()
{
    sf::RectangleShape rect(sf::Vector2f(200.f, 400.f));
    rect.setPosition(sf::Vector2f(2.5, 2.5));
    rect.setFillColor(sf::Color::Black);
    m_window.draw(rect);

    sf::Font font;
    if (!font.loadFromFile("futura-normal_[allfont.de].ttf"))
    {
        std::cerr << "Error loading font\n";
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Game over");
    text.setCharacterSize(30);
    text.setPosition(sf::Vector2f(35.f, 50.f));
    text.setColor(sf::Color::White);

    m_window.draw(text);
}

void PointSystem::resetValues()
{
    m_lines = 0;
    m_score = 0;
    m_level = 1;
}

