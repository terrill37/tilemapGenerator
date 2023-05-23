#include <iostream>

#include <SFML/Graphics.hpp>


int main(){
    sf::ContextSettings settings;
    settings.depthBits          = 24;
    settings.stencilBits        = 8;
    settings.antialiasingLevel  = 4;
    settings.majorVersion       = 4;
    settings.minorVersion       = 6;

    sf::RenderWindow  window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Default, settings);//, sf::Style::Titlebar);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
    std::cout<<"OpenGL version: "<<settings.majorVersion<<"."<<settings.minorVersion<<std::endl;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code==sf::Keyboard::Escape){
                        window.close();
                        std::cout<<"closing window: Esc pressed\n";
                    }
                    break;
                default:
                    break;
            }
            
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}
