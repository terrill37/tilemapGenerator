#ifndef button_hpp
#define button_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

class button{
    public:
        button();
        ~button();
        void CheckClick(sf::Vector2f);
        void SetState(bool);
        void SetText(std::string);
        bool GetVar();
        sf::String* GetText();
    
    private:
        bool current;
        sf::String buttonText;
        sf::Vector2f size;
        sf::Vector2f loc;
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif
