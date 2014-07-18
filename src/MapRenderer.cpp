#include "MapRenderer.hpp"

MapRenderer::MapRenderer(Map* map)
    : m_Map(map)
    , m_Verts(sf::Quads)
{
    m_TileSheet.loadFromFile("res/tilesheet.png");

    TEX_COORDS = 
    {   // TODO: Remove magic numbers
        { { 0.f, 0.f } , { 10.f, 0.f }, { 0.f, 10.f }, { 10.f, 10.f } },  // Grass
        { { 10.f, 0.f }, { 20.f, 0.f }, { 10.f, 10.f }, { 20.f, 10.f } }, // Sand
        { { 20.f, 0.f }, { 30.f, 0.f }, { 20.f, 10.f }, { 30.f, 10.f } }, // Stone
        { { 30.f, 0.f }, { 40.f, 0.f }, { 30.f, 10.f }, { 40.f, 10.f } }  // Water
    };

    buildVertexArray();
}

void MapRenderer::draw(sf::RenderTarget& target)
{
    target.draw(m_Verts, &m_TileSheet);
}

void MapRenderer::changeMap(Map* newMap)
{
    m_Map = newMap;
    buildVertexArray();
}

void MapRenderer::buildVertexArray()
{
    if (m_Map->m_Tiles == nullptr)
        return;

    m_Verts.clear();

    for (int y = 0; y < m_Map->HEIGHT; ++y)
    {
        for (int x = 0; x < m_Map->WIDTH; ++x)
        {
            auto tileType = m_Map->m_Tiles[y][x];
            
            sf::Vertex vertex;            
            
            // Top left
            vertex.position = { x * m_Map->TILE_SIZE, y * m_Map->TILE_SIZE };
            vertex.texCoords = TEX_COORDS[tileType][0];
            m_Verts.append(vertex);

            // Top right
            vertex.position = { (x + 1) * m_Map->TILE_SIZE, y * m_Map->TILE_SIZE };
            vertex.texCoords = TEX_COORDS[tileType][1];
            m_Verts.append(vertex);

            // Bottom left
            vertex.position = { x * m_Map->TILE_SIZE, (y + 1) * m_Map->TILE_SIZE };
            vertex.texCoords = TEX_COORDS[tileType][2];
            m_Verts.append(vertex);

            // Bottom right
            vertex.position = { (x + 1) * m_Map->TILE_SIZE, (y + 1) * m_Map->TILE_SIZE };
            vertex.texCoords = TEX_COORDS[tileType][3];
            m_Verts.append(vertex);
        }
    }
}
