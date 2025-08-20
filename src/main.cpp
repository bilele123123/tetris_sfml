#include <SFML/Graphics.hpp>
#include "common/Types.hpp"
#include <fmt/format.h>

void drawCell(sf::RenderWindow &window)
{
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
    cell.setFillColor(sf::Color(0, 0, 25));
    for (unsigned char i = 0; i < ROWS; i++)
    {
        for (unsigned char j = 0; j < COLUMNS; j++)
        {
            sf::Vector2f cellPosition(CELL_SIZE * i, CELL_SIZE * j);
            cell.setPosition(cellPosition);
            window.draw(cell);
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({WIN_W, WIN_H}), "Tetris in C++");
    sf::FloatRect rect({0.f, 0.f}, {float(BOARD_W), float(BOARD_H)});
    sf::View view(rect);
    window.setView(view);
    const std::string fontPath = "src/assets/fixedsys.ttf";

    sf::Font font;
    if (!font.openFromFile(fontPath))
    {
        fmt::print("Error: cannot load font from: {}\n", fontPath);
        return -1;
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        drawCell(window);
        window.display();
    }
}