#pragma once

#include "Observer.hpp"
#include "libDisplay.hpp"
#include "libEditor.hpp"



class IView : public Observer {
public:
    virtual ~IView() = default;
};

class ViewConsole : public IView, public std::enable_shared_from_this<ViewConsole>  {
    std::shared_ptr<IEditor> _editor;
    std::shared_ptr<IDisplay> _display;
    
    void setEditor (std::shared_ptr<IEditor> &editor);
public:
    static std::shared_ptr<IView> create (std::shared_ptr<IEditor> &editor);
    ~ViewConsole() = default;

    void update() override;
};
