#ifndef MAP_HPP
#define MAP_HPP

#include "PerlinNoise.hpp"
#include <SFML/Graphics.hpp>

class Map
{
    friend class MapRenderer;

    enum TileType { GRASS, SAND, STONE, WATER };

    public:
        Map(int width, int height, int tileSize);
        Map(const Map& map);
        ~Map();

        void generate();

        int getWidth() const;
        int getHeight() const;
        int getTileSize() const;

    private:
        const int WIDTH;
        const int HEIGHT; 
        const int TILE_SIZE;

        TileType** m_Tiles;

        PerlinNoise m_PerlinNoise;
};

#endif
