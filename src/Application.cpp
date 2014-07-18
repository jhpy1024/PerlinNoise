#include "Application.hpp"

#include <iostream>

Application::Application(int width, int height)
    : WIDTH(width)
    , HEIGHT(height)
    , MAP_WIDTH(500)
    , MAP_HEIGHT(MAP_WIDTH)
    , TILE_SIZE(10.f)
    , m_Window(sf::VideoMode(width, height), "Perlin Noise", sf::Style::Close)
    , m_Camera({ 0.f, 0.f }, { WIDTH, HEIGHT })
{
    loadTextures();
    createMap();

    m_Camera.setBounds(sf::FloatRect(0.f, 0.f, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE));
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

    unsigned numTilesDrawn = 0;

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (m_Camera.pointInView(x * TILE_SIZE, y * TILE_SIZE))
            {
                m_Window.draw(m_Sprites[y][x]);
                ++numTilesDrawn;
            }
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
