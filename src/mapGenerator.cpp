#include "mapGenerator.hpp"

mapGenerator::mapGenerator() : window("tile map generator"){
    std::cout<<"will use later"<<std::endl;
}

void mapGenerator::Update(){
    window.Update();
}

void mapGenerator::drawGrid(int rows, int cols){
    //std::cout<<"in draw grid\n";
    int numLines = rows+cols-2;
    sf::VertexArray grid(sf::Lines, 2*(numLines));
    window.setView();
    auto size = window.getViewSize();
    float rowH=size.y/rows;
    float colW=size.x/cols;
    
    //std::cout<<size.x<<','<<size.y<<std::endl;

    for(int i=0; i<rows-1; i++){
        int r=i+1;
        float rowY=rowH*r;
        grid[i*2].position={0, rowY};
        grid[i*2].color=sf::Color::Black;
        grid[i*2+1].position={size.x, rowY};
        grid[i*2+1].color=sf::Color::Black;
    }

    for(int i=rows-1; i<numLines; i++){
        int c=i-rows+2;
        float colX=colW*c;
        grid[i*2].position={colX,0};
        grid[i*2].color=sf::Color::Black;
        grid[i*2+1].position={colX, size.y};
        grid[i*2+1].color=sf::Color::Black;
        //std::cout<<"{"<<colX<<","<<size.y<<"}\n";
    }
    window.Draw(grid);
}

void mapGenerator::LateUpdate(){
    //drawGrid(10,10);
}

void mapGenerator::Draw(){
    window.BeginDraw();
    drawGrid(16,32);
    //sf::View view(player.
    //window.setView(view);
    window.EndDraw();
}

bool mapGenerator::IsRunning() const{
    return window.IsOpen();
}
