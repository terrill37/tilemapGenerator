#ifndef tileView_hpp
#define tileView_hpp

#include <iostream>
#include <unordered_map>
#include <map>

#include <SFML/Graphics.hpp>

struct Tile{
    unsigned int sprite;
    bool is_passable;
};

//struct Map{
//    //Tile tiles[size_x][size_y];
//};

class tileView : public sf::Drawable, public sf::Transformable{
    public:
        bool load(const std::string&, sf::Vector2u tileSize, const int* tiles,
                  unsigned int width, unsigned int height);
        bool ReadInTiles(const std::string&, sf::Vector2u);
        void setLowerTextures(sf::Vector2u);
        void setUpperTextures(sf::Vector2i);
        void isUpper(bool);

    private:
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

        sf::VertexArray m_verticesLower;
        sf::VertexArray m_verticesUpper;
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        
        bool isUp=false;

        std::unordered_map<int, sf::Vector2u> tilePositions; //tile position in tile set
        //location vector of tile # in upper view
        //stores location and tile number to a map that can be used by the setUpperTextures
        std::map<std::pair<int,int>, int> upperTileLocMap;
};

#endif
