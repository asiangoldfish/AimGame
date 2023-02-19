#include <vector>

#include <SFML/Graphics.hpp>
#include "core/Engine.hpp"

void closeGame(std::vector<void*> ptr);

int main()
{
    std::vector<void*> ptr;

    // Create window
    Game *game = new Game(sf::VideoMode(1280, 720), "Aim Game", 60);
    sf::RenderWindow *window = game->getWindow();

    ptr.push_back(game);
    ptr.push_back(window);

    // Game loop
    while (window->isOpen())
    {
        // Handle events
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
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
