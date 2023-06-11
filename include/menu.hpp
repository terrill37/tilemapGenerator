#ifndef menu_hpp
#define menu_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

#include "button.hpp"
#include "textBox.hpp"

struct menuItemAttr{
    //menu item attributes
    bool readable; //read-in text otherwise a button
    sf::Text itemText; //associated text to menu option 
    std::pair<int,int> relLoc; //relative position of the menu items to one another; 
                               //menu centered in window by default
    std::pair<int,int> itemSize; //relative size of button
    std::string userInput=""; //will be updated in non-button class
    sf::Text userText;
    bool isSubmission=false;
    bool active=false; //pointer to turn on and off
};

class menu : public sf::Drawable, public sf::Transformable{
    public:
        menu(sf::View, sf::Vector2u, sf::Vector2i*, char*); //constructor
        menu();
        ~menu(); //destructor
        
        void AddMenuItem(menuItemAttr);
        void makeMenu();
        void setExit();
        bool isExit();
        void SetMenuDims(sf::Vector2u, sf::Vector2u);
        void SetView(sf::View);
        void Update(sf::Vector2i*,bool);

        sf::View GetView();
        sf::Font GetFont();

        bool IsMenuOpen();
        
        std::vector<sf::Text*> texts;

    private:
        sf::View menuView;
        sf::Vector2u menuSize;
        sf::Vector2u menuDims; //dimensions of the menu in terms of menu items in x and y
        sf::Vector2u menuItemDims; //dimensions of the menu items in terms of x and y pixels
        sf::Vector2i* mousePos;
        bool click;
        bool exit=false;
        char* userInput;
        sf::Font font;

        std::vector<menuItemAttr> menuItems;
        sf::VertexArray m_menuVertices;
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const; //make the menu the drawable

};

#endif
