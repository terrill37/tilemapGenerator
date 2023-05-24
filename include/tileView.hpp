#ifndef tileView_hpp
#define tileView_hpp

#include <iostream>
#include <SFML/Graphics.hpp>

struct Tile{
    unsigned int sprite;
    bool is_passable;
};

struct Map{
    //Tile tiles[size_x][size_y];
};

class tileView : public sf::Drawable, public sf::Transformable{
    public:
        bool load(const std::string&, sf::Vector2u tileSize, const int* tiles,
                  unsigned int width, unsigned int height);

    private:
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
};

#endif
