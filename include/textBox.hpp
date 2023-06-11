#ifndef textBox_hpp
#define textBox_hpp

// creates the tools necessary to write in a textbox space
// used as part of start menu to load a map or tileset

#include <SFML/Graphics.hpp>
#include <iostream>

class textBox{
    public:
        textBox(float,float,float,float,sf::Text*,std::string,bool*);
        ~textBox();
        void Contains(sf::Vector2i*,bool);
        void makeQuad(sf::Vertex*);
        void makeText(std::string);
        void makeText(char*);
        std::string updateUserLabel(sf::Text*);

    private:
        bool hover=false;
        sf::Text* label;
        bool* active;
        std::string written;
        float top,bottom,left,right;
};

#endif
