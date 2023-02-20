#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "core/Engine.hpp"
#include "shared/debug.hpp"

void closeGame(std::vector<void*> ptr);

int main()
{
    std::vector<void*> ptr;

    // Create window
    Game *game = new Game(sf::VideoMode(800, 800), "Aim Game", 60);
    sf::RenderWindow *window = game->getWindow();

    // Mouse
    sf::Vector2i mousePos;

    // Debugger
    Debug debug = Debug();

    ptr.push_back(game);
    ptr.push_back(window);

    // Game loop
    while (window->isOpen())
    {
        mousePos = sf::Mouse::getPosition(*window);

        // Handle events
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;

                case sf::Event::MouseButtonPressed:
                    game->shootEnemy(mousePos);
                    break;
            }
        }
        game->draw();
    }

    // Deallocate memory
    closeGame(ptr);

    return 0;
}

void closeGame(std::vector<void*> ptr)
{
    for (auto p : ptr)
    {
        delete p;
        p = nullptr;
    }
}
