#include "../../../include/libDocument.hpp"
#include "../../../include/libGraphicElement.hpp"

#include <algorithm>
#include <memory>
#include <iostream>
#include <string_view>
#include <unistd.h>


IDocument::IDocument() {
    _name += std::to_string (_numberNoNameDocument++);
}

IDocument::IDocument(const char* name) : _name(std::string_view(name)) {};

void IDocument::setName(const char* name) { _name = name; };

std::string IDocument::getName() const { return _name; };

void IDocument::save() {
    std::cout << "Saving a document ...(mock)\n"; 
    sleep(3);
    //...
};
void IDocument::saveAs(const char*) {
    //...
};
void IDocument::open() {
    //...
};
void IDocument::close() {
    //...
};

std::shared_ptr<IDocument> Document::create() {
    auto ptr = std::shared_ptr<Document>{new Document()};
    return ptr; 
}

std::shared_ptr<IDocument> Document::create(const char* name) {
    auto ptr = std::shared_ptr<Document>{new Document()};
    ptr->setName(name);
    return ptr; 
}

void Document::addGraphicPrimitive() {
    auto graphicPrimitive = creatGraphicPrimitive();
    graphicElement.insert(std::pair(graphicPrimitive->getName(), graphicPrimitive));
    //...
}

std::shared_ptr<Glyph> Document::creatGraphicPrimitive() {
    return GraphicPrimitive::create();
}

void Document::removGraphicPrimitive(const std::string& name) {
    auto iter = graphicElement.find(name);
    if (iter == graphicElement.end()) {
        std::cout << "Input error! Try again." << std::endl;
        sleep(3);
        return;
    }
    graphicElement.erase(iter);
}

void Document::draw(std::shared_ptr<IDisplay> &display) const {
    if (graphicElement.empty()) {
        std::cout << "\t" << this->getName() << " is empty" << std::endl; 
    } else {
        std::cout << "\t" << this->getName() << " contains:" << std::endl; 
        std::for_each(graphicElement.cbegin(), graphicElement.cend(), 
            [&display] (auto GE) {
                GE.second->draw(display);
            }
        ); 
    }    
}