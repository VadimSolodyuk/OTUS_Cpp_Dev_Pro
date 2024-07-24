#include "../../include/libDocument.hpp"
#include "../../include/libDisplay.hpp"

#include <gtest/gtest.h>
#include <string>


struct testsDocument : public testing::Test {
  inline static int numberCreate{1};
  std::string name = "Document-" + std::to_string(numberCreate);
  std::string name_1{"Document"};
  std::string forRemove{"Document-5"};

  std::shared_ptr<IDocument> document = nullptr;
  std::shared_ptr<IDisplay> display{new ConsoleDisplay()};

  void SetUp() override {
    document = Document::create();
    ++numberCreate;
  }
};

TEST_F(testsDocument, constructDefaultAndGetName){
  ASSERT_TRUE(document->getName() == name);
}

TEST_F(testsDocument, setName){
  document->setName(name_1.data());
  ASSERT_TRUE(document->getName() == name_1);
}

TEST_F(testsDocument, getName){
  ASSERT_TRUE(document->getName() == name);
}

TEST_F(testsDocument, constructWithName){
  auto document = Document::create(name_1.data());
  ASSERT_TRUE(document->getName() == name_1);
}

TEST_F(testsDocument, save){
  document->save();
}

TEST_F(testsDocument, saveAs){
  document->saveAs(name.data());
}

TEST_F(testsDocument, open){
  document->open();
}

TEST_F(testsDocument, close){
  document->close();
}

TEST_F(testsDocument, addGraphicPrimitive){
  document->addGraphicPrimitive();
}

TEST_F(testsDocument, removGraphicPrimitive){
  document->removGraphicPrimitive(forRemove);
}

TEST_F(testsDocument, draw){
  document->draw(display);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
