#include "../../../include/libGraphicElement.hpp"
#include "../../../include/libDisplay.hpp"

#include <memory>
#include <string>


GraphicPrimitive::GraphicPrimitive() {
    _name += std::to_string (_numberGraphicPrimitive++); 
};

std::shared_ptr<GraphicPrimitive> GraphicPrimitive::create() {
    auto ptr = std::unique_ptr<GraphicPrimitive>{new GraphicPrimitive()};
    return ptr;
}

std::shared_ptr<GraphicPrimitive> GraphicPrimitive::create(const char* name) {
    auto ptr = std::unique_ptr<GraphicPrimitive>{new GraphicPrimitive()};
    ptr->setName(name);
    return ptr;
}

void GraphicPrimitive::setName(const char* name) {
    _name = name;
}

std::string GraphicPrimitive::getName() const {
   return _name;
}

void GraphicPrimitive::draw(std::shared_ptr<IDisplay> &dysplay) const {
    dysplay->drawGraphicPrimitive(this->shared_from_this());
};