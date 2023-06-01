#include "mapGenerator.hpp"

mapGenerator::mapGenerator() : window("tile map generator"),StartMenu(window.GetDefaultView()){
    std::cout<<"will use later"<<std::endl;
    if(!tiles.ReadInTiles(tileset, sf::Vector2u(32,32))){
        std::cout<<"cannot load tileset\n";
        return;
    }
    std::string menuFontLoc="/mnt/c/Windows/Fonts/arial.ttf";
    if(!font.loadFromFile(menuFontLoc)){
        std::cout<<"cannot load font"<<std::endl;
        return;
    }

    tiles.setLowerTextures(sf::Vector2u(32,32));
    tiles.setMap();    
    
    StartUpMenu();
    StartMenu.makeMenu();
    
    std::cout<<"Initialized...\n";
}

void mapGenerator::Update(){
    window.Update();
}

void mapGenerator::LateUpdate(){
}

void mapGenerator::Draw(){
    window.BeginDraw();
    
    //std::cout<<"drawing...\n";

    window.setViewPort_upper(sf::FloatRect(0.f,0.f,1.f,16/18.f));
    window.setView_upper();
    //std::cout<<"mapGen upper: "<<window.getUpperCenter().x<<","<<window.getUpperCenter().y<<std::endl;
    //std::cout<<"mapGen lower: "<<window.getLowerCenter().x<<","<<window.getLowerCenter().y<<std::endl;
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    window.Draw(shape);
    window.drawGrid(16,32);
    if(window.firstClick){tiles.setMap(window.retUpCoords());}
    tiles.isUpper(true);
    tiles.setUpperTextures(sf::Vector2i(32,32));    
    window.Draw(tiles);
    window.HighlightBin(32);

    window.setViewPort_lower(sf::FloatRect(0.f,512/576.f,1.f,1.f));
    window.setView_lower();
    tiles.isUpper(false);
    window.Draw(tiles);
    
    tiles.selectTile(window.retLowCoords());

    sf::RectangleShape rectangle9(sf::Vector2f(64,64));
    rectangle9.setPosition(512,0);
    rectangle9.setFillColor(sf::Color::Green);
    sf::RectangleShape rectangle10(sf::Vector2f(64,64));
    rectangle10.setPosition(576,0);
    rectangle10.setFillColor(sf::Color::Red);
    sf::RectangleShape rectangle11(sf::Vector2f(64,64));
    rectangle11.setPosition(640,0);
    rectangle11.setFillColor(sf::Color::Blue);
    sf::RectangleShape rectangle12(sf::Vector2f(64,64));
    rectangle12.setPosition(704,0);
    rectangle12.setFillColor(sf::Color::Black);
    sf::RectangleShape rectangle13(sf::Vector2f(64,64));
    rectangle13.setPosition(768,0);
    rectangle13.setFillColor(sf::Color::Yellow);
    sf::RectangleShape rectangle14(sf::Vector2f(64,64));
    rectangle14.setPosition(832,0);
    rectangle14.setFillColor(sf::Color::Magenta);
    sf::RectangleShape rectangle15(sf::Vector2f(64,64));
    rectangle15.setPosition(896,0);
    rectangle15.setFillColor(sf::Color::Cyan);
    sf::RectangleShape rectangle16(sf::Vector2f(64,64));
    rectangle16.setPosition(960,0);
    rectangle16.setFillColor(sf::Color::White);
   
    window.Draw(rectangle9);
    window.Draw(rectangle10);
    window.Draw(rectangle11);
    window.Draw(rectangle12);
    window.Draw(rectangle13);
    window.Draw(rectangle14);
    window.Draw(rectangle15);
    window.Draw(rectangle16);
    
    window.HighlightBin(64);

    window.EndDraw();
}

void mapGenerator::DrawMenu(){
    window.BeginDraw();
    window.setView(StartMenu.GetView());

    window.Draw(StartMenu);
    
    for(auto t : StartMenu.texts){
        std::cout<<"text string: "<<t.getString().toAnsiString()<<std::endl;
        t.setFont(font);
        window.Draw(t);
    }
    std::cout<<"after loop\n";

    window.EndDraw();
}

bool mapGenerator::IsRunning() const{
    return window.IsOpen();
}

bool mapGenerator::IsMenuRunning(std::string menuName="startup"){
    if(menuName=="startup") return StartMenu.IsMenuOpen();
    else return false;//return menu.IsMenuOpen();
}

void mapGenerator::StartUpMenu(){
    //generate startup menu attributes
    menuItemAttr submit;
    submit.readable=false;
    submit.itemText.setString("Submit");
    //submit.itemText.setFont(StartMenu.GetFont());
    submit.itemText.setCharacterSize(24);
    submit.itemText.setFillColor(sf::Color::Red);
    submit.relLoc={0,0};
    submit.itemSize={128,64};

    StartMenu.AddMenuItem(submit);
}

void mapGenerator::SaveMap(){
    std::string text="tileset: ";
    text+=tileset+"\n\n";

    tiles.retMap();
    
    text+="dim X: "+std::to_string(tiles.dimX)+"\n";
    text+="dim Y: "+std::to_string(tiles.dimY)+"\n\n";

    text+="tileMap:\n";
    text+=tiles.outputMap;

    std::ofstream file;
    file.open("../generatedMaps/mapSave.txt");
    file << text;
}
