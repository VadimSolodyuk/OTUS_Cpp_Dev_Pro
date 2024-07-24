#pragma once

#include <memory>
#include <string>

class IDisplay;

class Glyph {
public:
    virtual ~Glyph() = default;
    
    virtual void draw(std::shared_ptr<IDisplay>&) const = 0;

    virtual std::string getName() const = 0;
    virtual bool insert(std::unique_ptr<Glyph>, size_t) {return 0;};
    virtual bool remove(std::unique_ptr<Glyph>) {return 0;};
};


