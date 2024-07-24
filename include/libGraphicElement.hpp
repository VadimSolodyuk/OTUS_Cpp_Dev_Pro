#pragma once

#include "Glyph.hpp"

#include <cstddef>
#include <memory>
#include <string>


class GraphicPrimitive : public Glyph, public std::enable_shared_from_this<GraphicPrimitive> {
    inline static size_t _numberGraphicPrimitive{1};
    std::string _name{"gp-"};
    GraphicPrimitive();
public:
    virtual ~GraphicPrimitive() = default;

    static std::shared_ptr<GraphicPrimitive> create();
    static std::shared_ptr<GraphicPrimitive> create(const char*);

    void setName(const char*);
    std::string getName() const override;


    virtual void draw(std::shared_ptr<IDisplay>&) const override;
};