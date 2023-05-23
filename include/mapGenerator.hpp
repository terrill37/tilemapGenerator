#ifndef mapGenerator_hpp
#define mapGenerator_hpp

#include "window.hpp"

#include <iostream>

class mapGenerator{
    public:
        mapGenerator();

        void Update();
        void drawGrid(int rows, int cols);
        void LateUpdate();
        void Draw();

        bool IsRunning() const;

    private:
        Window window;

};

#endif
