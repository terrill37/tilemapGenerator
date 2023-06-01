#include "menu.hpp"

menu::menu(sf::View windowSize){
    menuView=windowSize;
    //std::string menuFontLoc="/mnt/c/Windows/Fonts/arial.ttf";
    //if(!font.loadFromFile(menuFontLoc)){return;}
}

menu::~menu(){}

void menu::AddMenuItem(menuItemAttr newItem){
    menuItems.push_back(newItem);
}

void menu::SetView(sf::View view){
    menuView=view;
}

sf::View menu::GetView(){
    return menuView;
}

//sf::Font menu::GetFont(){
//    return font;
//}

bool menu::IsMenuOpen(){
    return true;
}

void menu::makeMenu(){
    m_menuVertices.setPrimitiveType(sf::Quads);
    m_menuVertices.resize(4*menuItems.size());
    //menuItems;
    int i=0;
    for(auto& item : menuItems){ 
        sf::Vertex* quad = &m_menuVertices[4*i];

        quad[0].position=sf::Vector2f(item.relLoc.first, item.relLoc.second);
        quad[1].position=sf::Vector2f(item.relLoc.first+item.itemSize.first, item.relLoc.second);
        quad[2].position=sf::Vector2f(item.relLoc.first+item.itemSize.first, item.relLoc.second+item.itemSize.second);
        quad[3].position=sf::Vector2f(item.relLoc.first, item.relLoc.second+item.itemSize.second);

        quad[0].color=sf::Color::Green;
        quad[1].color=sf::Color::Green;
        quad[2].color=sf::Color::Green;
        quad[3].color=sf::Color::Green;

        item.itemText.setPosition(item.relLoc.first, item.relLoc.second);
        texts.push_back(item.itemText);

        i++;
    }


}

void menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    //states.texture    = &m_menuVertices;
    target.draw(m_menuVertices, states);
}
