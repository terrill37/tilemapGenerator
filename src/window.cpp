#include "window.hpp"

#include <iostream>

void Window::Update(){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();
        }
        
        if(event.type==sf::Event::KeyPressed){
            if(event.key.code==sf::Keyboard::Escape)
                window.close();
            
            std::cout<<"view event: "<<view.getCenter().x<<","<<view.getCenter().y<<std::endl;
            if(event.key.code==sf::Keyboard::Left)
                view=Move('L',view);
            if(event.key.code==sf::Keyboard::Right)
                view=Move('R',view);
            if(event.key.code==sf::Keyboard::Up)
                view=Move('U',view);
            if(event.key.code==sf::Keyboard::Down)
                view=Move('D',view);
            setView(view);
        }    
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            auto mousePos=sf::Mouse::getPosition(window);
            lastX=mousePos.x/32;
            lastY=mousePos.y/32;
            std::cout<<lastX<<","<<lastY<<std::endl;
        }   
    }
}

void Window::setView(){
    std::cout<<"set view default"<<std::endl;
    window.setView(window.getDefaultView());
}

void Window::setView(sf::View v){
    //std::cout<<v.getCenter().x<<","<<v.getCenter().y<<std::endl;
    std::cout<<"set view custom\n";
    window.setView(v);
}

sf::Vector2f Window::getViewSize(){
    return window.getView().getSize();
}

void Window::drawGrid(int rows, int cols){
    //std::cout<<"in draw grid\n";
    sf::Vector2f center=view.getCenter();
    std::cout<<"view: "<<center.x<<","<<center.y<<std::endl;
    sf::View origin=view;//.move(-512,-256);
    origin.move(-512,-256);
    std::cout<<"origin: "<<origin.getCenter().x<<","<<origin.getCenter().y<<std::endl;
    int numLines = rows+cols-2;
    sf::VertexArray grid(sf::Lines, 2*(numLines));
    
    auto size = getViewSize();
    float rowH=size.y/rows;
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
        grid[i*2+1].position={colX+origin.getCenter().x, size.y+origin.getCenter().y};
        grid[i*2+1].color=sf::Color::Black;
        //std::cout<<"{"<<colX<<","<<size.y<<"}\n";
    }
    Draw(grid);
}

sf::View Window::Move(char dir, sf::View view){
    std::cout<<"moving "<<dir<<std::endl;
    //sf::View view=window.getDefaultView();
    
    view=window.getView();

    if(dir=='L') view.move(32,0);
    if(dir=='R') view.move(-32,0);
    if(dir=='U') view.move(0,32);
    if(dir=='D') view.move(0,-32);
    
    return view;
}

sf::View Window::getDefaultView(){
    return window.getDefaultView(); 
}

void Window::HighlightBin(){
    //Highlight square in grid base on input positions of map
    int xpos=lastX;
    int ypos=lastY;
    sf::VertexArray square(sf::LineStrip, 5);
    square[0].position=sf::Vector2f(32*xpos,32*ypos);
    square[1].position=sf::Vector2f(32*xpos+32,32*ypos);
    square[2].position=sf::Vector2f(32*xpos+32,32*ypos+32);
    square[3].position=sf::Vector2f(32*xpos,32*ypos+32);
    square[4].position=sf::Vector2f(32*xpos,32*ypos);
    square[0].color=sf::Color::Green;
    square[1].color=sf::Color::Green;
    square[2].color=sf::Color::Green;
    square[3].color=sf::Color::Green;
    square[4].color=sf::Color::Green;

    Draw(square);
}

void Window::BeginDraw(){
    window.clear(sf::Color::White);
    //setView(view);
    std::cout<<"begin draw: "<<view.getCenter().x<<","<<view.getCenter().y<<std::endl;
}

void Window::Draw(const sf::Drawable& drawable){
    //std::cout<<"drawable"<<std::endl;
    window.draw(drawable);
}

void Window::EndDraw(){
    window.display();
}

bool Window::IsOpen() const{
    return window.isOpen();
}
