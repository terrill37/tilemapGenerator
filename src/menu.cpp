#include "menu.hpp"

menu::menu(sf::View windowView, sf::Vector2u windowSize){
    menuView=windowView;
    menuSize=windowSize;
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

void menu::SetMenuDims(sf::Vector2u dims, sf::Vector2u itemSize){
    menuDims=dims;
    menuItemDims=itemSize;
}

bool menu::IsMenuOpen(){
    return true;
}

void menu::makeMenu(){
    m_menuVertices.setPrimitiveType(sf::Quads);
    m_menuVertices.resize(4*menuItems.size());
    //menuItems;
    int i=0;
    
    std::cout<<"menuSize y: "<<menuSize.y<<std::endl;
    bool evenY=false;
    if(menuDims.y%2==0){evenY=true;}

    for(auto& item : menuItems){ 
        sf::Vertex* quad = &m_menuVertices[4*i];
        
        //int yMult=item.relLoc.second+1;
        int yShift=0;
        if(item.relLoc.second<menuDims.y/2){
            std::cout<<"upper half, odd\n";
            yShift = (menuDims.y-item.relLoc.second-1)*menuItemDims.y/2;
        }
        else if(item.relLoc.second>menuDims.y/2 && !evenY){
            std::cout<<"lower half, odd\n";
            yShift -= (menuDims.y-item.relLoc.second+1)*menuItemDims.y/2;
        }
        else if(item.relLoc.second>=menuDims.y/2 && evenY){
            std::cout<<"lower half, even\n";
            yShift -= (menuDims.y-item.relLoc.second)*menuItemDims.y/2;
        }
        
        std::cout<<"yShift: "<<yShift<<std::endl;
        //std::cout<<yMult<<std::endl;
        std::cout<<"top:    "<<(menuSize.y-menuItemDims.y)/2-yShift<<std::endl;
        std::cout<<"bottom: "<<(menuSize.y+menuItemDims.y)/2-yShift<<std::endl;

        quad[0].position=sf::Vector2f((menuSize.x-menuItemDims.x)/2, (menuSize.y-menuItemDims.y)/2-yShift);
        quad[1].position=sf::Vector2f((menuSize.x+menuItemDims.x)/2, (menuSize.y-menuItemDims.y)/2-yShift);
        quad[2].position=sf::Vector2f((menuSize.x+menuItemDims.x)/2, (menuSize.y+menuItemDims.y)/2-yShift);
        quad[3].position=sf::Vector2f((menuSize.x-menuItemDims.x)/2, (menuSize.y+menuItemDims.y)/2-yShift);

        quad[0].color=sf::Color::Green;
        quad[1].color=sf::Color::Blue;
        quad[2].color=sf::Color::Green;
        quad[3].color=sf::Color::Blue;

        item.itemText.setPosition((menuSize.x-menuItemDims.x)/2, (menuSize.y-menuItemDims.y)/2-yShift);
        texts.push_back(item.itemText);

        i++;
    }
}

void menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    //states.texture    = &m_menuVertices;
    target.draw(m_menuVertices, states);
}
