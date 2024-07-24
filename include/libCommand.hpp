#pragma once

#include "libEditor.hpp"    

#include <memory>
#include <iostream>
#include <string>
#include <unistd.h>



class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};

class EmptyForTests : public  ICommand {
    void execute() override {};
};


class DocumentCommand : public ICommand {
protected:
    std::weak_ptr<IDocument> _document;
    DocumentCommand(std::shared_ptr<IDocument> document) : _document(document){};
public:
    virtual ~DocumentCommand() = default;
};

class SafeDocumentCommand : public DocumentCommand {
public:
    SafeDocumentCommand(std::shared_ptr<IDocument> document) : DocumentCommand(document) {};
    ~SafeDocumentCommand() = default;

    void execute() override {
        _document.lock()->save();
    }; 
};

class SafeDocumentAsCommand : public DocumentCommand {
private:
    std::string _fname;
public:
    SafeDocumentAsCommand(std::shared_ptr<IDocument> document, const char* fname) : DocumentCommand(document), _fname(fname) {};
    ~SafeDocumentAsCommand() = default;

    void execute() override {
        _document.lock()->saveAs(_fname.data());
    }; 
};

class AddGraphicPrimitiveCommand : public DocumentCommand {
public:
    AddGraphicPrimitiveCommand(std::shared_ptr<IDocument> document) : DocumentCommand(document) {};
    ~AddGraphicPrimitiveCommand() = default;

    void execute() override {
        _document.lock()->addGraphicPrimitive();
    }; 
};

class RemoveGraphicPrimitiveCommand : public DocumentCommand {
private:
    std::string _name;
public:
    RemoveGraphicPrimitiveCommand(std::shared_ptr<IDocument> document, const std::string& name)
        : DocumentCommand(document), _name(name)
    {};

    ~RemoveGraphicPrimitiveCommand() = default;

    void execute() override {
        _document.lock()->removGraphicPrimitive(_name);
    }; 
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

struct DataEntry {
    virtual ~DataEntry() = default;
    virtual std::string input() = 0;
};

struct ConsoleDataEntry : DataEntry {
    std::string input() override {
       std::string data;
       std::getline(std::cin, data);
       return data;
    }
};

class CommandHandler {
    std::unique_ptr<CommandHandler> _next;  // поле для хранения ссылки на следующий объект цепочки
protected:
    std::weak_ptr<IEditor> _editor;
public:
    CommandHandler(std::shared_ptr<IEditor> &editor): _next(nullptr), _editor(editor) {} //
    virtual ~CommandHandler() = default;
    
    // метод получения следующего обработчика во всех конкретных обработчиках
    void add(std::unique_ptr<CommandHandler> n) {
        if (_next)
            _next->add(std::move(n));
        else
            _next = std::move(n);
    }

    //метод обработки перенаправляет запрос следующему объекту, проверив его наличие
    virtual void exec(const std::string &command) {  
        if (_next) {
            _next->exec(command);
        } else {
            std::cout << "Input error! Try again." << std::endl;
            sleep(3);
        }
    }
    virtual std::unique_ptr<DataEntry> makeDataEntry () {
        return std::make_unique<ConsoleDataEntry>();
    };
};

class AddDocument : public CommandHandler {
public:
    AddDocument(std::shared_ptr<IEditor> &editor) : CommandHandler(editor) {}

    void exec(const std::string &command) override {
        if (command == "c") {
            _editor.lock()->addDocument();
        } else {
            CommandHandler::exec(command);
        }
    }
};

class OpenDocument : public CommandHandler {
    std::unique_ptr<DataEntry> _dataEntry;
public:
    OpenDocument(std::shared_ptr<IEditor> &editor) : CommandHandler(editor) { //
        _dataEntry = makeDataEntry();
    }
    ~OpenDocument() = default;

   void exec(const std::string &command) override {
        if (command == "o") {
            std::cout << "Enter the file name: " ;
            _editor.lock()->openDocument(_dataEntry->input());
        } else {
            CommandHandler::exec(command);
        }
    }
};

class SafeDocument : public CommandHandler {
public:
    SafeDocument(std::shared_ptr<IEditor> &editor) : CommandHandler(editor) {};
    ~SafeDocument() = default;

   void exec(const std::string &command) override {
        if (command == "s") {
            _editor.lock()->safeDocument();
        } else {
            CommandHandler::exec(command);
        }
    }
};

class AddGraphicPrimitive : public CommandHandler {
public:
    AddGraphicPrimitive(std::shared_ptr<IEditor> &editor) : CommandHandler(editor) {};
    ~AddGraphicPrimitive() = default;

   void exec(const std::string &command) override {
        if (command == "cgp") {
            _editor.lock()->addGraphicPrimitive();
        } else {
            CommandHandler::exec(command);
        }
    }
};

class RemoveGraphicPrimitive : public CommandHandler {
    std::unique_ptr<DataEntry> _dataEntry;
public:
    RemoveGraphicPrimitive(std::shared_ptr<IEditor> &editor) : CommandHandler(editor) {
        _dataEntry = makeDataEntry();
    };
    ~RemoveGraphicPrimitive() = default;

   void exec(const std::string &command) override {
        if (command == "rgp") {
            std::cout << "Enter the primitive name: " ;
            _editor.lock()->removeGraphicPrimitive(_dataEntry->input());
        } else {
            CommandHandler::exec(command);
        }
    }
};

class Exit : public CommandHandler {
public:
    Exit(std::shared_ptr<IEditor> &editor) : CommandHandler(editor) {};

   void exec(const std::string &command) override {
        if (command == "e") {
            system("clear");
            exit(0);
        } else {
            CommandHandler::exec(command);
        }
    }
};
