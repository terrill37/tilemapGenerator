#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "mapGenerator.hpp"
//#include "menu.hpp"

int main(){
    //std::cout<<"in main\n";
    mapGenerator mapGen;
    while(mapGen.IsRunning()){
        mapGen.Update();
        mapGen.LateUpdate();
        mapGen.Draw();
    }
    mapGen.SaveMap();
    return 0;
}

