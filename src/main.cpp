#include <SFML/Graphics.hpp>
#include "common/Types.hpp"
#include <fmt/format.h>

sf::VertexArray drawGrid(sf::RenderWindow& win, int rows, int cols){
    int numLines = rows+cols-2;
    sf::VertexArray grid(sf::PrimitiveType::Lines, 2*(numLines));
    win.setView(win.getDefaultView());
    auto size = win.getView().getSize();
    float rowH = size.y/rows;
    float colW = size.x/cols;
    
    // row separators
    for (int i=0; i < rows-1; i++){
        int r = i+1;
        float rowY = rowH*r;
        grid[i*2].position = {0, rowY};
        grid[i*2+1].position = {size.x, rowY};
    }
    // column separators
    for (int i=rows-1; i < numLines; i++){
        int c = i-rows+2;
        float colX = colW*c;
        grid[i*2].position = {colX, 0};
        grid[i*2+1].position = {colX, size.y};
    }
    return grid;
}

int main()
{   
    unsigned int height = static_cast<int>(VideoSize::HEIGHT);
    unsigned int width = static_cast<int>(VideoSize::WIDTH);
    sf::RenderWindow window(sf::VideoMode({height, width}), "Tetris in C++");
 
    const std::string fontPath = "src/assets/fixedsys.ttf";
 
    sf::Font font;
    if (!font.openFromFile(fontPath)) {
        fmt::print("Error: cannot load font from: {}\n", fontPath);
        return -1;
    }
 
    sf::Text text(font, "Hello SFML", 50);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.draw(text);
        window.draw(drawGrid(window, 10, 20));
        window.display();
    }
}