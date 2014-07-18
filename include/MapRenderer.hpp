#ifndef MAP_RENDERER_HPP
#define MAP_RENDERER_HPP

#include "Map.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class MapRenderer
{
    public:
        MapRenderer(Map* map);

        void draw(sf::RenderTarget& target);
        void changeMap(Map* newMap);

    private:
        void buildVertexArray();

    private:
        Map* m_Map;

        sf::VertexArray m_Verts;
        sf::Texture m_TileSheet;

        // Stores the texture coordinates of the tiles in the following format:
        // TEX_COORDS[TileType] = { topLeft, topRight, bottomLeft, bottomRight }
        std::vector<std::vector<sf::Vector2f>> TEX_COORDS;
};

#endif
