#include "mapGenerator.hpp"

mapGenerator::mapGenerator() : window("tile map generator"){
    std::cout<<"will use later"<<std::endl;
}

void mapGenerator::Update(){
    window.Update();
}

void mapGenerator::LateUpdate(){
}

void mapGenerator::Draw(){
    window.BeginDraw();
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    window.Draw(shape);
    window.drawGrid(16,32);
    window.HighlightBin();

    window.EndDraw();
}

bool mapGenerator::IsRunning() const{
    return window.IsOpen();
}
