#ifndef mapGenerator_hpp
#define mapGenerator_hpp

#include "window.hpp"
#include "tileView.hpp"

#include <iostream>

class mapGenerator{
    public:
        mapGenerator();

        void Update();
        void LateUpdate();
        void Draw();

        bool IsRunning() const;

    private:
        Window window;
        
        tileView tiles;
        //tileView tilesUpper;
        //sf::View view_upper;

};

#endif
