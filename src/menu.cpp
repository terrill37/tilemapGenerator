#include "menu.hpp"

menu::menu(sf::View windowSize){
    menuView=windowSize;
}

menu::~menu(){}

void menu::AddMenuItem(menuItemAttr newItem){
    menuItems.push_back(newItem);
}

void menu::SetView(sf::View view){
    menuView=view;
}

sf::View menu::GetView(){
    return menuView;
}

bool menu::IsMenuOpen(){
    return true;
}
