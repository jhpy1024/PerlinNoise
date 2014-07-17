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
        void loadTextures();
        void createMap();

        void handleKeyPress(const sf::Event& event);
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void zoomIn();
        void zoomOut();
        void resetZoom();

    private:
        const int WIDTH;
        const int HEIGHT;
        const int MAP_WIDTH;
        const int MAP_HEIGHT;
        const float TILE_SIZE;
        const float ZOOM_FACTOR;

        sf::RenderWindow m_Window;
        sf::View m_View;
        
        sf::Texture m_Grass;
        sf::Texture m_Water;
        sf::Texture m_Sand;
        sf::Texture m_Stone;
        std::vector<std::vector<sf::RectangleShape>> m_Sprites;

        PerlinNoise m_PerlinNoise;
};

#endif

