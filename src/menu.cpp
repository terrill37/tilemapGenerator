#include "menu.hpp"

menu::menu(sf::View windowView, sf::Vector2u windowSize, sf::Vector2i* moPos, char* userIn){
    menuView=windowView;
    menuSize=windowSize;
    mousePos=moPos;
    userInput=userIn;
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
    
    //std::cout<<"menuSize y: "<<menuSize.y<<std::endl;
    bool evenX=false,evenY=false;
    if(menuDims.x%2==0){evenX=true;}
    if(menuDims.y%2==0){evenY=true;}

    for(auto& item : menuItems){ 
        sf::Vertex* quad = &m_menuVertices[4*i];
        
        int xShift=0;
        if(item.relLoc.first<menuDims.x/2){
            xShift = (menuDims.x-item.relLoc.first-1)*menuItemDims.x/2;
        }
        else if(item.relLoc.first>menuDims.x/2 && !evenX){
            xShift -= (menuDims.x-item.relLoc.first+1)*menuItemDims.x/2;
        }
        else if(item.relLoc.first>=menuDims.x/2 && evenX){
            xShift -= (menuDims.x-item.relLoc.first)*menuItemDims.x/2;
        }
        
        int yShift=0;
        if(item.relLoc.second<menuDims.y/2){
            yShift = (menuDims.y-item.relLoc.second-1)*menuItemDims.y/2;
        }
        else if(item.relLoc.second>menuDims.y/2 && !evenY){
            yShift -= (menuDims.y-item.relLoc.second+1)*menuItemDims.y/2;
        }
        else if(item.relLoc.second>=menuDims.y/2 && evenY){
            yShift -= (menuDims.y-item.relLoc.second)*menuItemDims.y/2;
        }
        
        //std::cout<<"yShift: "<<yShift<<std::endl;
        //std::cout<<"xShift: "<<xShift<<std::endl;
        float top       = (menuSize.y-menuItemDims.y)/2-yShift;
        float bottom    = (menuSize.y+menuItemDims.y)/2-yShift;
        float left      = (menuSize.x-menuItemDims.x)/2-xShift;
        float right     = (menuSize.x+menuItemDims.x)/2-xShift;
        
        //std::cout<<"before button\n";
        if(!item.readable){
            button b(top,bottom,right,left,&item.itemText);
            b.Contains(mousePos); //get mouse position
            b.makeQuad(quad);
        }
        else{
            textBox tb(top,bottom,right,left,&item.itemText,item.userInput);
            tb.makeText(userInput);
            item.userInput=tb.updateUserLabel();
            tb.makeQuad(quad);
            
            item.itemText.setPosition(left, top);
        }
        texts.push_back(&item.itemText);

        i++;
    }
}

void menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    //states.texture    = &m_menuVertices;
    target.draw(m_menuVertices, states);
}

void menu::Update(sf::Vector2i* moPos){
    mousePos=moPos;
    makeMenu();
}
