#include "mapGenerator.hpp"

mapGenerator::mapGenerator() : window("tile map generator"),StartMenu(window.GetDefaultView(), window.GetSize(), window.GetMousePos(), window.GetUserInput()){
    //if(!tiles.ReadInTiles(tileset, sf::Vector2u(32,32))){
    //    std::cout<<"cannot load tileset\n";
    //    return;
    //}
    std::string menuFontLoc="/mnt/c/Windows/Fonts/cour.ttf";
    if(!font.loadFromFile(menuFontLoc)){
        std::cout<<"cannot load font"<<std::endl;
        return;
    }
    
    StartUpMenu();
    
    std::cout<<"Initialized...\n";
}

void mapGenerator::Update(){
    window.Update();
}

void mapGenerator::menuUpdate(){
    window.Update();
    StartMenu.Update(window.GetMousePos(),window.isMouseClicked);
}

void mapGenerator::LateUpdate(){
}

void mapGenerator::LoadTiles(std::string tilesetName="../textures/tileset_alt.png"){
    if(tileset.size()==0){
        tileset="../textures/"+loadTiles.userText.getString()+".png";
    }
    //std::cout<<"userText: "<<loadMap.userInput<<std::endl;
    //std::cout<<tileset<<std::endl;
    if(!tiles.ReadInTiles(tileset, sf::Vector2u(32,32))){
        std::cout<<"cannot load tileset\n";
        return;
    }
    tiles.setLowerTextures(sf::Vector2u(32,32));
    tiles.setMap();
}

void mapGenerator::Draw(){
    window.BeginDraw();
    
    //std::cout<<"drawing...\n";

    window.setViewPort_upper(sf::FloatRect(0.f,0.f,1.f,16/18.f));
    window.setView_upper();
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Red);
    //window.Draw(shape);
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
        //std::cout<<"text string: "<<t->getString().toAnsiString()<<std::endl;
        t->setFont(font);
        window.Draw(*t);
    }
    //std::cout<<"after loop\n";

    window.EndDraw();
}

bool mapGenerator::IsRunning() const{
    return window.IsOpen();
}

bool mapGenerator::IsMenuRunning(std::string menuName="startup"){
    if(menuName=="startup"){ 
        if(!StartMenu.IsMenuOpen()){window.resetMousePos();}
        return StartMenu.IsMenuOpen();
    }
    else{ 
        window.resetMousePos();
        return false;
    }
}

void mapGenerator::StartUpMenu(){
    StartMenu.SetMenuDims(sf::Vector2u(1,3), sf::Vector2u(128,64));
    //generate startup menu attributes
    submit.readable=false;
    submit.itemText.setString("Submit");
    submit.itemText.setCharacterSize(16);
    submit.relLoc={0,2};
    submit.isSubmission=true;
    submit.itemSize={128,64};
    
    //menuItemAttr loadMap;
    loadMap.readable=true;
    loadMap.itemText.setString("Load Map Save: ");
    loadMap.itemText.setCharacterSize(8);
    loadMap.active=true;
    loadMap.relLoc={0,0};
    loadMap.itemSize={128,64};
    
    //menuItemAttr loadTiles;
    loadTiles.readable=true;
    loadTiles.itemText.setString("Load Tile Set: ");
    loadTiles.itemText.setCharacterSize(8);
    loadTiles.relLoc={0,1};
    loadTiles.itemSize={128,64};

    StartMenu.AddMenuItem(&submit);
    StartMenu.AddMenuItem(&loadMap);
    StartMenu.AddMenuItem(&loadTiles);
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
    std::cout<<"mapsave: "<<mapsave<<std::endl;
    file.open(mapsave);
    file << text;
}

void mapGenerator::LoadMap(){
    if(!loadMap.userText.getString().toAnsiString().size()==0){
        mapsave="../generatedMaps/"+loadMap.userText.getString()+".txt";
    }
    else{
        time_t now = time(0);
        tm* ltm = localtime(&now);
        auto year=1900+ltm->tm_year;
        auto month=1+ltm->tm_mon;
        auto day=ltm->tm_mday;
        
        std::string date=std::to_string(year)+"_"+std::to_string(month)+"_"+std::to_string(day);

        mapsave="../generatedMaps/genMap_"+date+".txt";
    }
    if(!std::filesystem::exists(mapsave)){
        std::cout<<"Map Save File Does Not Exist\nSkipping map loading procedure\n";
    }
    else{
        std::cout<<"Map Save File Exists\n Loading map...\n";
        std::ifstream savedFile(mapsave);
        std::string line;
        bool inMap=false;
        while(std::getline(savedFile,line)){
            //std::cout<<line<<std::endl;
            if(line.find("tileset:") != std::string::npos){
                tileset=std::regex_replace(line, std::regex("tileset: "), "");
                continue;
            }
            else if(line.find("dim X:") != std::string::npos){
                tiles.dimX=std::stoi(std::regex_replace(line, std::regex("dim X: "), ""));
                continue;
                //std::cout<<tiles.dimX<<std::endl;
            }
            else if(line.find("dim Y:") != std::string::npos){
                tiles.dimY=std::stoi(std::regex_replace(line, std::regex("dim Y: "), ""));
                continue;
            }
            else if(line.find("tileMap:") != std::string::npos){
                continue;
            }
            std::cout<<line<<std::endl;
            for(int i=0; i<line.size(); i++){
                //std::cout<<line[i]<<" ";
                if(line[i]==','){
                    //std::cout<<"comma\n";
                    continue;
                }
                else if(line[i]=='-'){
                    //std::cout<<"-1: "<<line[i+1]<<","<<(int(line[i+1])-'0')<<std::endl;
                    mapTileNum.push_back(-1*(int(line[i+1])-'0'));
                    i++;
                }
                else if(line[i+1]!=','){
                    mapTileNum.push_back((int(line[i]-'0'))*10 + int(line[i+1]-'0'));
                    i++;
                }
                else{
                    //std::cout<<line[i]<<"\n";
                    mapTileNum.push_back(int(line[i]-'0'));
                }
            }
            std::cout<<std::endl;
        }
        tiles.setMap(mapTileNum);
    }
}

//std::string GetTileSetName(){
//    return "tileset_alt"; //loadTiles.userInput;
//}

