#include "window.hpp"

#include <iostream>

void Window::Update(){
    sf::Event event;
    while(window.pollEvent(event)){
        mousePos=sf::Mouse::getPosition(window);
        isMouseClicked=sf::Mouse::isButtonPressed(sf::Mouse::Left);
        //userInput;
        //std::cout<<"mousePos: "<<mousePos.x<<","<<mousePos.y<<std::endl;
        if(event.type==sf::Event::Closed){
            window.close();
        }
        
        if(event.type==sf::Event::KeyPressed){
            if(event.key.code==sf::Keyboard::Escape){
                window.close();
            }

            std::cout<<"view event: "<<view_upper.getCenter().x<<","<<view_upper.getCenter().y<<std::endl;
            if(event.key.code==sf::Keyboard::Left)
                view_upper=Move('L',view_upper);
            if(event.key.code==sf::Keyboard::Right)
                view_upper=Move('R',view_upper);
            if(event.key.code==sf::Keyboard::Up)
                view_upper=Move('U',view_upper);
            if(event.key.code==sf::Keyboard::Down)
                view_upper=Move('D',view_upper);
        }    
        
        if(event.type == sf::Event::TextEntered){
            userInput=static_cast<char>(event.text.unicode);
        }
        else{userInput = '\0';}

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2f upPos  = window.mapPixelToCoords(mousePos,view_upper);
            sf::Vector2f lowPos = window.mapPixelToCoords(mousePos,view_lower); 
            if(mousePos.y<512){
                upX=(int)upPos.x/32;
                upY=(int)upPos.y/32;
                if(upPos.x<=0) upX-=1;
                if(upPos.y<=0) upY-=1;
                if(!firstClick){firstClick=true;}
                tileMapping();
            }
            else if(mousePos.y>512){
                lowX=(int)lowPos.x/128; //FIXME for different tile sizes
                lowY=(int)lowPos.y/128;
                std::cout<<lowX<<","<<lowY<<std::endl;
            }
        }   
    }
}

sf::View Window::GetDefaultView(){
    return window.getDefaultView();
}

void Window::resetMousePos(){
    upX=0;
    upY=0;
    firstClick=false;
}

void Window::setView_upper(){
    //std::cout<<"set view default"<<std::endl;
    window.setView(view_upper);
}

void Window::setView_lower(){
    window.setView(view_lower);
}

void Window::setView(sf::View v){
    //std::cout<<v.getCenter().x<<","<<v.getCenter().y<<std::endl;
    //std::cout<<"set view custom\n";
    window.setView(v);
}

sf::Vector2u Window::GetSize(){
    return window.getSize();
}

sf::Vector2f Window::getUpperCenter(){
    return view_upper.getCenter();
}

sf::Vector2f Window::getLowerCenter(){
    return view_lower.getCenter();
}

void Window::setViewPort_lower(sf::FloatRect rect){
    view_lower.setViewport(rect);
}

void Window::setViewPort_upper(sf::FloatRect rect){
    view_upper.setViewport(rect);
}

sf::Vector2f Window::getViewSize(){
    return window.getView().getSize();
}

