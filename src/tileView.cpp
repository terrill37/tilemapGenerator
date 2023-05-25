#include "tileView.hpp"

bool tileView::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles,
                  unsigned int width, unsigned int height){
    //might repurpose for upper view when placing tiles

    if(!m_tileset.loadFromFile(tileset)){
        std::cout<<"can't load tileset\n";
        return false;
    }

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width*height*4);
    


    //for(unsigned int i=0; i<width; i++){
    //    for(unsigned int j=0; j<height; j++){
    //        int tileNumber=tiles[i+j*width];

    //        int tu=tileNumber%(m_tileset.getSize().x/tileSize.x);
    //        int tv=tileNumber/(m_tileset.getSize().x/tileSize.x);

    //        sf::Vertex* quad=&m_vertices[(i+j*width)*4];

    //        quad[0].position=sf::Vector2f(i*tileSize.x,j*tileSize.y);
    //        quad[1].position=sf::Vector2f((i+1)*tileSize.x, j*tileSize.y);
    //        quad[2].position=sf::Vector2f((i+1)*tileSize.x, (j+1)*tileSize.y);
    //        quad[3].position=sf::Vector2f(i*tileSize.x, (j+1)*tileSize.y);

    //        
    //        quad[0].texCoords=sf::Vector2f(tu*tileSize.x,tv*tileSize.y); 
    //        quad[1].texCoords=sf::Vector2f((tu+1)*tileSize.x,tv*tileSize.y); 
    //        quad[2].texCoords=sf::Vector2f((tu+1)*tileSize.x,(tv+1)*tileSize.y); 
    //        quad[3].texCoords=sf::Vector2f(tu*tileSize.x,(tv+1)*tileSize.y); 
    //    }
    //}
    return true;
}

void tileView::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

bool tileView::ReadInTiles(const std::string& tileset, sf::Vector2u tileSize){ 
                           //const int width, const int height){
    //used to read out tile set
    //for lower view
    //height of texture file
    if(!m_tileset.loadFromFile(tileset)) return false;
    
    //m_vertices.setPrimitiveType(sf::Quads);
    //m_vertices.resize(64*1024*4);

    //tile location in tile set as (x,y) pair
    //tileSetSize is length of tile set in (x,y) directions by tile
    sf::Vector2u tileSetDim = sf::Vector2u(m_tileset.getSize().x/tileSize.x, m_tileset.getSize().y/tileSize.y);
    std::cout<<"tileSet dimensions: "<<tileSetDim.x<<","<<tileSetDim.y<<std::endl;
    unsigned int k=0;
    for(unsigned int i=0; i<tileSetDim.x; i++){
        //loop through x direction of tileset
        for(unsigned int j=0; j<tileSetDim.y; j++){
            //loop through y direction of tileset
            tilePositions[k]=sf::Vector2u(i,j);
            //std::cout<<"i,j: "<<i<<","<<j<<std::endl;
            //std::cout<<"k: "<<k<<std::endl;
            k++;
        }
    }
    return true;   
}

void tileView::setLowerTextures(sf::Vector2u tileSize){
    std::cout<<"set lower textures\n";
    unsigned int width=tilePositions.size();
    unsigned int height=1;
    
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width*height*4);

    for(unsigned int i=0; i<width; i++){
        for(unsigned int j=0; j<height; j++){
            int tileNumber=i;

            sf::Vector2u tilePos = tilePositions[i];

            sf::Vertex* quad = &m_vertices[(i+j*width)*4];

            quad[0].position=sf::Vector2f(2*i*tileSize.x, 2*j*tileSize.y);
            quad[1].position=sf::Vector2f(2*(i+1)*tileSize.x, 2*j*tileSize.y);
            quad[2].position=sf::Vector2f(2*(i+1)*tileSize.x, 2*(j+1)*tileSize.y);
            quad[3].position=sf::Vector2f(2*i*tileSize.x, 2*(j+1)*tileSize.y);

            quad[0].texCoords=sf::Vector2f(tilePos.x*tileSize.x, tilePos.y*tileSize.y);
            quad[1].texCoords=sf::Vector2f((tilePos.x+1)*tileSize.x, tilePos.y*tileSize.y);
            quad[2].texCoords=sf::Vector2f((tilePos.x+1)*tileSize.x, (tilePos.y+1)*tileSize.y);
            quad[3].texCoords=sf::Vector2f(tilePos.x*tileSize.x, (tilePos.y+1)*tileSize.y);
        }
    }
    std::cout<<"end of lower texture\n";
}

