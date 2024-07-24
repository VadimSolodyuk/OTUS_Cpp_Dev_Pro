#include "../../../include/libEditor.hpp"
#include "../../../include/libCommand.hpp"

#include <memory>


Editor::Editor(std::shared_ptr<IDocument> &document) : _document(document) {};

std::shared_ptr<IEditor> Editor::create() {
    auto ptrDoc = Document::create();
    static auto ptr = std::shared_ptr<Editor>{new Editor(ptrDoc)};
    return ptr; 
}

void Editor::drawDocument(std::shared_ptr<IDisplay> &display) const {
    _document->draw(display);
}

void Editor::addDocument() {
    _document = Document::create();
    notify();
}

void Editor::openDocument(const std::string &) {
    std::cout << "Opening a document ...(mock)\n"; 
    //...
    sleep(3);
    notify();
}

void Editor::safeDocument() {
    auto command = std::make_unique<SafeDocumentCommand>(_document);
    command->execute();
    notify();
}

void Editor::safeDocumentAs(const std::string &fname) {
    auto command = std::make_unique<SafeDocumentAsCommand>(_document, fname.data());
    command->execute();
    notify();
}

void Editor::addGraphicPrimitive() {
    auto command = std::make_unique<AddGraphicPrimitiveCommand>(_document);
    command->execute();
    notify();
}

void Editor::removeGraphicPrimitive(const std::string& name) {
    auto command = std::make_unique<RemoveGraphicPrimitiveCommand>(_document, name);
    command->execute();
    notify();
}