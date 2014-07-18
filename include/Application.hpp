#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "PerlinNoise.hpp"
#include "Camera.hpp"

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
        void loadTextures();
        void createMap();

        void handleKeyPress(const sf::Event& event);

    private:
        const int WIDTH;
        const int HEIGHT;
        const int MAP_WIDTH;
        const int MAP_HEIGHT;
        const float TILE_SIZE;

        sf::RenderWindow m_Window;
        Camera m_Camera;
        
        sf::Texture m_Grass;
        sf::Texture m_Water;
        sf::Texture m_Sand;
        sf::Texture m_Stone;
        std::vector<std::vector<sf::RectangleShape>> m_Sprites;

        PerlinNoise m_PerlinNoise;
};

#endif

