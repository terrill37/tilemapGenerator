#ifndef Window_hpp
#define Window_hpp

#include <string>
#include <SFML/Graphics.hpp> //Find out if this is necessary


class Window{
    public:
        Window(const std::string& windowName) : window(sf::VideoMode(1024,512), windowName, sf::Style::Titlebar){
            window.setVerticalSyncEnabled(true);
        }

        void Update();
        void setView();
        sf::Vector2f getViewSize();
        void BeginDraw();
        void Draw(const sf::Drawable& drawable);
        void EndDraw();
        bool IsOpen() const;

    private:
        sf::RenderWindow window;

};
#endif
