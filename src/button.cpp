#include "button.hpp"

button::button(float ymax, float ymin, float xmax, float xmin, sf::Text* text){
    top=ymax;
    bottom=ymin;
    left=xmin;
    right=xmax;
    buttonText=text;
}

button::~button(){}

void button::Contains(sf::Vector2i* mousePos){
    if(left<mousePos->x && right>mousePos->x && top<mousePos->y && bottom>mousePos->y){hover=true;}
    else{hover=false;}
}

void button::makeQuad(sf::Vertex* quad){
    quad[0].position=sf::Vector2f(left,top);
    quad[1].position=sf::Vector2f(right,top);
    quad[2].position=sf::Vector2f(right, bottom);
    quad[3].position=sf::Vector2f(left, bottom);

    sf::Color buttonCol;
    if(hover){
        //std::cout<<"hovering\n";
        buttonCol=sf::Color::Red;
    }
    else{
        buttonCol=sf::Color::Green;
    }

    quad[0].color=buttonCol;
    quad[1].color=buttonCol;
    quad[2].color=buttonCol;
    quad[3].color=buttonCol;

    buttonText->setPosition(left,top);
    buttonText->setFillColor(sf::Color::Blue);
}

