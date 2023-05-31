#ifndef menu_hpp
#define menu_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

struct menuItemAttr{
    //menu item attributes
    bool readable; //read-in text otherwise a button
    std::string itemText; //associated text to menu option 
};

class menu{
    public:
        menu(sf::View); //constructor
        menu();
        ~menu(); //destructor
        
        void AddMenuItem(menuItemAttr);
        void SetView(sf::View);
        sf::View GetView();

        bool IsMenuOpen();

    private:
        sf::View menuView;
        std::vector<menuItemAttr> menuItems;

};

#endif
