#include <SFML/Graphics.hpp>
#include "common/Types.hpp"
#include <fmt/format.h>
#include <vector>

void drawCell(sf::RenderWindow &window, std::vector<std::vector<unsigned char>> &gameGrid)
{
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
    for (unsigned char i = 0; i < ROWS; i++)
    {
        for (unsigned char j = 0; j < COLUMNS; j++)
        {
            sf::Vector2f cellPosition(CELL_SIZE * i, CELL_SIZE * j);
            switch (gameGrid[i][j])
            {
            case 1:
                cell.setFillColor(sf::Color(255, 255, 0));
                cell.setPosition(cellPosition);
                window.draw(cell);
                break;
            case 2:
                cell.setFillColor(sf::Color(0, 255, 0));
                cell.setPosition(cellPosition);
                window.draw(cell);
                break;
            case 3:
                cell.setFillColor(sf::Color(0, 0, 139));
                cell.setPosition(cellPosition);
                window.draw(cell);
                break;
            case 4:
                cell.setFillColor(sf::Color(255, 165, 0));
                cell.setPosition(cellPosition);
                window.draw(cell);
                break;
            default:
                cell.setFillColor(sf::Color(0, 0, 25));
                cell.setPosition(cellPosition);
                window.draw(cell);
                break;
            }
        }
    }
};

void resetGrid(unsigned char &x, unsigned char &y, std::vector<std::vector<unsigned char>> &gameGrid, unsigned char type)
{
    switch (type)
    {
    case 1:
        gameGrid[x][y] = 0;
        gameGrid[x + 1][y] = 0;
        gameGrid[x][y + 1] = 0;
        gameGrid[x + 1][y + 1] = 0;
        break;
    case 2:
        gameGrid[x][y] = 0;
        gameGrid[x - 1][y] = 0;
        gameGrid[x + 1][y] = 0;
        gameGrid[x + 2][y] = 0;
        break;
    }
};

void drawTetrimino(unsigned char &x, unsigned char &y, std::vector<std::vector<unsigned char>> &gameGrid, unsigned char type)
{
    switch (type)
    {
    case 1: // Tetrimino O
        gameGrid[x][y] = 1;
        gameGrid[x + 1][y] = 1;
        gameGrid[x][y + 1] = 1;
        gameGrid[x + 1][y + 1] = 1;
        break;
    case 2: // Tetrimino I
        gameGrid[x][y] = 2;
        gameGrid[x - 1][y] = 2;
        gameGrid[x + 1][y] = 2;
        gameGrid[x + 2][y] = 2;
        break;
    case 3: // Tetrimino J
        gameGrid[x + 1][y] = 3;
        gameGrid[x + 1][y + 1] = 3;
        gameGrid[x + 1][y + 2] = 3;
        gameGrid[x][y + 2] = 3;
        break;
    case 4: // Tetrimino L
        gameGrid[x][y] = 4;
        gameGrid[x][y + 1] = 4;
        gameGrid[x][y + 2] = 4;
        gameGrid[x + 1][y + 2] = 4;
    }
};

bool pieceCollision(unsigned char &x, unsigned char &y, std::vector<std::vector<unsigned char>> &gameGrid, unsigned char &shape)
{
    switch (shape)
    {
    case (1):
        if (y >= COLUMNS - 2)
            return true; // Y position of piece is out of bounds
        if (gameGrid[x][y + 2] != 0 || gameGrid[x + 1][y + 2] != 0)
            return true;
        return false;
        break;
    case (2):
        if (y >= COLUMNS - 1)
            return true;
        if (gameGrid[x][y + 1] != 0 || gameGrid[x - 1][y + 1] != 0 ||
            gameGrid[x + 1][y + 1] != 0 || gameGrid[x + 2][y + 1] != 0)
            return true;
        return false;
        break;
    }
    return false;
};

void tetriminoDropInteraction(unsigned char &x, unsigned char &y, std::vector<std::vector<unsigned char>> &gameGrid, unsigned char &shape)
{
    switch (shape)
    {
    case 1:
        if (!pieceCollision(x, y, gameGrid, shape))
        {
            resetGrid(x, y, gameGrid, shape);
            y++;
            drawTetrimino(x, y, gameGrid, shape);
        }
        else
        {
            y = 0;
            shape++;
        }
        break;
    case 2:
        if (!pieceCollision(x, y, gameGrid, shape))
        {
            resetGrid(x, y, gameGrid, shape);
            y++;
            drawTetrimino(x, y, gameGrid, shape);
        }
        else
        {
            y = 0;
            shape = 1;
        }
        break;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({WIN_W, WIN_H}), "Tetris in C++");
    sf::View view(sf::FloatRect({0.f, 0.f}, {float(BOARD_W), float(BOARD_H)}));
    window.setView(view);

    std::vector<std::vector<unsigned char>> gameGrid(ROWS, std::vector<unsigned char>(COLUMNS));

    sf::Clock clock;
    const float fallInterval = 0.8f;

    unsigned char x = 4; // top middle of the grid
    unsigned char y = 0;
    unsigned char shape = 1;

    drawTetrimino(x, y, gameGrid, shape);

    sf::Font font;
    const std::string fontPath = "src/assets/fixedsys.ttf";
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
        while (clock.getElapsedTime().asSeconds() > fallInterval)
        {
            clock.restart();
            tetriminoDropInteraction(x, y, gameGrid, shape);
        }
        window.clear();
        drawCell(window, gameGrid);
        window.display();
    }
}