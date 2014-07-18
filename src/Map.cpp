#include "Map.hpp"

Map::Map(int width, int height, int tileSize)
    : WIDTH(width)
    , HEIGHT(height)
    , TILE_SIZE(tileSize)
    , m_Tiles(nullptr)
{
}

Map::Map(const Map& map)
    : WIDTH(map.WIDTH)
    , HEIGHT(map.HEIGHT)
    , TILE_SIZE(map.TILE_SIZE)
    , m_Tiles(nullptr)
{
}

Map::~Map()
{
    for (int y = 0; y < HEIGHT; ++y)
        delete [] m_Tiles[y];

    delete [] m_Tiles;
    m_Tiles = nullptr;
}

void Map::generate()
{
    m_PerlinNoise.setSeed(rand() / 1000);

    m_Tiles = new TileType*[HEIGHT];

    for (int y = 0; y < HEIGHT; ++y)
    {
        m_Tiles[y] = new TileType[WIDTH];

        for (int x = 0; x < WIDTH; ++x)
        {
            float noise = m_PerlinNoise(x, y, 5.f, 0.5f, 2);
            float color = noise * 128.f + 128.f;
            if (color > 255.f) color = 255.f;
            else if (color < 0.f) color = 0.f;

            if (color < 140.f)
                m_Tiles[y][x] = WATER;
            else if (color < 180.f)
                m_Tiles[y][x] = SAND;
            else if (color >= 195.f && color <= 205.f)
                m_Tiles[y][x] = STONE;
            else if (color < 220.f)
                m_Tiles[y][x] = GRASS;
            else 
                m_Tiles[y][x] = STONE;
        }
    }
}

int Map::getWidth() const
{
    return WIDTH;
}

int Map::getHeight() const
{
    return HEIGHT;
}

int Map::getTileSize() const
{
    return TILE_SIZE;
}
