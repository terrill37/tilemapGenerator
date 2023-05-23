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

    }
}

void Window::setView(){
    window.setView(window.getDefaultView());
}

sf::Vector2f Window::getViewSize(){
    return window.getView().getSize();
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
