#ifndef APPLICATION_HPP
#define APPLICATION_HPP

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
        const int WIDTH;
        const int HEIGHT;

        sf::RenderWindow m_Window;
        sf::VertexArray m_Points;
};

#endif

