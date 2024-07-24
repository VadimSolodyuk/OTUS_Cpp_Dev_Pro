#include "../../include/libController.hpp"

#include <gtest/gtest.h>
#include <memory>

struct testsController : testing::Test {
  std::shared_ptr<IEditor> editor = Editor::create();
  std::unique_ptr<IController> controller = std::make_unique<Controller>(editor); //(std::move(std::make_unique<Controller>(editor)));
};

TEST_F(testsController, start){
  // controller->start();
};

// TEST_F(testsConsoleEditorUI, execute){
//   // ui.execute(std::shared_ptr<ICommand>);
// };



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
