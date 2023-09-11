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

void menu::AddMenuItem(menuItemAttr* newItem){
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
    return !exit;
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

    for(auto item : menuItems){ 
        sf::Vertex* quad = &m_menuVertices[4*i];
        
        float xShift=0;
        if(item->relLoc.first<menuDims.x/2 && evenX){
            xShift = ((menuDims.x/2-item->relLoc.first)-1./2)*menuItemDims.x;
        }
        else if(item->relLoc.first<menuDims.x/2 && !evenX){
            xShift = (menuDims.x/2-item->relLoc.first)*menuItemDims.x;
        }
        else if(item->relLoc.first>menuDims.x/2 && !evenX){
            xShift = -1.*(abs(menuDims.x-item->relLoc.first))*menuItemDims.x;
        }
        else if(item->relLoc.first>=menuDims.x/2 && evenX){
            xShift = -(abs(menuDims.x-item->relLoc.first)+1./2)*menuItemDims.x;
        }
        
        float yShift=0;
        std::cout<<"initial yShift: "<<yShift<<std::endl;
        if(item->relLoc.second<menuDims.y/2 && evenY){
            //shift up
            yShift = ((menuDims.y/2-item->relLoc.second)-1./2)*menuItemDims.y;
        }
        else if(item->relLoc.second<menuDims.y/2 && !evenY){
            //shift up
            yShift = (menuDims.y/2-item->relLoc.second)*menuItemDims.y;
        }
        else if(item->relLoc.second>menuDims.y/2 && !evenY){
            //shift down with odd number of items
            yShift = -1.* (abs(menuDims.y/2-item->relLoc.second))*menuItemDims.y;
        }
        else if(item->relLoc.second>=menuDims.y/2 && evenY){
            //shift down with even number of items
            yShift = -(abs(menuDims.y/2-item->relLoc.second)+1./2)*menuItemDims.y;
        }
        
        float top       = (menuSize.y-menuItemDims.y)/2-yShift;
        float bottom    = (menuSize.y+menuItemDims.y)/2-yShift;
        float left      = (menuSize.x-menuItemDims.x)/2-xShift;
        float right     = (menuSize.x+menuItemDims.x)/2-xShift;
        
        std::cout<<"index: "<<item->relLoc.second<<" len: "<<menuDims.y<<" yshift: "<<yShift<<std::endl;
        if(!item->readable){
            button b(top,bottom,right,left,&item->itemText, &item->active);
            b.Contains(mousePos,click); //get mouse position
            b.makeQuad(quad);
            if(item->isSubmission && item->active){setExit();}
        }
        else{
            textBox tb(top,bottom,right,left,&item->itemText,item->userInput,&item->active);
            tb.makeText(userInput);
            item->userInput=tb.updateUserLabel(&item->userText);
            tb.Contains(mousePos,click);
            tb.makeQuad(quad);
            texts.push_back(&item->userText);
        }
        texts.push_back(&item->itemText);
        i++;
    }
    std::cout<<std::endl;
}

void menu::setExit(){
    exit=true;
}

bool menu::isExit(){
    return exit;
}

void menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(m_menuVertices, states);
}

void menu::Update(sf::Vector2i* moPos, bool mouseClick){
    mousePos=moPos;
    click=mouseClick;
    makeMenu();
}
