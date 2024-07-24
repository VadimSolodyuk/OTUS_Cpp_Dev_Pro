#include "../../../include/libDisplay.hpp"

#include <iostream>


void ConsoleDisplay::redraw() {
    //...
};

void ConsoleDisplay::drawGraphicPrimitive(const std::shared_ptr<const GraphicPrimitive> &graphicPrimitive)
{
    std::cout << graphicPrimitive->getName() << std::endl;
};