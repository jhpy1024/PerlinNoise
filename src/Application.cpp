#include "Application.hpp"

#include <iostream>

Application::Application(int width, int height)
    : WIDTH(width)
    , HEIGHT(height)
    , m_Window(sf::VideoMode(width, height), "Perlin Noise", sf::Style::Close)
    , m_Camera({ 0.f, 0.f }, { WIDTH, HEIGHT })
    , m_Map(1000, 1000, 10)
    , m_MapRenderer(&m_Map)
{
    m_Camera.setBounds(sf::FloatRect(0.f, 0.f, m_Map.getWidth() * m_Map.getTileSize(), m_Map.getHeight() * m_Map.getTileSize()));

    m_Map.generate();
    m_MapRenderer.changeMap(&m_Map);
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
            case sf::Event::KeyPressed:
                handleKeyPress(event);
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
    m_Window.setView(m_Camera);

    m_MapRenderer.draw(m_Window);

    m_Window.display();
}

void Application::handleKeyPress(const sf::Event& event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Space:
            m_Map.generate();
            m_MapRenderer.changeMap(&m_Map);
            break;
        case sf::Keyboard::H:
        case sf::Keyboard::Left:
            m_Camera.moveLeft();
            break;
        case sf::Keyboard::L:
        case sf::Keyboard::Right:
            m_Camera.moveRight();
            break;
        case sf::Keyboard::J:
        case sf::Keyboard::Down:
            m_Camera.moveDown();
            break;
        case sf::Keyboard::K:
        case sf::Keyboard::Up:
            m_Camera.moveUp();
            break;
        case sf::Keyboard::I:
            m_Camera.zoomIn();
            break;
        case sf::Keyboard::O:
            m_Camera.zoomOut();
            break;
        case sf::Keyboard::P:
            m_Camera.reset();
            break;
        default:
            break;
    }
}
