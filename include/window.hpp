#ifndef Window_hpp
#define Window_hpp

#include <string>
#include <map>
#include <SFML/Graphics.hpp> //Find out if this is necessary


class Window{
    public:
        Window(const std::string& windowName) : window(sf::VideoMode(1024,576), windowName, sf::Style::Titlebar){
            window.setVerticalSyncEnabled(true);
        }

        float upX,upY;
        float lowX,lowY;

        void Update();
        sf::View GetDefaultView();
        void setView_upper();
        void setView_lower();
        void setView(sf::View);
        void setViewPort_upper(sf::FloatRect);
        void setViewPort_lower(sf::FloatRect);
        sf::View getDefaultView();
        sf::Vector2f getUpperCenter();
        sf::Vector2f getLowerCenter();
        sf::Vector2f getViewSize();
        sf::View Move(char, sf::View);
        void drawGrid(int, int);
        void tileMapping();
        std::pair<int,int> retUpCoords();
        std::pair<int,int> retLowCoords();
        void HighlightBin(int);
        void BeginDraw();
        void Draw(const sf::Drawable& drawable);
        void EndDraw();
        bool IsOpen() const;
        bool firstClick=false;
        

    private:
        sf::RenderWindow window;
        sf::View view_upper=sf::View(sf::FloatRect(0.f,0.f, window.getSize().x, 16*window.getSize().y/18));
        sf::View view_lower=sf::View(sf::FloatRect(0.f,0.f, window.getSize().x, window.getSize().y));
        std::pair<int,int> upCoords;
        std::pair<int,int> lowCoords;
};
#endif
