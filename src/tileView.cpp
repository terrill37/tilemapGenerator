#include "tileView.hpp"

bool tileView::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles,
                  unsigned int width, unsigned int height){
    //might repurpose for upper view when placing tiles

    if(!m_tileset.loadFromFile(tileset)){
        std::cout<<"can't load tileset\n";
        return false;
    }

    //m_vertices.setPrimitiveType(sf::Quads);
    //m_vertices.resize(width*height*4);
    


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

void tileView::selectTile(std::pair<int,int> pos){
    //pos marks the currently highlighted texture in the lower view
    currentTile=pos.first; //will need to change when adding second row of textures
}

void tileView::setLowerTextures(sf::Vector2u tileSize){
    std::cout<<"set lower textures\n";
    unsigned int width=tilePositions.size();
    unsigned int height=1;
    
    m_verticesLower.setPrimitiveType(sf::Quads);
    m_verticesLower.resize(width*height*4);

    for(unsigned int i=0; i<width; i++){
        for(unsigned int j=0; j<height; j++){
            int tileNumber=i;

            sf::Vector2u tilePos = tilePositions[i];

            sf::Vertex* quad = &m_verticesLower[(i+j*width)*4];

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

void tileView::setUpperTextures(sf::Vector2i tileSize){
    //std::cout<<"set upper textures\n";
    
    unsigned int width=tilePositions.size();
    unsigned int height=1;

    m_verticesUpper.setPrimitiveType(sf::Quads);
    m_verticesUpper.resize(4*upperTileLocMap.size());
    
    int k=0;
    //loop through upperTileLocMap
    //key is where tile/quad is positioned
    //value is the tile number to extract from tile set (tilePositions map)
    for(auto const& [key, val] : upperTileLocMap){
        
        //std::cout<<"upperTileLocMap: "<<key.first<<","<<key.second<<","<<val<<std::endl;
        if(val==-1) continue;

        sf::Vector2u tilePos = tilePositions[val];

        sf::Vertex* quad = &m_verticesUpper[4*(k)];

        quad[0].position=sf::Vector2f((key.first)*tileSize.x, key.second*tileSize.y);
        quad[1].position=sf::Vector2f((key.first+1)*tileSize.x, key.second*tileSize.y);
        quad[2].position=sf::Vector2f((key.first+1)*tileSize.x, (key.second+1)*tileSize.y);
        quad[3].position=sf::Vector2f((key.first)*tileSize.x, (key.second+1)*tileSize.y);

        quad[0].texCoords=sf::Vector2f(tilePos.x*tileSize.x, tilePos.y*tileSize.y);
        quad[1].texCoords=sf::Vector2f((tilePos.x+1)*tileSize.x, tilePos.y*tileSize.y);
        quad[2].texCoords=sf::Vector2f((tilePos.x+1)*tileSize.x, (tilePos.y+1)*tileSize.y);
        quad[3].texCoords=sf::Vector2f(tilePos.x*tileSize.x, (tilePos.y+1)*tileSize.y);
        k++;
    }

    //std::cout<<"end of upper texture\n";
}

void tileView::isUpper(bool flag){
    if(flag){m_vertices = m_verticesUpper;}
    else{m_vertices = m_verticesLower;}
}

void tileView::setMap(std::pair<int,int> input){
    upperTileLocMap[input]=currentTile;
}

void tileView::setMap(){
    upperTileLocMap[{0,0}]=-1;
}

void tileView::retMap(){
    //use this function to store info about map when closing window
    std::vector<int> xVals,yVals;
    for(auto const& [key,val] : upperTileLocMap){
        if(val<0) continue;
        xVals.push_back(key.first);
        yVals.push_back(key.second);
    }
    int minX=*min_element(xVals.begin(),xVals.end()),minY=*min_element(yVals.begin(),yVals.end());
    int maxX=*max_element(xVals.begin(),xVals.end()),maxY=*max_element(xVals.begin(),xVals.end());
    dimX=abs(maxX - minX)+1;
    dimY=abs(maxY - minY)+1;

    std::cout<<"map of size: "<<dimX<<"x"<<dimY<<std::endl;
    std::cout<<"max x element: "<<*max_element(xVals.begin(),xVals.end())<<std::endl;
    std::cout<<"min x element: "<<*min_element(xVals.begin(),xVals.end())<<std::endl;
    
    outputMap="";
    for(int i=minX; i<=maxX; i++){
        for(int j=minY; j<=maxY; j++){
            std::cout<<i<<","<<j<<std::endl;
            if(upperTileLocMap.count({i,j})==1){
                std::cout<<"found key\n";
                outputMap+=std::to_string(upperTileLocMap.at({i,j}))+",";
            }
            else{
                std::cout<<"no key\n";
                outputMap+="-1,";
            }
        }
        outputMap+="\n";
    }
}
