#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "mapGenerator.hpp"

int main(){
    mapGenerator mapGen;
    while(mapGen.IsRunning()){
        mapGen.Update();
        mapGen.LateUpdate();
        if(!mapGen.IsMenuRunning("startup")){
            mapGen.Draw();
            mapGen.StartUpMenu();
        }
        else{mapGen.DrawMenu();}
    }
    mapGen.SaveMap();
    return 0;
}

