#include "Application.hpp"

#include <iostream>

Application::Application(int width, int height)
    : WIDTH(width)
    , HEIGHT(height)
    , MAP_WIDTH(500)
    , MAP_HEIGHT(MAP_WIDTH)
    , TILE_SIZE(10.f)
    , ZOOM_FACTOR(0.1f)
    , m_Window(sf::VideoMode(width, height), "Perlin Noise", sf::Style::Close)
    , m_View({ WIDTH / 2.f, HEIGHT / 2.f }, { WIDTH, HEIGHT })
{
    loadTextures();
    createMap();
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
    m_Window.setView(m_View);

    for (unsigned y = 0; y < m_Sprites.size(); ++y)
    {
        for (unsigned x = 0; x < m_Sprites[y].size(); ++x)
        {
            auto viewTopLeft = sf::Vector2f(m_View.getCenter().x - m_View.getSize().x / 2.f, m_View.getCenter().y - m_View.getSize().y / 2.f);

            bool outOfBounds = x * TILE_SIZE < viewTopLeft.x
                            || y * TILE_SIZE < viewTopLeft.y
                            || x * TILE_SIZE > viewTopLeft.x + m_View.getSize().x
                            || y * TILE_SIZE > viewTopLeft.y + m_View.getSize().y;

            if (!outOfBounds)
                m_Window.draw(m_Sprites[y][x]);
        }
    }

    m_Window.display();
}

void Application::handleKeyPress(const sf::Event& event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Space:
            createMap();
            break;
        case sf::Keyboard::H:
        case sf::Keyboard::Left:
            moveLeft();
            break;
        case sf::Keyboard::L:
        case sf::Keyboard::Right:
            moveRight();
            break;
        case sf::Keyboard::J:
        case sf::Keyboard::Down:
            moveDown();
            break;
        case sf::Keyboard::K:
        case sf::Keyboard::Up:
            moveUp();
            break;
        case sf::Keyboard::I:
            zoomIn();
            break;
        case sf::Keyboard::O:
            zoomOut();
            break;
        case sf::Keyboard::P:
            resetZoom();
            break;
        default:
            break;
    }
}

void Application::moveUp()
{
    auto viewTopLeft = sf::Vector2f(m_View.getCenter().x - m_View.getSize().x / 2.f, m_View.getCenter().y - m_View.getSize().y / 2.f);

    if (viewTopLeft.y > 0.f)
        m_View.move(0.f, -TILE_SIZE);
}

void Application::moveDown()
{
    auto viewTopLeft = sf::Vector2f(m_View.getCenter().x - m_View.getSize().x / 2.f, m_View.getCenter().y - m_View.getSize().y / 2.f);

    if (viewTopLeft.y + m_View.getSize().y < TILE_SIZE * MAP_HEIGHT)
        m_View.move(0.f, TILE_SIZE);
}

void Application::moveLeft()
{
    auto viewTopLeft = sf::Vector2f(m_View.getCenter().x - m_View.getSize().x / 2.f, m_View.getCenter().y - m_View.getSize().y / 2.f);

    if (viewTopLeft.x > 0.f)
        m_View.move(-TILE_SIZE, 0.f);
}

void Application::moveRight()
{
    auto viewTopLeft = sf::Vector2f(m_View.getCenter().x - m_View.getSize().x / 2.f, m_View.getCenter().y - m_View.getSize().y / 2.f);

    if (viewTopLeft.x + m_View.getSize().x < TILE_SIZE * MAP_WIDTH)
        m_View.move(TILE_SIZE, 0.f);
}

void Application::zoomIn()
{
    m_View.zoom(1.f - ZOOM_FACTOR);
}

void Application::zoomOut()
{
    m_View.zoom(1.f + ZOOM_FACTOR);
}

void Application::resetZoom()
{
    m_View.setSize(WIDTH, HEIGHT);
}

void Application::loadTextures()
{
    m_Grass.loadFromFile("res/grass.png");
    m_Water.loadFromFile("res/water.png");
    m_Sand.loadFromFile("res/sand.png");
    m_Stone.loadFromFile("res/stone.png");
}

void Application::createMap()
{
    m_PerlinNoise.setSeed((float) rand() / 1000);

    m_Sprites.clear();

    sf::RectangleShape sprite;
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        std::vector<sf::RectangleShape> row;

        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            float noise = m_PerlinNoise(x, y, 5.f, 0.5f, 2);
            float color = noise * 128.f + 128.f;
            if (color > 255.f) color = 255.f;
            else if (color < 0.f) color = 0.f;

            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            sprite.setSize({ TILE_SIZE, TILE_SIZE });

            if (color < 140)
                sprite.setTexture(&m_Water);
            else if (color < 180)
                sprite.setTexture(&m_Sand);
            else if (color >= 195 && color <= 205)
                sprite.setTexture(&m_Stone);
            else if (color < 220)
                sprite.setTexture(&m_Grass);
            else 
                sprite.setTexture(&m_Stone);

            row.push_back(sprite);
        }

        m_Sprites.push_back(row);
    }
}
