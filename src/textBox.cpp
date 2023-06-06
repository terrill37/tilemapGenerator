#include "textBox.hpp"

textBox::textBox(float ymax, float ymin, float xmax, float xmin, sf::Text* text, std::string userLabel){
    top=ymax;
    bottom=ymin;
    left=xmin;
    right=xmax;
    label=text;
    written=userLabel;
}

textBox::~textBox(){}

void textBox::Contains(sf::Vector2i* mousePos){
    if(left<mousePos->x && right>mousePos->x && top<mousePos->y && bottom>mousePos->y){hover=true;}
    else{hover=false;}
}

void textBox::makeQuad(sf::Vertex* quad){
    quad[0].position=sf::Vector2f(left,top);
    quad[1].position=sf::Vector2f(right,top);
    quad[2].position=sf::Vector2f(right, bottom);
    quad[3].position=sf::Vector2f(left, bottom);

    sf::Color buttonCol;
    if(hover){
        std::cout<<"hovering\n";
        buttonCol=sf::Color::Black;
    }
    else{
        buttonCol=sf::Color::Blue;
    }

    quad[0].color=buttonCol;
    quad[1].color=buttonCol;
    quad[2].color=buttonCol;
    quad[3].color=buttonCol;

    label->setPosition(left,top);
    label->setFillColor(sf::Color::Black);
}

void textBox::makeText(std::string input){
    written+=input;
    std::cout<<written<<std::endl;
}

void textBox::makeText(char* input){
    written.push_back(*input);
    *input='\0';
    //std::cout<<written<<std::endl;
}

std::string textBox::updateUserLabel(){
    return written;
}
