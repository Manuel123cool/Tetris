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
