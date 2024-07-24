#include "../../../include/libView.hpp"

#include <iostream>
#include <memory>


std::shared_ptr<IView> ViewConsole::create (std::shared_ptr<IEditor> &editor) {
    auto viewPtr = std::shared_ptr<ViewConsole>{new ViewConsole()};
    viewPtr->_display = std::shared_ptr<ConsoleDisplay>{new ConsoleDisplay()}; 
    viewPtr->setEditor(editor);
    return viewPtr;
}

void ViewConsole::setEditor (std::shared_ptr<IEditor> &editor) {
    _editor = editor;
    _editor->addObserver(shared_from_this());
}

void ViewConsole::update() {
    std::cout << "\n";
    system("clear");
    std::cout << "     <<< Editor_HW-5 >>>" << "\n" << std::endl;
    std::cout << "*******************************" << std::endl;
    _editor-> drawDocument(_display);
    std::cout
    << "*******************************\n"
    << "\n"
    << "\tEDITOR MENU:\n\n"
    << "с" << "\t- Create a new document\n"
    << "o" << "\t- Open a document\n"
    << "s" << "\t- Safe this document\n"
    << "cgp" << "\t- Сreating a graphic primitive\n"
    << "rgp" << "\t- Removing a graphic primitive\n"
    << "e" << "\t- Exit\n"
    << "\nEnter command: " ;
}