void Window::drawGrid(int rows, int cols){
    //std::cout<<"in draw grid\n";
    //sf::Vector2f center=view_upper.getCenter();
    //std::cout<<"view: "<<center.x<<","<<center.y<<std::endl;
    sf::View origin=view_upper;//.move(-512,-256);
    origin.move(-512,-256);
    //std::cout<<"origin: "<<origin.getCenter().x<<","<<origin.getCenter().y<<std::endl;
    int numLines = rows+cols-2;
    sf::VertexArray grid(sf::Lines, 2*(numLines));
    
    auto size = view_upper.getSize(); //getViewSize();
    float rowH=(size.y)/rows;
    float colW=size.x/cols;
    
    //std::cout<<size.x<<','<<size.y<<std::endl;

    for(int i=0; i<rows-1; i++){
        int r=i+1;
        float rowY=rowH*r;
        grid[i*2].position={origin.getCenter().x, rowY+origin.getCenter().y};
        grid[i*2].color=sf::Color::Black;
        grid[i*2+1].position={size.x+origin.getCenter().x, rowY+origin.getCenter().y};
        grid[i*2+1].color=sf::Color::Black;
    }

    for(int i=rows-1; i<numLines; i++){
        int c=i-rows+2;
        float colX=colW*c;
        grid[i*2].position={colX+origin.getCenter().x,origin.getCenter().y};
        grid[i*2].color=sf::Color::Black;
        grid[i*2+1].position={colX+origin.getCenter().x, (size.y)+origin.getCenter().y};
        grid[i*2+1].color=sf::Color::Black;
        //std::cout<<"{"<<colX<<","<<size.y<<"}\n";
    }
    Draw(grid);
}

sf::View Window::Move(char dir, sf::View view){
    //std::cout<<"moving "<<dir<<std::endl;
    //sf::View view=window.getDefaultView();
    //std::cout<<"move: "<<view.getCenter().x<<","<<view.getCenter().y<<std::endl;
    //view=window.getView();
    
    if(dir=='L') view.move(32,0);
    if(dir=='R') view.move(-32,0);
    if(dir=='U') view.move(0,32);
    if(dir=='D') view.move(0,-32);
    
    //std::cout<<"move: "<<view.getCenter().x<<","<<view.getCenter().y<<std::endl;
    std::cout<<"window size: "<<window.getSize().x<<","<<window.getSize().y<<std::endl;

    return view;
}

sf::View Window::getDefaultView(){
    return window.getDefaultView(); 
}

void Window::tileMapping(){
    upCoords={upX,upY}; //may make adjustments in different location
    lowCoords={lowX, lowY};
}

std::pair<int,int> Window::retUpCoords(){
    return upCoords;
}

std::pair<int,int> Window::retLowCoords(){
    return lowCoords;
}

void Window::HighlightBin(int mult, bool isUpper){
    //bool isUpper to say if in upper view or not
    //int mult to decide scaling of the highlighted bin size

    int xpos,ypos,width,scale;
    sf::View origin;

    if(isUpper){
        origin=view_upper;
        origin.move(-512,-256);
        xpos=upX;
        ypos=upY;
        width=2;
        scale=1;
    }
    else{
        origin=view_lower;
        origin.move(-512,-32);
        xpos=lowX;
        ypos=lowY;
        width=4;
        scale=2;
    }
    
    sf::RectangleShape top(sf::Vector2f(scale*mult,width));
    top.setFillColor(sf::Color::Green);
    sf::RectangleShape bottom(sf::Vector2f(scale*mult,width));
    bottom.setFillColor(sf::Color::Green);
    sf::RectangleShape left(sf::Vector2f(width,scale*mult));
    left.setFillColor(sf::Color::Green);
    sf::RectangleShape right(sf::Vector2f(width,scale*mult));
    right.setFillColor(sf::Color::Green);
    
    top.setPosition(scale*mult*xpos,scale*mult*ypos-width/2);
    bottom.setPosition(scale*mult*xpos,scale*mult*ypos+scale*mult-width/2);
    left.setPosition(scale*mult*xpos-width/2,scale*mult*ypos);
    right.setPosition(scale*mult*xpos+scale*mult-width/2,scale*mult*ypos);

    Draw(top);
    Draw(bottom);
    Draw(left);
    Draw(right);
}

void Window::BeginDraw(){
    window.clear(sf::Color::White);
}

void Window::Draw(const sf::Drawable& drawable){
    window.draw(drawable);
}

void Window::EndDraw(){
    window.display();
}

bool Window::IsOpen() const{
    return window.isOpen();
}

sf::Vector2i* Window::GetMousePos(){
    auto *ptr = &mousePos;
    return ptr;
}

char* Window::GetUserInput(){
    auto *ptr = &userInput;
    return ptr;
}
