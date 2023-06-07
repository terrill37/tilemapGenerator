#include "textBox.hpp"

textBox::textBox(float ymax, float ymin, float xmax, float xmin, sf::Text* text, std::string userLabel){
    top=ymax;
    bottom=ymin;
    left=xmin;
    right=xmax;
    label=text;
    //userInput=userLabel;
    written=userLabel;

    //std::cout<<"written: "<<written<<std::endl;
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
        //std::cout<<"hovering\n";
        buttonCol=sf::Color::Black;
    }
    else{
        buttonCol=sf::Color::Blue;
    }

    quad[0].color=buttonCol;
    quad[1].color=buttonCol;
    quad[2].color=buttonCol;
    quad[3].color=buttonCol;

    float bWidth  = abs(left - right);
    float bHeight = abs(top - bottom);
    auto tWidth  = label->getLocalBounds().width;
    auto tHeight = label->getLocalBounds().height;
    
    float dX = (tWidth);
    float dY = (1/2.)*(bHeight-tHeight);

    label->setPosition(left-dX,top+dY);
    label->setFillColor(sf::Color::Black);

    //userInput->setPosition(left+10, top+dY);
}

void textBox::makeText(std::string input){
    //std::cout<<written<<std::endl;
    written+=input;
}

void textBox::makeText(char* input){
    if(!*input=='\0'){
        if(*input=='\b' && written.size()>0){
            written.pop_back();
        }
        else{written.push_back(*input);}
        *input='\0';
    //userInput->setString(written);
    std::cout<<written<<std::endl;
    }
}

std::string textBox::updateUserLabel(sf::Text* uText){
    uText->setString(written);
    uText->setPosition(left,top);
    uText->setFillColor(sf::Color::Black);
    return written;
}

