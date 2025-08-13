#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({480, 640}), "Tetris in C++");

    const sf::Font font("src/assets/arial.ttf");
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
        window.display();
    }
}