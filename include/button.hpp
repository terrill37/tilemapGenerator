#ifndef button_hpp
#define button_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

class button{
    public:
        button(float,float,float,float,sf::Text*,bool*);
        ~button();
        void Contains(sf::Vector2i*, bool);
        void makeQuad(sf::Vertex*);

    private:
        bool hover=false;
        bool* active;
        bool prevMouseState=false; //previous mouse click state
        sf::Text* buttonText;
        float top,bottom,left,right;
};

#endif
