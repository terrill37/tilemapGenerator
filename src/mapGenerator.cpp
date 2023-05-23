#include "mapGenerator.hpp"

mapGenerator::mapGenerator() : window("tile map generator"){
    std::cout<<"will use later"<<std::endl;
}

void mapGenerator::Update(){
    window.Update();
}

void mapGenerator::LateUpdate(){
    //window.drawGrid(16,32);
}

void mapGenerator::Draw(){
    window.BeginDraw();
    //window.setView();
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    window.Draw(shape);
    window.drawGrid(16,32);
    window.HighlightBin();
    //window.setView(window.view);
    window.EndDraw();
}

bool mapGenerator::IsRunning() const{
    return window.IsOpen();
}
