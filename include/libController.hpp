#pragma once

#include "libEditor.hpp"
#include "libCommand.hpp"

#include <memory>


class IController {
protected:
    std::shared_ptr<IEditor> _editor{nullptr};
    IController(std::shared_ptr<IEditor> &editor);
public:
    virtual ~IController() = default;
    
    virtual void start() = 0;
};

class Controller : public IController {
    std::unique_ptr<CommandHandler> _commandHandler;
    std::unique_ptr<CommandHandler> makeCommandHandler();
public:
    Controller(std::shared_ptr<IEditor> &editor);
    ~Controller() = default;

    virtual void start() override;
};


