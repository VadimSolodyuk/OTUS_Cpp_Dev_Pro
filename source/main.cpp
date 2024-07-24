#include "../include/handlersEditor.hpp"



int main() {
    auto editor = createEditor();
    auto view = createView(editor);
    auto controller = createController(editor);
    controller->start();
}