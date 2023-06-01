#ifndef mapGenerator_hpp
#define mapGenerator_hpp

#include "window.hpp"
#include "tileView.hpp"
#include "menu.hpp"

#include <iostream>
#include <fstream>
#include <map>

class mapGenerator{
    public:
        mapGenerator();

        void Update();
        void LateUpdate();
        void Draw();
        void SaveMap();
        void StartUpMenu();

        bool IsRunning() const;
        bool IsMenuRunning(std::string);
        
        void DrawMenu();

    private:
        Window window;

        tileView tiles;
        menu StartMenu;
        std::string tileset="../textures/tileset_alt.png";
        
        sf::Font font;

        //tileView tilesUpper;
        //sf::View view_upper;

};

#endif
