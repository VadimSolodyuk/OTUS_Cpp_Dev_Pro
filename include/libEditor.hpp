#pragma once

#include "Observer.hpp"
#include "libDocument.hpp"


class IEditor :  public BaseObserved { 
public:
    virtual ~IEditor() = default;

    virtual void addDocument() = 0;
    virtual void openDocument(const std::string&) = 0;
    virtual void safeDocument() = 0;
    virtual void safeDocumentAs(const std::string&) = 0;
    virtual void addGraphicPrimitive() = 0;
    virtual void removeGraphicPrimitive(const std::string&) = 0;
    virtual void drawDocument(std::shared_ptr<IDisplay> &display) const = 0;
};


class Editor : public IEditor, public std::enable_shared_from_this<Editor> {
    std::shared_ptr<IDocument> _document;
    Editor(std::shared_ptr<IDocument> &document);
public:
    virtual ~Editor() = default;

    static std::shared_ptr<IEditor> create();

    void addDocument() override;
    void openDocument(const std::string&) override;
    void safeDocument() override;
    void safeDocumentAs(const std::string&) override;
    void addGraphicPrimitive() override;
    void removeGraphicPrimitive(const std::string&) override;
    virtual void drawDocument(std::shared_ptr<IDisplay> &display) const override;
};