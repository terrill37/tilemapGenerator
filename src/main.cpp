#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "mapGenerator.hpp"

int main(){
    mapGenerator mapGen;
    while(mapGen.IsMenuRunning("startup") && mapGen.IsRunning()){
        mapGen.menuUpdate();
        //mapGen.LateUpdate();
        mapGen.DrawMenu();
    }
    
    mapGen.menuUpdate();
    std::string tileset="../textures/";
    mapGen.LoadMap();
    mapGen.LoadTiles(tileset);

    while(mapGen.IsRunning()){
        mapGen.Update();
        mapGen.LateUpdate();
        mapGen.Draw();
    }
    mapGen.SaveMap();
    return 0;
}

