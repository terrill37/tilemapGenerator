#ifndef button_hpp
#define button_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

class button{
    public:
        button(float,float,float,float,sf::Text*);
        ~button();
        void Contains(sf::Vector2i*);
        void makeQuad(sf::Vertex*);

    private:
        bool hover=false;
        sf::Text* buttonText;
        float top,bottom,left,right;
};

#endif
