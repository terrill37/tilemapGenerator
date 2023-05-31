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

        bool IsRunning() const;
        bool IsMenuRunning(menu) const;

    private:
        Window window;

        tileView tiles;
        menu StartMenu;
        std::string tileset="../textures/tileset_alt.png";

        //tileView tilesUpper;
        //sf::View view_upper;

};

#endif
