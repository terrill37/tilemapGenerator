#include <button.hpp>

button::button(){}

button::~button(){}

void button::CheckClick(sf::Vector2f mousePos){
    if(mousePos.x>loc.x && mousePos.x<loc.x+size.x && mousePos.y>loc.y && mousePos.y<loc.y+size.y){
        SetState(!current);
    }
}

void button::SetState(bool which){
    current=which;
    if(current){
        return;
    }
}

void button::SetText(std::string words){
    buttonText=words;
}

bool button::GetVar(){return true;}

sf::String* button::GetText(){
    return &buttonText;
}

void button::draw(sf::RenderTarget&, sf::RenderStates) const{}
