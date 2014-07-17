#include "Application.hpp"

Application::Application(int width, int height)
    : WIDTH(width)
    , HEIGHT(height)
    , m_Window(sf::VideoMode(width, height), "Perlin Noise", sf::Style::Close)
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

    for (auto& sprite : m_Sprites)
        m_Window.draw(sprite);

    m_Window.display();
}

void Application::handleKeyPress(const sf::Event& event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Space:
            createMap();
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
    m_Sprites.reserve((WIDTH / 50) * (HEIGHT / 50));

    sf::RectangleShape sprite;
    for (int x = 0; x < WIDTH / 10; ++x)
    {
        for (int y = 0; y < HEIGHT / 10; ++y)
        {
            float noise = m_PerlinNoise(x, y, 5.f, 0.5f, 2);
            float color = noise * 128.f + 128.f;
            if (color > 255.f) color = 255.f;
            else if (color < 0.f) color = 0.f;

            sprite.setPosition(x * 10.f, y * 10.f);
            sprite.setSize({ 10.f, 10.f });

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

            m_Sprites.push_back(sprite);
        }
    }
}
