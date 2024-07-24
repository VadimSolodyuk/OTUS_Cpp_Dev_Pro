#include "../../include/libView.hpp"

#include <gtest/gtest.h>


struct testsViewConsole : public testing::Test {
  std::shared_ptr<IEditor> editor = Editor::create();
  std::shared_ptr<IView> view = ViewConsole::create(editor);
};

TEST_F(testsViewConsole, update){
  view->update();
}



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
