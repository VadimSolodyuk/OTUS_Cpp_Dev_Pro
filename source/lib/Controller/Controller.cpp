#include "../../../include/libController.hpp"

#include <iostream>


IController::IController(std::shared_ptr<IEditor> &editor) : _editor(editor) {}

Controller::Controller(std::shared_ptr<IEditor> &editor) : IController(editor) {
    _commandHandler = makeCommandHandler();
}

std::unique_ptr<CommandHandler> Controller::makeCommandHandler() {
    auto hendler = std::make_unique<AddDocument>(_editor);
    hendler->add(std::make_unique<OpenDocument>(_editor));    
    hendler->add(std::make_unique<SafeDocument>(_editor));    
    hendler->add(std::make_unique<AddGraphicPrimitive>(_editor));
    hendler->add(std::make_unique<RemoveGraphicPrimitive>(_editor));    
    hendler->add(std::make_unique<Exit>(_editor));    
    return hendler;
};

void Controller::start() {
    std::string command;
    while (true)
    {
        _editor->notify();    
        std::getline(std::cin, command);
        _commandHandler->exec(command);
    }
};
