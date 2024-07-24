#include "../../include/handlersEditor.hpp"

#include <gtest/gtest.h>
#include <memory>


struct testsHandlersFunstions : testing::Test {
  std::shared_ptr<IEditor> editor{nullptr};
  std::shared_ptr<IView> view{nullptr};
  std::shared_ptr<IController> controller{nullptr};

  void SetUp() override{
    editor = createEditor();
    view = createView(editor);
    controller = createController(editor);
  }

};

TEST_F(testsHandlersFunstions, createEditor){
	ASSERT_TRUE(editor != nullptr);
}

TEST_F(testsHandlersFunstions, createView){
  ASSERT_TRUE(view != nullptr);
}

TEST_F(testsHandlersFunstions, createController){
	ASSERT_TRUE(controller != nullptr);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
