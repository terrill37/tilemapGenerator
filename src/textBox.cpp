#include "textBox.hpp"

textBox::textBox(float ymax, float ymin, float xmax, float xmin, sf::Text* text, std::string userLabel, bool* isActive){
    top=ymax;
    bottom=ymin;
    left=xmin;
    right=xmax;
    label=text;
    active=isActive; //intialization if text box is initially active
    //userInput=userLabel;
    written=userLabel;
}

textBox::~textBox(){}

void textBox::Contains(sf::Vector2i* mousePos, bool mouseClick){
    // Will use function to make textbox active;
    if(left<mousePos->x && right>mousePos->x && top<mousePos->y && bottom>mousePos->y){
        hover=true;
        if(mouseClick){*active=true;} //doesn't need a deactivate condition unless 
                                     //clicked in different spot while not hovering
    }
    else{
        hover=false;
        if(mouseClick){*active=false;}
    }
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
    if(*input!='\0' && *active){
        if(*input=='\b' && written.size()>0){
            written.pop_back();
        }
        else if(*input!='\b'){written.push_back(*input);}
        *input='\0';
    //userInput->setString(written);
    //std::cout<<*active<<": "<<written<<std::endl;
    }
}

std::string textBox::updateUserLabel(sf::Text* uText){
    uText->setString(written);
    uText->setPosition(left,top);
    uText->setFillColor(sf::Color::Black);
    return written;
}

