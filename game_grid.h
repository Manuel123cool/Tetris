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
