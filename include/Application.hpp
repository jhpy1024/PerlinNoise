#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Camera.hpp"
#include "Map.hpp"
#include "MapRenderer.hpp"

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

    private:
        const int WIDTH;
        const int HEIGHT;

        sf::RenderWindow m_Window;
        Camera m_Camera;

        Map m_Map;
        MapRenderer m_MapRenderer;
};

#endif

