#pragma once

#include "Glyph.hpp"

#include <cstddef>
#include <memory>
#include <map>
#include <string>



class IDocument{
    inline static size_t _numberNoNameDocument{1};
    std::string _name{"Document-"};
protected:
    virtual std::shared_ptr<Glyph> creatGraphicPrimitive() = 0;
    IDocument();
    explicit IDocument(const char*);
public:
    virtual ~IDocument() = default;
    
    void setName(const char*);
    std::string getName() const;
    void save();
    void saveAs(const char*);
    void open();
    void close();

    virtual void addGraphicPrimitive() = 0;
    virtual void removGraphicPrimitive(const std::string&) = 0;
    virtual void draw(std::shared_ptr<IDisplay>&) const = 0;
};

class Document : public IDocument{
    std::map<std::string, std::shared_ptr<Glyph> > graphicElement;
public:
    ~Document() = default;
    
    static std::shared_ptr<IDocument> create();
    static std::shared_ptr<IDocument> create(const char*);

    virtual std::shared_ptr<Glyph> creatGraphicPrimitive() override;
    virtual void addGraphicPrimitive() override;
    virtual void removGraphicPrimitive(const std::string&) override;
    virtual void draw(std::shared_ptr<IDisplay>&) const override;
};