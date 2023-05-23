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
        }    
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            auto mousePos=sf::Mouse::getPosition(window);
            lastX=mousePos.x/32;
            lastY=mousePos.y/32;
        }   
    }
}

void Window::setView(){
    window.setView(window.getDefaultView());
}

sf::Vector2f Window::getViewSize(){
    return window.getView().getSize();
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
