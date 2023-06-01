#ifndef menu_hpp
#define menu_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

#include "button.hpp"

struct menuItemAttr{
    //menu item attributes
    bool readable; //read-in text otherwise a button
    sf::Text itemText; //associated text to menu option 
    std::pair<int,int> relLoc; //relative position of the menu items to one another; 
                               //menu centered in window by default
    std::pair<int,int> itemSize; //relative size of button
    
};

class menu : public sf::Drawable, public sf::Transformable{
    public:
        menu(sf::View); //constructor
        menu();
        ~menu(); //destructor
        
        void AddMenuItem(menuItemAttr);
        void makeMenu();
        void SetView(sf::View);
        
        sf::View GetView();
        sf::Font GetFont();

        bool IsMenuOpen();
        
        std::vector<sf::Text> texts;

    private:
        sf::View menuView;
        sf::Font font;

        std::vector<menuItemAttr> menuItems;
        std::vector<button> buttons;
        //std::vector<sf::Text> texts;
        sf::VertexArray m_menuVertices;
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const; //make the menu the drawable

};

#endif
