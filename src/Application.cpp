#include "Application.hpp"
#include "Noise.hpp"

#include <iostream>

Application::Application(int width, int height)
    : WIDTH(width)
    , HEIGHT(height)
    , m_Window(sf::VideoMode(width, height), "Perlin Noise", sf::Style::Close)
{
    unsigned numOctaves = 2;
    float persistence = 0.5f;
    float zoom = 50.f;

    sf::Vertex vertex;
    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            float noise = 0.f;
            for (unsigned o = 0; o < numOctaves - 1; ++o)
            {
                float frequency = std::pow(2.f, (float) o);
                float amplitude = std::pow(persistence, (float) o);

                noise += Noise::getPerlinNoise(x * frequency / zoom, y * frequency / zoom) * amplitude;
            }

            float color = noise * 128.f + 128.f;
            color = (color > 255.f ? 255.f : (color < 0.f ? 0.f : color));

            vertex.position = { x, y };
            vertex.color = { color, color, color };
            m_Points.append(vertex);
        }
    }
}

void Application::run()
{
    while (m_Window.isOpen())
    {
        handleInput();
        update();
        draw();
    }
}

void Application::handleInput()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                m_Window.close();
                break;
            default:
                break;
        }
    }
}

void Application::update()
{

}

void Application::draw()
{
    m_Window.clear();
    m_Window.draw(m_Points);
    m_Window.display();
}
