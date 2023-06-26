#ifndef button_hpp
#define button_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

#include "menu.hpp"

class button{
    public:
        button(float,float,float,float,sf::Text*,bool*);
        //button(float,float,float,float, menuItemAttr*);
        ~button();
        void Contains(sf::Vector2i*, bool);
        void makeQuad(sf::Vertex*);

    private:
        bool hover=false;
        bool* active;
        sf::Text* buttonText;
        float top,bottom,left,right;
};

#endif
