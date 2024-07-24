#include "../../include/libEditor.hpp"

#include <gtest/gtest.h>

struct testsEditor : public testing::Test {
  std::shared_ptr<IEditor> editor{nullptr};

  std::shared_ptr<Observer> shared = std::make_shared<ObserverForTests>();
  std::string forRemove{"Document-3"};
  
  void SetUp() override {
    editor = Editor::create();
  }
};

TEST_F(testsEditor, addDocument){
  editor->addDocument();
}

TEST_F(testsEditor, openDocument){
  std::string fname("Doc");
  editor->openDocument(fname);
}

TEST_F(testsEditor, safeDocument){
  editor->safeDocument();
}

TEST_F(testsEditor, safeDocumentAs){
  editor->safeDocumentAs("Doc");
}

TEST_F(testsEditor, addGraphicPrimitive){
  editor->addGraphicPrimitive();
}

TEST_F(testsEditor, removeGraphicPrimitive){
  editor->removeGraphicPrimitive(forRemove);
}

TEST_F(testsEditor, addObserver){
  editor->addObserver(shared);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
