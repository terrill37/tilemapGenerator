#ifndef Window_hpp
#define Window_hpp

#include <string>
#include <SFML/Graphics.hpp> //Find out if this is necessary


class Window{
    public:
        Window(const std::string& windowName) : window(sf::VideoMode(1024,576), windowName, sf::Style::Titlebar){
            window.setVerticalSyncEnabled(true);
        }

        float upX=0,upY=0;
        float lowX=0,lowY=0;

        void Update();
        void setView_upper();
        void setView_lower();
        void setView(sf::View);
        //void setViewPort(sf::View, sf::FloatRect);
        void setViewPort_upper(sf::FloatRect);
        void setViewPort_lower(sf::FloatRect);
        sf::View getDefaultView();
        sf::Vector2f getUpperCenter();
        sf::Vector2f getLowerCenter();
        sf::Vector2f getViewSize();
        sf::View Move(char, sf::View);
        void drawGrid(int, int);
        void HighlightBin(int);
        void BeginDraw();
        void Draw(const sf::Drawable& drawable);
        void EndDraw();
        bool IsOpen() const;
        
        //sf::View view_lower=sf::View(sf::FloatRect(0.f,0.f,1024.f,-64.f));

    private:
        sf::RenderWindow window;
        //sf::View view_upper=window.getDefaultView();
        sf::View view_upper=sf::View(sf::FloatRect(0.f,0.f, window.getSize().x, 16*window.getSize().y/18));
        sf::View view_lower=sf::View(sf::FloatRect(0.f,0.f, window.getSize().x, window.getSize().y));
        //sf::Vector2f sq=(1024.f,64.f);
        //sf::View view_lower=sf::View(sf::Vector2f(1024.f,64.f),sf::Vector2f(1000.f,1000.f));
};
#endif
