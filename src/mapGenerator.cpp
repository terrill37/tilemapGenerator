#include "mapGenerator.hpp"

mapGenerator::mapGenerator() : window("tile map generator"),StartMenu(window.GetDefaultView(), window.GetSize(), window.GetMousePos(), window.GetUserInput()){
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
    if(!tiles.ReadInTiles(tileset, sf::Vector2u(64,64))){ //FIXME 64 for larger tiles
        std::cout<<"cannot load tileset\n";
        return;
    }
    tiles.setLowerTextures(sf::Vector2u(64,64)); //FIXME
    tiles.setMap();
}

void mapGenerator::Draw(){
    window.BeginDraw();

    window.setViewPort_upper(sf::FloatRect(0.f,0.f,1.f,16/18.f));
    window.setView_upper();
    window.drawGrid(8,16);
    if(window.firstClick){tiles.setMap(window.retUpCoords());}
    tiles.isUpper(true);
    tiles.setUpperTextures(sf::Vector2i(64,64)); //FIXME upper texture size
    window.Draw(tiles);
    window.HighlightBin(64,true); //FIXME for changing tile size

    window.setViewPort_lower(sf::FloatRect(0.f,512/576.f,1.f,1.f));
    window.setView_lower();
    tiles.isUpper(false);
    window.Draw(tiles);
    
    tiles.selectTile(window.retLowCoords());
    
    window.HighlightBin(64,false);

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
    StartMenu.SetMenuDims(sf::Vector2u(1,4), sf::Vector2u(128,64));
    //generate startup menu attributes
    submit.readable=false;
    submit.itemText.setString("Submit");
    submit.itemText.setCharacterSize(16);
    submit.relLoc={0,3};
    submit.isSubmission=true;
    submit.itemSize={128,64};
    
    test.readable=false;
    test.itemText.setString("test");
    test.itemText.setCharacterSize(16);
    test.relLoc={0,4};
    test.isSubmission=true;
    test.itemSize={128,64};
    
    test2.readable=false;
    test2.itemText.setString("test");
    test2.itemText.setCharacterSize(16);
    test2.relLoc={0,5};
    test2.isSubmission=true;
    test2.itemSize={128,64};

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

    loadTileSize.readable=true;
    loadTileSize.itemText.setString("Load Tiles Size: "); // in Tile Set: ");
    loadTileSize.itemText.setCharacterSize(8);
    loadTileSize.relLoc={0,2};
    loadTileSize.itemSize={128,64};

    StartMenu.AddMenuItem(&loadMap);
    StartMenu.AddMenuItem(&loadTileSize);
    StartMenu.AddMenuItem(&loadTiles);
    StartMenu.AddMenuItem(&submit);
    //StartMenu.AddMenuItem(&test);
    //StartMenu.AddMenuItem(&test2);
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

