#include "button.hpp"

button::button(float ymax, float ymin, float xmax, float xmin, sf::Text* text, bool* isActive){
    top=ymax;
    bottom=ymin;
    left=xmin;
    right=xmax;
    active=isActive;
    buttonText=text;
}

button::~button(){}

void button::Contains(sf::Vector2i* mousePos, bool mouseClick){
    if(left<mousePos->x && right>mousePos->x && top<mousePos->y && bottom>mousePos->y){
        hover=true;
        if(mouseClick && !*active && prevMouseState!=mouseClick){*active=true;}
        else if(mouseClick && *active && prevMouseState!=mouseClick){*active=false;}//togglable
        prevMouseState=mouseClick;
    }
    else{
        hover=false;
        if(mouseClick && prevMouseState!=mouseClick){*active=false;}
    }
    //prevMouseState=(mouseClick && *active);
    std::cout<<*active<<" in button\n";
}

void button::makeQuad(sf::Vertex* quad){
    quad[0].position=sf::Vector2f(left,top);
    quad[1].position=sf::Vector2f(right,top);
    quad[2].position=sf::Vector2f(right, bottom);
    quad[3].position=sf::Vector2f(left, bottom);

    sf::Color buttonCol;
    if(hover || *active){
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
    
    //get the button texts bounding box to be able to center
    float bWidth  = abs(left - right);
    float bHeight = abs(top - bottom);
    auto tWidth  = buttonText->getLocalBounds().width;
    auto tHeight = buttonText->getLocalBounds().height;
    
    float dX = (1/2.)*(bWidth-tWidth);
    float dY = (1/2.)*(bHeight-tHeight);
    
    //std::cout<<"text: "<<tWidth<<","<<tHeight<<std::endl;
    //std::cout<<"button: "<<bWidth<<","<<bHeight<<std::endl;
    
    buttonText->setPosition(left+dX,top+dY);
    buttonText->setFillColor(sf::Color::Blue);
}

