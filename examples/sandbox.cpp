#include <iostream>
#include "engine.h"

int main(int argc, char** argv){

    // Just trying to use those core-defined entities in sanbox to ensure linking.
    Core::Vec2f o = { 6.0f, 5.0f };
    Core::Vec2f p = { 1.0f, 3.0f };
    Core::Vec2f d = { o[0] - p[0], o[1] - p[1] };
    std::cout << "O : (" << o[0] << ", " << o[1] << ")" << std::endl;
    std::cout << "P : (" << p[0] << ", " << p[1] << ")" << std::endl;
    std::cout << "d : (" << d[0] << ", " << d[1] << ")" << std::endl;

    return 0;
}