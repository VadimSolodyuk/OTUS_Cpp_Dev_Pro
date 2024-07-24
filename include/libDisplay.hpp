#pragma once

#include "libGraphicElement.hpp"


class IDisplay : public std::enable_shared_from_this<IDisplay> {
public:
    virtual ~IDisplay() = default;

    virtual void redraw() = 0;
    virtual void drawGraphicPrimitive (const std::shared_ptr<const GraphicPrimitive>&) = 0;
};


class ConsoleDisplay : public IDisplay {
public:
    virtual void redraw() override;
    virtual void drawGraphicPrimitive (const std::shared_ptr<const GraphicPrimitive>&) override;
};