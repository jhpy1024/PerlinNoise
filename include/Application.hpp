#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "PerlinNoise.hpp"

#include <SFML/Graphics.hpp>

class Application
{
    public:
        Application(int width, int height);

        void run();
        void handleInput();
        void update();
        void draw();

    private:
        void handleKeyPress(const sf::Event& event);
        void loadTextures();
        void createMap();

    private:
        const int WIDTH;
        const int HEIGHT;

        sf::RenderWindow m_Window;
        
        sf::Texture m_Grass;
        sf::Texture m_Water;
        std::vector<sf::RectangleShape> m_Sprites;

        PerlinNoise m_PerlinNoise;
};

#endif

