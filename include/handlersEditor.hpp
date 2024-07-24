#pragma once

#include "libEditor.hpp"
#include "libController.hpp"
#include "libView.hpp"


inline std::shared_ptr<IEditor> createEditor() {
    return Editor::create();
};

inline std::shared_ptr<IView> createView(std::shared_ptr<IEditor> &editor) {
    return ViewConsole::create(editor);
};

inline std::unique_ptr<IController> createController(std::shared_ptr<IEditor> &editor){ 
    return std::make_unique<Controller>(editor);
};